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

#ifndef UNSQ_EVE_ITERATION_GUARDED_UNALIGNED_H_
#define UNSQ_EVE_ITERATION_GUARDED_UNALIGNED_H_

#include "eve_extra/eve_extra.h"
#include "unsq_eve/iteration_traits.h"
#include "unsq_eve/unroll.h"

#include <iostream>

namespace unsq_eve {
namespace _iteration_guarded_unaligned {

template <typename Traits, typename T, typename Delegate>
EVE_FORCEINLINE StopReason
main_loop(T*& f, T* l, Delegate& delegate) requires(Traits::unroll() == 1) {
  while ((l - f) >= static_cast<std::ptrdiff_t>(Traits::chunk_size())) {
    if (delegate.small_step(f, indx_c<0>{}, eve_extra::ignore_nothing{}))
      return StopReason::Terminated;
    f += Traits::chunk_size();
  }
  return StopReason::No;
}  // namespace _iteration_guarded_unaligned

template <typename Traits, typename T, typename Delegate>
EVE_FORCEINLINE StopReason main_loop(T*& f, T* l, Delegate& delegate) {
  while (true) {  // To the beginning at most twice
    // initialize every register with small steps
    // (also can help for smaller range size)
    // (also reusable for when not enough for big step)
    StopReason res = unroll<Traits::unroll()>([&](auto idx) mutable {
      if ((l - f) < static_cast<std::ptrdiff_t>(Traits::chunk_size()))
        return StopReason::EndReached;

      if (delegate.small_step(f, idx, eve_extra::ignore_nothing{}))
        return StopReason::Terminated;

      f += Traits::chunk_size();
      return StopReason::No;
    });

    if (res != StopReason::No) return res;

    static constexpr std::ptrdiff_t big_step =
        Traits::chunk_size() * Traits::unroll();

    std::ptrdiff_t big_steps_count = (l - f) / big_step;
    if (!big_steps_count) continue;

    delegate.before_big_steps();

    do {
      delegate.start_big_step(f);

      res = unroll<Traits::unroll()>([&](auto idx) mutable {
        T* offset_ptr{f + Traits::chunk_size() * idx};
        if (delegate.big_step(offset_ptr, idx)) return StopReason::Terminated;
        return StopReason::No;
      });

      if (res != StopReason::No) return res;

      if (delegate.complete_big_step(f)) return StopReason::Terminated;

      f += big_step;
      --big_steps_count;
    } while (big_steps_count);

    delegate.after_big_steps();
  }
}

}  // namespace _iteration_guarded_unaligned

template <typename Traits, typename T, typename Delegate>
// require IterationUnlignedDelegate<P>
EVE_FORCEINLINE Delegate iteration_unaligned(T* f, T* l, Delegate delegate) {
  StopReason stop =
      _iteration_guarded_unaligned::main_loop<Traits>(f, l, delegate);
  if (stop == StopReason::Terminated || f == l) return delegate;

  T* page_boundary = eve_extra::end_of_page(f);
  if (page_boundary - f < static_cast<std::ptrdiff_t>(Traits::chunk_size())) {
    T* safe = l - Traits::chunk_size();
    eve_extra::ignore_first_n ignore{static_cast<std::size_t>(f - safe)};
    delegate.small_step(safe, indx_c<0>{}, ignore);
    return delegate;
  }

  eve_extra::ignore_last_n ignore{
      static_cast<std::size_t>(f + Traits::chunk_size() - l)};
  delegate.small_step(f, indx_c<0>{}, ignore);
  return delegate;
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ITERATION_GUARDED_UNALIGNED_H_
