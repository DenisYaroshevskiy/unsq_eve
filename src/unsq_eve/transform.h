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
#include "unsq_eve/iteration_one_range_aligned_stores.h"

namespace unsq_eve {
namespace _transform {

template <typename Traits, typename I, typename Op>
struct inplace_body {
  using T = typename Traits::type;
  using wide_read = eve::wide<value_type<I>, width_t<Traits>>;
  using wide = typename Traits::wide;

  Op op;

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
  bool small_step(Ptr ptr, const wide_read& read, indx_c<idx>, Ignore) {
    wide xs = eve::convert(read, eve::as_<T>{});
    wide transfromed = op(xs);
    wide_read ys = eve::convert(transfromed, eve::as_<value_type<I>>{});
    eve::store(ys, ptr);
    return false;
  }

  void before_big_steps() {}

  template <typename Ptr>
  void start_big_step(Ptr) {}

  template <typename Ptr, std::size_t idx_>
  bool big_step(Ptr ptr, const wide_read& read, indx_c<idx_> idx) {
    return small_step(ptr, read, idx, eve_extra::ignore_nothing{});
  }

  template <typename Ptr>
  bool complete_big_step(Ptr) {
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

}  // namespace unsq_eve

#endif  // UNSQ_EVE_TRANSFORM_H_
