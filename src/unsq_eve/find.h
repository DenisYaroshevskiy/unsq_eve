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

#include "unsq_eve/iteration_guarded.h"

namespace unsq_eve {
namespace _find {

template <typename Traits, typename StrippedI, typename PV>
// require ContigiousIterator<I> && VectorPredicate<PV, ValueType<I>>
struct body {
  using T = ValueType<StrippedI>;
  using wide = eve::wide<T, width_t<Traits>>;

  PV p;
  StrippedI found;

  // Intentionally unitilialized
  std::array<wide, Traits::unroll()> regs;

  body(PV p, StrippedI found) : p(p), found(found) {}

  template <typename Ptr, std::size_t idx, typename Ignore>
  bool small_step(Ptr ptr, indx_c<idx>, Ignore ignore) {
    if constexpr (std::is_same_v<Ignore, eve_extra::ignore_nothing>) {
      regs[idx] = wide{ptr};
    } else {
      regs[idx] = eve_extra::load_unsafe(ptr, eve::as_<wide>{});
    }

    const std::optional match = first_true(p(regs[idx]), ignore);
    if (!match) return false;

    found = &*from + *match;
    return true;
  }

  // All registers are already intialized with small steps
  // before invoking big steps.
  // Big step will be invoked for each register, in order, once each step.

  void before_big_steps() {}
  void start_big_step() {}

  template <typename Ptr, std::size_t idx>
  bool big_step(Ptr ptr, indx_c<idx>) {
    regs[idx] = wide{ptr};
    return false;
  }

  bool complete_big_step() {
    // Compute predicate for each register
    std::array<eve::logical<wide>, Traits::unroll()> tests;
    std::transform(regs.begin(), regs.end(), tests.begin(), p);

    const std::optional match = first_true(p(regs[idx]), ignore);

    // Reduce the result
    auto reduced = eve_extra::segment_reduction(tests, eve::logical_or);
    res = eve_extra::any(reduced, eve_extra::ignore_nothing{});
    return res;
  }

  void after_big_steps() {}
};

template <typename Traits, typename I, typename U>
auto equal_to(const U& y) {
  using T = ValueType<I>;
  using wide = eve::wide<T, width_t<Traits>>;
  wide ys{static_cast<T>(y)};
  return [ys](const wide& xs) { return xs == ys; };
}

}  // namespace _find

template <typename Traits, typename I, typename PV>
// require ContigiousIterator<I> && VectorPredicate<PV, ValueType<I>>
I find_if(I _f, I _l, PV p) {
  auto [f, l] = drill_down_range(_f, _l);

  _find::body<Traits, decltype(f), PV> body{p, l};
  auto* found = iteration_aligned<Traits>(f, l, body).res;

  return undo_drill_down(_f, found);
}

template <typename Traits, typename I, typename T>
// require ContigiousIterator<I> && VectorPredicate<PV, ValueType<I>>
I find(I f, I l, const T& x) {
  return unsq_eve::find_if<Traits>(f, l, equal_to<Traits, I>(x));
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_FIND_H_
