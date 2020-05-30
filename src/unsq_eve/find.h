/*
 * Copyright 2020 Denis Yaroshevskiy
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef UNSQ_EVE_FIND_H_
#define UNSQ_EVE_FIND_H_

#include <algorithm>
#include <array>

#include "eve_extra/eve_extra.h"

#include "unsq_eve/concepts.h"
#include "unsq_eve/iteration_guarded.h"
#include "unsq_eve/iteration_unguarded.h"
#include "unsq_eve/predicate_helpers.h"

namespace unsq_eve {
namespace _find {

template <typename Traits, typename StrippedI, typename PV>
// require ContigiousIterator<I> && VectorPredicate<PV, ValueType<I>>
struct body {
  using T = value_type<StrippedI>;
  using wide = eve::wide<T, width_t<Traits>>;

  PV p;
  StrippedI found;

  // Intentionally unitilialized
  std::array<wide, Traits::unroll()> regs;

  body(PV p, StrippedI found) : p(p), found(found) {}

  template <typename Ptr, std::size_t idx, typename Ignore>
  bool small_step(Ptr from, indx_c<idx>, Ignore ignore) {
    // For unguarded we never know if we are complete in the data
    regs[idx] = eve_extra::load_unsafe(from, eve::as_<wide>{});

    const std::optional match = first_true(p(regs[idx]), ignore);
    if (!match) return false;

    found = &*from + *match;
    return true;
  }

  // All registers are already intialized with small steps
  // before invoking big steps.
  // Big step will be invoked for each register, in order, once each step.

  void before_big_steps() {}

  template <typename Ptr>
  void start_big_step(Ptr) {}

  template <typename Ptr, std::size_t idx>
  bool big_step(Ptr ptr, indx_c<idx>) {
    // For unguarded we never know if we are complete in the data
    regs[idx] = eve_extra::load_unsafe(ptr, eve::as_<wide>{});
    return false;
  }

  template <typename Ptr>
  bool complete_big_step(Ptr from) {
    // Compute predicate for each register
    std::array<eve::logical<wide>, Traits::unroll()> tests;
    std::transform(regs.begin(), regs.end(), tests.begin(), p);

    const std::optional match = eve_extra::first_true_array(tests);
    if (!match) return false;

    found = &*from + *match;

    return true;
  }

  void after_big_steps() {}
};

}  // namespace _find

template <typename Traits, typename I, wide_predicate_for<Traits, I> PV>
// require ContigiousIterator<I>
I find_if(I _f, I _l, PV p) {
  auto [f, l] = drill_down_range(_f, _l);

  _find::body<Traits, decltype(f), PV> body{p, l};
  auto* found = iteration_aligned<Traits>(f, l, body).found;

  return undo_drill_down(_f, found);
}

template <typename Traits, typename I, typename T>
I find(I f, I l, const T& x) {
  return unsq_eve::find_if<Traits>(f, l, equal_to<Traits, I>(x));
}

template <typename Traits, typename I, wide_predicate_for<Traits, I> PV>
// require ContigiousIterator<I> && VectorPredicate<PV, ValueType<I>>
I find_if_unguarded(I _f, PV p) {
  auto* f = drill_down(_f);

  _find::body<Traits, decltype(f), PV> body{p, f};
  auto* found = iteration_aligned_unguarded<Traits>(f, body).found;

  return undo_drill_down(_f, found);
}

template <typename Traits, typename I, typename T>
// require ContigiousIterator<I> && Convertible<T, ValueType<P>>
I find_unguarded(I f, const T& x) {
  return unsq_eve::find_if_unguarded<Traits>(f, equal_to<Traits, I>(x));
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_FIND_H_
