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

#ifndef UNSQ_EVE_ITERATION_TWO_SIDES_H_
#define UNSQ_EVE_ITERATION_TWO_SIDES_H_

#include <algorithm>

#include "eve_extra/eve_extra.h"
#include "unsq_eve/iteration_traits.h"
#include "unsq_eve/unroll.h"

namespace unsq_eve {
namespace _iteration_two_sides_parallel {

// [0 1 2 3 4 5 6]
// (0 1 2 3) (3 4 5 6)
// (3 2 1 0) (6 5 4 3)
// (6 5 4 3)
//       (3 2 1 0)
// [6 5 4 3 2 1 0]
// -------------------
//
// [0 1 2 3 4 5 6 7 8 9]
// (0 1 2 3)   (6 7 8 9)
// [9 8 7 6 4 5 3 2 1 0]
// (4 5 3 2)
//

template <typename Traits, typename T, typename Delegate>
EVE_FORCEINLINE Delegate less_then_chunk(T* f, T* l, Delegate& delegate) {
  if (eve_extra::end_of_page(f) - f < static_cast<int>(Traits::chunk_size())) {
    T* read_from = l - Traits::chunk_size();
    delegate.small_array_step(read_from, eve::ignore_first_{f - read_from});
    return delegate;
  }
  delegate.small_array_step(f, eve::ignore_last_{f + Traits::chunk_size() - l});
  return delegate;
}

template <typename Traits, typename T, typename Delegate>
EVE_FORCEINLINE StopReason
main_loop(T* f, T* l, std::ptrdiff_t n,
          Delegate& delegate) requires(Traits::unroll() == 1) {
  while (n--) {
    l -= Traits::chunk_size();
    delegate.small_step(f, l);
    f += Traits::chunk_size();
  }
  return StopReason::No;
}

template <typename Traits, typename T, typename Delegate>
EVE_FORCEINLINE StopReason main_loop(T* f, T* l, std::ptrdiff_t n,
                                     Delegate& delegate) {
  while (true) {  // To the beginning at most twice
    // initialize every register with small steps
    // (also can help for smaller range size)
    // (also reusable for when not enough for big step)

    StopReason res = unroll<Traits::unroll()>([&](auto) mutable {
      if (!n--) return StopReason::EndReached;
      l -= Traits::chunk_size();
      delegate.small_step(f, l);
      f += Traits::chunk_size();
      return StopReason::No;
    });

    if (res != StopReason::No) return res;

    for (; n >= static_cast<std::ptrdiff_t>(Traits::unroll());
         n -= static_cast<std::ptrdiff_t>(Traits::unroll())) {
      // Don't know what bigstep should look like yet
      unroll<Traits::unroll()>([&](auto) mutable {
        l -= Traits::chunk_size();
        delegate.small_step(f, l);
        f += Traits::chunk_size();
        return StopReason::No;
      });
    }
  }
}

}  // namespace _iteration_two_sides_parallel

template <typename Traits, typename T, typename Delegate>
// require IterationTwoSidesParallelDelegate<Delegate>
EVE_FORCEINLINE Delegate iteration_two_sides_parallel(T* f, T* l,
                                                      Delegate delegate) {
  std::ptrdiff_t two_register_steps = (l - f) / (2 * Traits::chunk_size());
  std::ptrdiff_t left = (l - f) - Traits::chunk_size() * 2 * two_register_steps;

  if (left < static_cast<std::ptrdiff_t>(Traits::chunk_size())) {
    std::ptrdiff_t one_side_offset = two_register_steps * Traits::chunk_size();
    _iteration_two_sides_parallel::less_then_chunk<Traits>(
        f + one_side_offset, l - one_side_offset, delegate);
  } else {
    ++two_register_steps;
  }

  _iteration_two_sides_parallel::main_loop<Traits>(f, l, two_register_steps,
                                                   delegate);
  return delegate;
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ITERATION_TWO_SIDES_H_
