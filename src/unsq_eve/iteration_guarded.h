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

#ifndef UNSQ_EVE_ITERATION_GUARDED_H_
#define UNSQ_EVE_ITERATION_GUARDED_H_

#include "eve_extra/eve_extra.h"
#include "unsq_eve/iteration_traits.h"
#include "unsq_eve/unroll.h"

namespace unsq_eve {
namespace _iteration_guarded {

template <typename Traits, typename Ptr, typename Delegate>
EVE_FORCEINLINE StopReason
main_loop(Ptr aligned_f, Ptr aligned_l,
          Delegate& delegate) requires(Traits::unroll() == 1) {
  while (aligned_f.get() != aligned_l.get()) {
    if (delegate.small_step(aligned_f, indx_c<0>{}, eve::ignore_none))
      return StopReason::Terminated;
    aligned_f += Traits::chunk_size();
  }
  return StopReason::No;
}

template <typename Traits, typename Ptr, typename Delegate>
EVE_FORCEINLINE StopReason main_loop(Ptr aligned_f, Ptr aligned_l,
                                     Delegate& delegate) {
  while (true) {  // To the beginning at most twice
    // initialize every register with small steps
    // (also can help for smaller range size)
    // (also reusable for when not enough for big step)
    StopReason res = unroll<Traits::unroll()>([&](auto idx) mutable {
      if (aligned_f.get() == aligned_l.get()) return StopReason::EndReached;

      if (delegate.small_step(aligned_f, idx, eve::ignore_none))
        return StopReason::Terminated;

      aligned_f += Traits::chunk_size();
      return StopReason::No;
    });

    if (res != StopReason::No) return res;

    static constexpr std::ptrdiff_t big_step =
        Traits::chunk_size() * Traits::unroll();

    std::ptrdiff_t big_steps_count =
        (aligned_l.get() - aligned_f.get()) / big_step;
    if (!big_steps_count) continue;

    delegate.before_big_steps();

    do {
      delegate.start_big_step(aligned_f);

      res = unroll<Traits::unroll()>([&](auto idx) mutable {
        Ptr offset_ptr{aligned_f + Traits::chunk_size() * idx};
        if (delegate.big_step(offset_ptr, idx)) return StopReason::Terminated;
        return StopReason::No;
      });

      if (res != StopReason::No) return res;

      if (delegate.complete_big_step(aligned_f)) return StopReason::Terminated;

      aligned_f += big_step;
      --big_steps_count;
    } while (big_steps_count);

    delegate.after_big_steps();
  }
}

}  //  namespace _iteration_guarded

template <typename Traits, typename T, typename Delegate>
// require IterationAlignedDelegate<P>
EVE_FORCEINLINE Delegate iteration_aligned(T* f, T* l, Delegate delegate) {
  auto aligned_f = Traits::previous_aligned_address(f);
  auto aligned_l = Traits::previous_aligned_address(l);

  delegate.set_base(aligned_f.get());

  eve::ignore_first_ ignore_first{static_cast<int>(f - aligned_f.get())};

  if (aligned_f.get() != aligned_l.get()) {
    // first chunk, maybe partial
    if (delegate.small_step(aligned_f, indx_c<0>{}, ignore_first))
      return delegate;
    ignore_first = eve::ignore_first_{0};
    aligned_f += Traits::chunk_size();

    StopReason stop =
        _iteration_guarded::main_loop<Traits>(aligned_f, aligned_l, delegate);

    if (stop == StopReason::Terminated || aligned_l.get() == l) return delegate;
  }

  const int last_offset = aligned_l.get() + Traits::chunk_size() - l;

  eve::ignore_last_ ignore_last{last_offset};
  delegate.small_step(aligned_l, indx_c<0>{}, ignore_first && ignore_last);
  return delegate;
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ITERATION_GUARDED_H_
