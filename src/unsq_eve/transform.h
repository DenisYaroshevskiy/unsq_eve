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
#include "unsq_eve/iteration_one_range_aligned_stores.h"

namespace unsq_eve {
namespace _transform {

template <typename Traits, typename I, typename Op>
struct inplace_body {
  using T = typename Traits::type;
  using wide_read = eve::wide<value_type<I>, width_t<Traits>>;
  using wide = typename Traits::wide;

  Op op;

  std::array<wide, Traits::unroll()> regs;

  inplace_body(Op op) : op(op) {}

  template <typename Ptr, std::size_t idx, typename Ignore>
  void under_chunk_size_step(Ptr ptr, indx_c<idx>, const wide_read& read,
                             Ignore ignore) {
    wide xs = eve::convert(read, eve::as_<T>{});
    wide transfromed = op(xs);
    wide_read ys = eve::convert(transfromed, eve::as_<value_type<I>>{});
    eve_extra::store(ys, ptr, ignore);
  }

  template <typename Ptr, std::size_t idx, typename Ignore>
  bool small_step(Ptr ptr, const wide_read& read, indx_c<idx>, Ignore ignore) {
    wide xs = eve::convert(read, eve::as_<T>{});
    wide transfromed = op(xs);
    wide_read ys = eve::convert(transfromed, eve::as_<value_type<I>>{});
    eve_extra::store(ys, ptr, ignore);
    return false;
  }

  template <typename Ptr, std::size_t _idx, typename Ignore>
  bool small_step(Ptr ptr, indx_c<_idx> idx, Ignore ignore) {
    wide_read read;
    if constexpr (std::is_same_v<Ignore, eve_extra::ignore_nothing>) {
      read = wide_read{ptr};
    } else {
      read = eve_extra::load_unsafe(ptr, eve::as_<wide_read>{});
    }
    return small_step(ptr, read, idx, ignore);
  }

  void before_big_steps() {}

  template <typename Ptr>
  void start_big_step(Ptr) {}

  template <typename Ptr, std::size_t idx>
  bool big_step(Ptr, const wide_read& read, indx_c<idx>) {
    regs[idx] = eve::convert(read, eve::as_<T>{});
    return false;
  }

  template <typename Ptr, std::size_t _idx>
  bool big_step(Ptr ptr, indx_c<_idx> idx) {
    return big_step(ptr, wide_read{ptr}, idx);
  }

  template <typename Ptr>
  bool complete_big_step(Ptr ptr) {
    for (auto& reg : regs) {
      reg = op(reg);
    }

    for (Ptr it = ptr; auto& reg : regs) {
      wide_read ys = eve::convert(reg, eve::as_<value_type<I>>{});
      eve::store(ys, it);
      it += wide_read::static_size;
    }

    return false;
  }

  void after_big_steps() {}
};

}  // namespace _transform

template <typename Traits, contigious_iterator I,
          wide_map_unary<typename Traits::wide> Op>
EVE_FORCEINLINE void transform(I _f, I _l, Op op) {
  _transform::inplace_body<Traits, I, Op> body{op};
  auto [f, l] = drill_down_range(_f, _l);
  iteration_one_range_aligned_stores<iteration_traits_t<Traits>>(f, l, body);
}

template <typename Traits, contigious_iterator I,
          wide_map_unary<typename Traits::wide> Op>
EVE_FORCEINLINE void transform_masked(I _f, I _l, Op op) {
  _transform::inplace_body<Traits, I, Op> body{op};
  auto [f, l] = drill_down_range(_f, _l);
  iteration_aligned<iteration_traits_t<Traits>>(f, l, body);
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_TRANSFORM_H_
