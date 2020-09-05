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

#ifndef UNSQ_EVE_ALL_ANY_NONE_H_
#define UNSQ_EVE_ALL_ANY_NONE_H_

#include <algorithm>
#include <array>

#include "eve_extra/eve_extra.h"

#include "unsq_eve/concepts.h"
#include "unsq_eve/iteration_guarded.h"
#include "unsq_eve/predicate_helpers.h"

namespace unsq_eve {
namespace _all_any_none {

template <typename Traits, typename StrippedI, typename PV>
// require ContigiousIterator<I> && VectorPredicate<PV, ValueType<I>>
struct any_body {
  using T = value_type<StrippedI>;
  using wide = eve::wide<T, width_t<Traits>>;

  PV p;
  bool res = false;

  // Intentionally unitilialized
  std::array<wide, Traits::unroll()> regs;

  explicit any_body(PV p) : p(p) {}

  void set_base(StrippedI) {}

  template <typename Ptr, std::size_t idx, typename Ignore>
  bool small_step(Ptr ptr, indx_c<idx>, Ignore ignore) {
    if constexpr (std::is_same_v<Ignore, eve::ignore_none_>) {
      regs[idx] = wide{ptr};
    } else {
      regs[idx] = eve_extra::load_unsafe(ptr, eve::as_<wide>{});
    }

    res = eve_extra::any(p(regs[idx]), ignore);

    return res;
  }

  // All registers are already intialized with small steps
  // before invoking big steps.
  // Big step will be invoked for each register, in order, once each step.

  void before_big_steps() {}

  template <typename Ptr>
  void start_big_step(Ptr) {}

  template <typename Ptr, std::size_t idx>
  bool big_step(Ptr ptr, indx_c<idx>) {
    regs[idx] = wide{ptr};
    return false;
  }

  template <typename Ptr>
  bool complete_big_step(Ptr) {
    // Compute predicate for each register
    std::array<eve::logical<wide>, Traits::unroll()> tests;
    std::transform(regs.begin(), regs.end(), tests.begin(), p);

    res = eve_extra::any_array(tests);
    return res;
  }

  void after_big_steps() {}
};

}  // namespace _all_any_none

template <typename Traits, contigious_iterator I, wide_predicate_for<Traits> PV>
EVE_FORCEINLINE bool any_of(I _f, I _l, PV p) {
  auto [f, l] = drill_down_range(_f, _l);

  _all_any_none::any_body<Traits, decltype(f), PV> body{p};

  return iteration_aligned<iteration_traits_t<Traits>>(f, l, body).res;
}

template <typename Traits, contigious_iterator I,
          std::convertible_to<value_type<I>> T>
EVE_FORCEINLINE bool any_of_is(I f, I l, const T& x) {
  return unsq_eve::any_of<Traits>(f, l, equal_to<Traits, I>(x));
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ALL_ANY_NONE_H_
