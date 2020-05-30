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

#ifndef UNSQ_EVE_TRANSFORM_REDUCE_H_
#define UNSQ_EVE_TRANSFORM_REDUCE_H_

#include <array>

#include <eve/function/convert.hpp>

#include "eve_extra/eve_extra.h"
#include "unsq_eve/concepts.h"
#include "unsq_eve/iteration_guarded.h"

namespace unsq_eve {
namespace _transform_reduce {

template <typename Traits, typename I, typename ZeroT, typename Reduce,
          typename Map>
struct unary_body {
  using T = value_type<I>;

  using wide_read = wide_for<Traits, I>;
  using wide_mapped = std::decay_t<decltype(std::declval<Map>()(wide_read{}))>;

  using U = std::common_type_t<typename wide_mapped::value_type, ZeroT>;
  using wide_reduced = eve::wide<U, width_t<Traits>>;

  Map map;
  Reduce reduce;
  wide_read small_zeroes;
  std::array<wide_reduced, Traits::unroll()> regs;

  unary_body(Map map, Reduce reduce, ZeroT zero)
      : map{map}, reduce{reduce}, small_zeroes{static_cast<T>(zero)} {
    regs.fill(wide_reduced{zero});
  }

  template <typename Ptr, std::size_t idx, typename Ignore>
  bool small_step(Ptr from, indx_c<idx>, Ignore ignore) {
    wide_read read;
    if constexpr (std::is_same_v<Ignore, eve_extra::ignore_nothing>) {
      read = wide_read{from};
    } else {
      read = eve_extra::load_unsafe(from, eve::as_<wide_read>{});
    }

    read = eve_extra::replace_ignored(read, ignore, small_zeroes);

    const auto mapped = map(read);
    const auto to_reduce = eve::convert(mapped, eve::as_<U>{});

    regs[idx] = reduce(regs[idx], to_reduce);
    return false;
  }

  void before_big_steps() {}

  template <typename Ptr>
  void start_big_step(Ptr) {}

  template <typename Ptr, std::size_t idx_>
  bool big_step(Ptr ptr, indx_c<idx_> idx) {
    return small_step(ptr, idx, eve_extra::ignore_nothing{});
  }

  template <typename Ptr>
  bool complete_big_step(Ptr) {
    return false;
  }

  void after_big_steps() {}

  U final_reduction() const {
    auto combined = eve_extra::segment_reduction(regs, reduce);
    combined = eve_extra::reduce_wide(combined, reduce);
    return combined[0];
  }
};

}  // namespace _transform_reduce

template <typename Traits, contigious_iterator I, typename T,
          typename Reduction, wide_map_unary_for<Traits, I> Map>
auto transform_reduce(I _f, I _l, const T& zero, Reduction reduce, Map map) {
  _transform_reduce::unary_body<Traits, I, T, Reduction, Map> body(map, reduce,
                                                                   zero);
  auto [f, l] = drill_down_range(_f, _l);

  return iteration_aligned<Traits>(f, l, body).final_reduction();
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_TRANSFORM_REDUCE_H_
