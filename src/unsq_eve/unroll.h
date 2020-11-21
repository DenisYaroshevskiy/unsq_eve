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

#ifndef UNSQ_EVE_ITERATION_MAIN_LOOP_UNROLLED_H_
#define UNSQ_EVE_ITERATION_MAIN_LOOP_UNROLLED_H_

#include <cstddef>
#include <cstdint>
#include <utility>

#include "unsq_eve/iteration_traits.h"

namespace unsq_eve {

namespace _unroll {

template <typename Op, std::size_t... unroll_idxs>
EVE_FORCEINLINE StopReason do_unroll(Op op, std::index_sequence<unroll_idxs...>) {
  StopReason res = StopReason::No;
  ([&]() mutable {
    res = op(indx_c<unroll_idxs>{});
    return res != StopReason::No;
  }() ||
   ...);
  return res;
}

}  // namespace _unroll

template <std::size_t how_much, typename Op>
EVE_FORCEINLINE auto unroll(Op op) {
  return _unroll::do_unroll(op, std::make_index_sequence<how_much>{});
}

template <typename Traits, typename Ptr, typename Op>
EVE_FORCEINLINE void unroll_iteration(Ptr f, Op op) {
  auto tranformed_op = [&](auto idx) mutable {
    Ptr offset_ptr = f + Traits::chunk_size() * idx;
    return op(offset_ptr, idx) ? StopReason::Terminated : StopReason::No;
  };

  while (unroll<Traits::unroll()>(tranformed_op) == StopReason::No) {
    f += Traits::chunk_size() * Traits::unroll();
  }
}  // namespace unsq_eve

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ITERATION_MAIN_LOOP_UNROLLED_H_
