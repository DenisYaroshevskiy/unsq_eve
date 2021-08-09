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

#ifndef UNSQ_EVE_TRANSFORM_H_
#define UNSQ_EVE_TRANSFORM_H_

#include <eve/function/convert.hpp>

#include "eve_extra/eve_extra.h"
#include "unsq_eve/concepts.h"
#include "unsq_eve/iteration_guarded.h"

namespace unsq_eve {
namespace _transform {

template <typename Traits, typename I, typename Op>
struct inplace_body {
  using T = typename Traits::type;
  using wide_read = eve::wide<value_type<I>, width_t<Traits>>;
  using wide = typename Traits::wide;

  Op op;

  std::array<wide, Traits::unroll()> regs;

  explicit inplace_body(Op op) : op(op) {}

  void set_base(I) {}

  template <typename Ptr, std::size_t idx, typename Ignore>
  bool small_step(Ptr ptr, indx_c<idx>, Ignore ignore) {
    wide_read read;

    if constexpr (std::is_same_v<Ignore, eve::ignore_none_>) {
      read = wide_read{ptr};
    } else {
      read = eve::unsafe(eve::load)(ptr, width_t<Traits>{});
    }

    wide xs = eve::convert(read, eve::as<T>{});
    wide transfromed = op(xs);
    wide_read ys = eve::convert(transfromed, eve::as<value_type<I>>{});
    eve::store[ignore](ys, ptr);
    return false;
  }

  void before_big_steps() {}

  template <typename Ptr>
  void start_big_step(Ptr) {}

  template <typename Ptr, std::size_t idx>
  bool big_step(Ptr ptr, indx_c<idx>) {
    regs[idx] = eve::convert(wide_read{ptr}, eve::as<T>{});
    return false;
  }

  template <typename Ptr>
  bool complete_big_step(Ptr ptr) {
    for (auto& reg : regs) {
      reg = op(reg);
    }

    for (Ptr it = ptr; auto& reg : regs) {
      wide_read ys = eve::convert(reg, eve::as<value_type<I>>{});
      eve::store(ys, it);
      it += wide_read::size();
    }

    return false;
  }

  void after_big_steps() {}
};

}  // namespace _transform

template <typename Traits, contigious_iterator I,
          wide_map_unary<typename Traits::wide> Op>
EVE_FORCEINLINE void transform(I _f, I _l, Op op) {
  if (_f == _l) return;

  _transform::inplace_body<Traits, Pointer<I>, Op> body{op};
  auto [f, l] = drill_down_range(_f, _l);
  iteration_aligned<iteration_traits_t<Traits>>(f, l, body);
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_TRANSFORM_H_
