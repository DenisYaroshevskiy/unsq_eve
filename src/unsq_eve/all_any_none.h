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

#include "unsq_eve/iteration_guarded.h"

namespace unsq_eve {
namespace _all_any_none {

template <typename Traits, typename StrippedI, typename PV>
// require ContigiousIterator<I> && VectorPredicate<PV, ValueType<I>>
struct any_body {
  using T = ValueType<StrippedI>;
  using wide = eve::wide<T, width_t<Traits>>;

  PV p;
  bool res = false;

  // Intentionally unitilialized
  std::array<wide, Traits::unroll()> regs;

  explicit any_body(PV p) : p(p) {}

  template <typename Ptr, std::size_t idx, typename Ignore>
  bool small_step(Ptr ptr, indx_c<idx>, Ignore ignore) {
    if constexpr (std::is_same_v<Ignore, eve_extra::ignore_nothing>) {
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
  void start_big_step() {}

  template <typename Ptr, std::size_t idx>
  bool big_step(Ptr ptr, indx_c<idx>) {
    regs[idx] = wide{ptr};
    return false;
  }

  bool complete_big_step() {
    using logical = eve::logical<wide>;
    using extra_fixed = eve::fixed<Traits::width() * Traits::unroll()>;
    using extra_wide = eve::wide<T, extra_fixed>;
    using extra_logical = eve::logical<extra_wide>;

    using bool_t = typename extra_logical::value_type;
    using aligned_ptr = eve::aligned_ptr<bool_t, alignof(extra_logical)>;

    // Compute predicate for each register
    alignas(extra_logical) std::array<logical, Traits::unroll()> tests;
    std::transform(regs.begin(), regs.end(), tests.begin(), p);

    // Pretened this is 'eve::wide'
    aligned_ptr tests_ptr{reinterpret_cast<bool_t*>(tests.data())};
    const extra_logical as_extra_wide{tests_ptr};

    // Do a smarter any
    if constexpr (Traits::use_extra_any)
      res = eve_extra::any(as_extra_wide, eve_extra::ignore_nothing{});
    else
      res = eve::any(as_extra_wide);
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

}  // namespace _all_any_none

template <typename Traits, typename I, typename PV>
// require ContigiousIterator<I> && VectorPredicate<PV, ValueType<I>>
bool any_of(I _f, I _l, PV p) {
  auto [f, l] = drill_down_range(_f, _l);

  _all_any_none::any_body<Traits, decltype(f), PV> body{p};

  return iteration_aligned<Traits>(f, l, body).res;
}

template <typename Traits, typename I, typename T>
// require ContigiousIterator<I> && VectorPredicate<PV, ValueType<I>>
bool any_of_is(I f, I l, const T& x) {
  return unsq_eve::any_of<Traits>(f, l, _all_any_none::equal_to<Traits, I>(x));
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ALL_ANY_NONE_H_
