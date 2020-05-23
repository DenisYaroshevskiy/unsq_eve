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

#include "eve_extra/eve_extra.h"

#include "unsq_eve/iteration_guarded.h"

namespace unsq_eve {
namespace _all_any_none {

template <typename Traits, typename StrippedI, typename PV>
// require ContigiousIterator<I> && VectorPredicate<PV, ValueType<I>>
struct any_body {
  using wide = eve::wide<ValueType<StrippedI>, width_t<Traits>>;
  using extra_wide = eve::wide<ValueType<StrippedI>, extra_width_t<Traits>>;

  PV p;
  bool res = false;

  any_body(PV p) : p(p) {}

  template <typename Ptr, typename Ignore>
  bool small_step(Ptr ptr, Ignore ignore) {
    wide reg;
    if constexpr (std::is_same_v<Ignore, eve_extra::ignore_nothing>) {
      reg = wide{ptr};
    } else {
      reg = eve_extra::load_unsafe(ptr, eve::as_<wide>{});
    }
    res = eve_extra::any(p(reg), ignore);
    return res;
  }

  template <typename Ptr>
  bool big_step(Ptr ptr, eve_extra::ignore_nothing ignore) {
    extra_wide reg{ptr};
    auto applied = eve_extra::widened_predicate<wide, extra_wide>(p)(reg);

    if constexpr(Traits::use_extra_any) {
      res = eve_extra::any(applied, ignore);
    } else {
      res = eve::any(applied);
    }
    return res;
  }
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
