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

#include "eve_extra/eve_extra.h"
#include "unsq_eve/iteration_traits.h"
#include "unsq_eve/unroll.h"

#ifndef UNSQ_EVE_ITERATION_GUARDED_H_
#define UNSQ_EVE_ITERATION_GUARDED_H_

namespace unsq_eve {
namespace _iteration_guarded {

template <typename Traits, typename Ptr, typename Delegate>
StopReason main_loop(Ptr aligned_f, Ptr aligned_l,
                     Delegate& delegate) requires(Traits::unroll() == 1) {
  while (aligned_f.get() != aligned_l.get()) {
    if (delegate.small_step(aligned_f, indx_c<0>{},
                            eve_extra::ignore_nothing{}))
      return StopReason::Terminated;
    aligned_f += Traits::width();
  }
  return StopReason::No;
}

template <typename Traits, typename Ptr, typename Delegate>
StopReason main_loop(Ptr aligned_f, Ptr aligned_l,
                     Delegate& delegate) /*requires(Traits::unroll() > 1)*/ {
  while (true) {  // To the beginning at most twice
    // initialize every register with small steps
    // (also can help for smaller range size)
    // (also reusable for when not enough for big step)
    StopReason res = unroll<Traits::unroll()>([&](auto idx) mutable {
      if (aligned_f.get() == aligned_l.get()) return StopReason::EndReached;

      if (delegate.small_step(aligned_f, idx, eve_extra::ignore_nothing{}))
        return StopReason::Terminated;

      aligned_f += Traits::width();
      return StopReason::No;
    });

    if (res != StopReason::No) return res;

    static constexpr std::ptrdiff_t big_step =
        Traits::width() * Traits::unroll();

    std::ptrdiff_t big_steps_count =
        (aligned_l.get() - aligned_f.get()) / big_step;
    if (!big_steps_count) continue;

    delegate.before_big_steps();

    do {
      delegate.start_big_step();

      res = unroll<Traits::unroll()>([&](auto idx) mutable {
        Ptr offset_ptr{aligned_f + Traits::width() * idx};
        if (delegate.big_step(offset_ptr, idx)) return StopReason::Terminated;
        return StopReason::No;
      });

      if (res != StopReason::No) return res;

      if (delegate.complete_big_step()) return StopReason::Terminated;

      aligned_f += big_step;
      --big_steps_count;
    } while (big_steps_count);

    delegate.after_big_steps();
  }
}

}  //  namespace _iteration_guarded

template <typename Traits, typename T, typename Delegate>
// require ContigiousIterator<I> && IterationAlignedDelegate<P>
Delegate iteration_aligned(T* f, T* l, Delegate delegate) {
  using wide = eve::wide<ValueType<T*>, eve::fixed<Traits::width()>>;

  auto aligned_f = eve_extra::previous_aligned_address(eve::as_<wide>{}, f);
  auto aligned_l = eve_extra::previous_aligned_address(eve::as_<wide>{}, l);

  eve_extra::ignore_first_n ignore_first{
      static_cast<std::size_t>(f - aligned_f.get())};

  if (aligned_f.get() != aligned_l.get()) {
    // first chunk, maybe partial
    if (delegate.small_step(aligned_f, indx_c<0>{}, ignore_first))
      return delegate;
    ignore_first = eve_extra::ignore_first_n{0};
    aligned_f += Traits::width();

    StopReason stop =
        _iteration_guarded::main_loop<Traits>(aligned_f, aligned_l, delegate);

    if (stop == StopReason::Terminated || aligned_l.get() == l) return delegate;
  }

  const std::ptrdiff_t last_offset = aligned_l.get() + Traits::width() - l;

  eve_extra::ignore_last_n ignore_last{static_cast<std::size_t>(last_offset)};
  delegate.small_step(aligned_l, indx_c<0>{},
                      eve_extra::combine(ignore_first, ignore_last));
  return delegate;
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ITERATION_GUARDED_H_
