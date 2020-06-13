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

#ifndef ITERATION_ONE_RANGE_ALIGNED_STORES_H_
#define ITERATION_ONE_RANGE_ALIGNED_STORES_H_

#include "eve_extra/eve_extra.h"
#include "unsq_eve/iteration_traits.h"
#include "unsq_eve/unroll.h"

namespace unsq_eve {
namespace _iteration_one_range_aligned_stores {

// [f  |  l]  => Ok from f, Ok from l - width
// [|f  l] => Ok from f, Not Ok from l - width
// [f, l|] => Not ok from f, Ok from l - width
template <typename Traits, typename T, typename Delegate>
Delegate under_chunk_size(T* f, T* l, Delegate delegate) {
  using wide = eve::wide<T, eve::fixed<Traits::chunk_size()>>;

  T* page_boundary = eve_extra::end_of_page(f);

  if (page_boundary - f < static_cast<std::ptrdiff_t>(Traits::chunk_size())) {
    T* safe = l - Traits::chunk_size();
    eve_extra::ignore_first_n ignore{static_cast<std::size_t>(f - safe)};

    auto loaded = eve_extra::load_unsafe(safe, eve::as_<wide>{});

    delegate.under_chunk_size_step(safe, indx_c<0>{}, loaded, ignore);
    return delegate;
  }

  auto loaded = eve_extra::load_unsafe(f, eve::as_<wide>{});
  eve_extra::ignore_last_n ignore{
      static_cast<std::size_t>(f + Traits::chunk_size() - l)};

  delegate.under_chunk_size_step(f, indx_c<0>{}, loaded, ignore);
  return delegate;
}

template <typename Traits, typename Ptr, typename Wide, typename Delegate>
StopReason main_loop(Ptr aligned_f, Ptr aligned_l, Wide& cur,
                     Delegate& delegate) requires(Traits::unroll() == 1) {
  using wide = Wide;

  while (aligned_f != aligned_l) {
    if (delegate.small_step(aligned_f, cur, indx_c<0>{},
                            eve_extra::ignore_nothing{}))
      return StopReason::Terminated;

    aligned_f += Traits::chunk_size();
    cur = wide{aligned_f};
  }

  return StopReason::No;
}

template <typename Traits, typename Ptr, typename Wide, typename Delegate>
StopReason main_loop(Ptr aligned_f, Ptr aligned_l, Wide& cur,
                     Delegate& delegate) {
  using wide = Wide;

  while (true) {  // To the beginning at most twice
    // initialize every register with small steps
    // (also can help for smaller range size)
    // (also reusable for when not enough for big step)

    // Special unroll for preloaded cur.
    if (aligned_f == aligned_l) return StopReason::EndReached;
    if (delegate.small_step(aligned_f, cur, indx_c<0>{},
                            eve_extra::ignore_nothing{}))
      return StopReason::Terminated;
    aligned_f += Traits::chunk_size();

    StopReason res =
        unroll<Traits::unroll() - 1>([&]<std::size_t idx>(indx_c<idx>) mutable {
          cur = wide{aligned_f};
          if (aligned_f.get() == aligned_l.get()) return StopReason::EndReached;

          if (delegate.small_step(aligned_f, cur, indx_c<idx - 1>{},
                                  eve_extra::ignore_nothing{}))
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
        cur = wide{offset_ptr};
        if (delegate.big_step(offset_ptr, cur, idx))
          return StopReason::Terminated;
        return StopReason::No;
      });

      if (res != StopReason::No) return res;

      if (delegate.complete_big_step(aligned_f)) return StopReason::Terminated;

      aligned_f += big_step;
      --big_steps_count;
    } while (big_steps_count);

    delegate.after_big_steps();
    cur = wide{aligned_f};
  }
}

}  // namespace _iteration_one_range_aligned_stores

template <typename Traits, typename T, typename Delegate>
Delegate iteration_one_range_aligned_stores(T* f, T* l, Delegate delegate) {
  using wide = eve::wide<T, eve::fixed<Traits::chunk_size()>>;

  if (l - f < static_cast<std::ptrdiff_t>(Traits::chunk_size())) {
    return _iteration_one_range_aligned_stores::under_chunk_size<Traits>(
        f, l, delegate);
  }

  wide cur{f};

  // At least one full chunk that's not intersecting with first or last chunk
  // [f |    |  l)
  if (l - f > static_cast<std::ptrdiff_t>(Traits::chunk_size() * 2)) {
    auto aligned_f = Traits::previous_aligned_address(f + Traits::chunk_size());
    auto aligned_l = Traits::previous_aligned_address(l) - Traits::chunk_size();

    wide next{aligned_f};

    eve_extra::ignore_last_n ignore{
        static_cast<std::size_t>(f + Traits::chunk_size() - aligned_f.get())};
    if (delegate.small_step(f, cur, indx_c<0>{}, ignore)) return delegate;

    cur = next;

    StopReason stop = _iteration_one_range_aligned_stores::main_loop<Traits>(
        aligned_f, aligned_l, cur, delegate);

    if (stop == StopReason::Terminated) return delegate;

    f = aligned_l.get();
  }

  T* load_last_from = l - Traits::chunk_size();
  wide next{load_last_from};

  eve_extra::ignore_last_n ignore{static_cast<std::size_t>(load_last_from - f)};
  if (delegate.small_step(f, cur, indx_c<0>{}, ignore)) return delegate;

  delegate.small_step(load_last_from, next, indx_c<0>{},
                      eve_extra::ignore_nothing{});
  return delegate;
}

}  // namespace unsq_eve

#endif  // ITERATION_ONE_RANGE_ALIGNED_STORES_H_
