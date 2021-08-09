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

#ifndef UNSQ_EVE_INCLUSIVE_SCAN_H
#define UNSQ_EVE_INCLUSIVE_SCAN_H

#include <eve/function/add.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/replace.hpp>

#include "eve_extra/eve_extra.h"
#include "unsq_eve/concepts.h"
#include "unsq_eve/iteration_guarded.h"

namespace unsq_eve {

namespace _inclusive_scan {

template <typename Traits, typename I, typename Op>
struct inplace_body {
  using T = typename Traits::type;
  using wide_read = eve::wide<value_type<I>, width_t<Traits>>;
  using wide = typename Traits::wide;

  Op op;
  wide zeroes;
  wide running_sum;

  inplace_body(Op op, T zero) : op(op), zeroes(zero), running_sum(zeroes) {}

  void set_base(I) {}

  template <typename Ptr, std::size_t idx, typename Ignore>
  bool small_step(Ptr ptr, indx_c<idx>, Ignore ignore) {
    wide_read read;
    if constexpr (std::is_same_v<Ignore, eve::ignore_none_>) {
      read = wide{ptr};
    } else {
      read = eve::unsafe(eve::load)(ptr, width_t<Traits>{});
    }

    wide xs = eve::convert(read, eve::as<T>{});
    xs = eve::replace_ignored(xs, ignore, zeroes);
    xs = eve_extra::inclusive_scan_wide(xs, op, zeroes);
    xs = op(running_sum, xs);
    running_sum = wide(xs.get(wide::size() - 1));

    wide_read ys = eve::convert(xs, eve::as<value_type<I>>{});
    eve::store[ignore](ys, ptr);

    return false;
  }

  void before_big_steps() {}

  template <typename Ptr>
  void start_big_step(Ptr) {}

  template <typename Ptr, std::size_t _idx>
  bool big_step(Ptr ptr, indx_c<_idx> idx) {
    return small_step(ptr, idx, eve::ignore_none);
  }

  template <typename Ptr>
  bool complete_big_step(Ptr) {
    return false;
  }

  void after_big_steps() {}
};

}  // namespace _inclusive_scan

template <typename Traits, contigious_iterator I, typename Op>
EVE_FORCEINLINE void inclusive_scan_inplace(I _f, I _l, Op op,
                                            const value_type<I>& zero) {
  _inclusive_scan::inplace_body<Traits, Pointer<I>, Op> body{op, zero};

  auto [f, l] = drill_down_range(_f, _l);

  iteration_aligned<iteration_traits_t<Traits>>(f, l, body);
}

template <typename Traits, contigious_iterator I, typename Op>
EVE_FORCEINLINE void inclusive_scan_inplace(I f, I l, Op op) {
  unsq_eve::inclusive_scan_inplace<Traits>(f, l, op, value_type<I>{});
}

template <typename Traits, contigious_iterator I>
EVE_FORCEINLINE void inclusive_scan_inplace(I f, I l) {
  unsq_eve::inclusive_scan_inplace<Traits>(f, l, eve::add);
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_INCLUSIVE_SCAN_H
