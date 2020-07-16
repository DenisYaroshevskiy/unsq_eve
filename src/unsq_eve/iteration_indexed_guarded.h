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

#ifndef UNSQ_EVE_ITERATION_INDEXED_GUARDED_H_
#define UNSQ_EVE_ITERATION_INDEXED_GUARDED_H_

#include <limits>

#include "eve_extra/eve_extra.h"
#include "unsq_eve/iteration_traits.h"
#include "unsq_eve/unroll.h"

namespace unsq_eve {
namespace _iteration_indexed_guarded {

template <typename Traits>
constexpr std::ptrdiff_t max_idx() {
  return std::numeric_limits<index_t<Traits>>::max();
}

template <typename Traits>
constexpr std::ptrdiff_t big_step() {
  return Traits::chunk_size() * Traits::unroll();
}

template <typename Traits>
auto wide_step() {
  return wide_index_t<Traits>{Traits::chunk_size()};
}

template <typename Traits>
auto wide_big_step() {
  return wide_index_t<Traits>{big_step<Traits>()};
}

template <typename Traits>
auto wider_iota() {
  std::array<wide_index_t<Traits>, Traits::unroll()> res;

  auto cur = eve_extra::iota(eve::as_<wide_index_t<Traits>>{});

  for (auto& i : res) {
    i = cur;
    cur += wide_step<Traits>();
  }

  return res;
}

template <typename Traits, typename Ptr, typename Delegate>
EVE_FORCEINLINE StopReason
main_loop(Ptr& aligned_f, Ptr aligned_l, wide_index_t<Traits>& wide_i,
          Delegate& delegate) requires(Traits::unroll() == 1) {
  std::ptrdiff_t n = max_idx<Traits>() - Traits::chunk_size();

  const auto step = wide_step<Traits>();

  while (aligned_f != aligned_l) {
    n = std::min(n, aligned_l.get() - aligned_f.get());
    auto* end = aligned_f.get() + n;

    while (aligned_f.get() < end) {
      if (delegate.small_step(aligned_f, indx_c<0>{}, wide_i,
                              eve_extra::ignore_nothing{})) {
        return StopReason::Terminated;
      }
      wide_i += step;
      aligned_f += Traits::chunk_size();
    }

    delegate.index_overflow();
    delegate.set_base(aligned_f.get());
    n = max_idx<Traits>();
    wide_i = eve_extra::iota(eve::as_<wide_index_t<Traits>>{});
  }

  return StopReason::No;
}

template <typename Traits, typename Ptr, typename Delegate>
EVE_FORCEINLINE StopReason main_loop_unrolled(Ptr& aligned_f, Ptr aligned_l,
                                              Delegate& delegate) {
  while (true) {
    delegate.index_overflow();
    delegate.set_base(aligned_f.get());

    std::ptrdiff_t n =
        std::min(aligned_l.get() - aligned_f.get(), max_idx<Traits>());
    n /= big_step<Traits>();

    if (n == 0) return StopReason::No;

    auto wider_i = wider_iota<Traits>();

    delegate.before_big_steps();

    do {
      delegate.start_big_step(aligned_f);

      StopReason res = unroll<Traits::unroll()>([&](auto idx) mutable {
        Ptr offset_ptr{aligned_f + Traits::chunk_size() * idx};

        if (delegate.big_step(offset_ptr, idx, wider_i[idx]))
          return StopReason::Terminated;
        wider_i[idx] += wide_big_step<Traits>();

        return StopReason::No;
      });

      if (res != StopReason::No) return res;
      if (delegate.complete_big_step(aligned_f)) return StopReason::Terminated;

      aligned_f += big_step<Traits>();
    } while (--n);

    delegate.after_big_steps();
  }
}

template <typename Traits, typename Ptr, typename Delegate>
EVE_FORCEINLINE StopReason main_loop(Ptr& aligned_f, Ptr aligned_l,
                                     wide_index_t<Traits>& wide_i,
                                     Delegate& delegate) {
  static_assert((Traits::unroll() + 1) * Traits::chunk_size() <=
                max_idx<Traits>());

  while (true) {  // To the beginning at most twice
    StopReason res = unroll<Traits::unroll()>([&](auto reg_idx) mutable {
      if (aligned_f.get() == aligned_l.get()) return StopReason::EndReached;

      if (delegate.small_step(aligned_f, reg_idx, wide_i,
                              eve_extra::ignore_nothing{}))
        return StopReason::Terminated;

      aligned_f += Traits::chunk_size();
      wide_i += wide_step<Traits>();
      return StopReason::No;
    });

    if (res != StopReason::No) return res;
    res = main_loop_unrolled<Traits>(aligned_f, aligned_l, delegate);
    if (res != StopReason::No) return res;

    wide_i = eve_extra::iota(eve::as_<wide_index_t<Traits>>{});
  }
}

}  // namespace _iteration_indexed_guarded

template <typename Traits, typename T, typename Delegate>
EVE_FORCEINLINE Delegate iteration_indexed_aligned(T* f, T* l,
                                                   Delegate delegate) {
  using idx_t = wide_index_t<Traits>;

  auto aligned_f = Traits::previous_aligned_address(f);
  auto aligned_l = Traits::previous_aligned_address(l);

  eve_extra::ignore_first_n ignore_first{
      static_cast<std::size_t>(f - aligned_f.get())};

  delegate.set_base(aligned_f.get());

  idx_t wide_i = eve_extra::iota(eve::as_<idx_t>{});

  if (aligned_f != aligned_l) {
    if (delegate.small_step(aligned_f, indx_c<0>{}, wide_i, ignore_first))
      return delegate;

    ignore_first = eve_extra::ignore_first_n{0};
    aligned_f += Traits::chunk_size();
    wide_i += _iteration_indexed_guarded::wide_step<Traits>();

    StopReason stop = _iteration_indexed_guarded::main_loop<Traits>(
        aligned_f, aligned_l, wide_i, delegate);

    if (stop == StopReason::Terminated || aligned_l.get() == l) return delegate;
  }

  const std::ptrdiff_t last_offset = aligned_l.get() + Traits::chunk_size() - l;

  eve_extra::ignore_last_n ignore_last{static_cast<std::size_t>(last_offset)};
  delegate.small_step(aligned_l, indx_c<0>{}, wide_i,
                      eve_extra::combine(ignore_first, ignore_last));
  return delegate;
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ITERATION_INDEXED_GUARDED_H_
