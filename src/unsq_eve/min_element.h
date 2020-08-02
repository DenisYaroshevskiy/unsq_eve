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

#ifndef UNSQ_EVE_MIN_ELEMENT_H_
#define UNSQ_EVE_MIN_ELEMENT_H_

#include <array>

#include <eve/function/all.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/min.hpp>

#include "eve_extra/eve_extra.h"
#include "unsq_eve/concepts.h"
#include "unsq_eve/iteration_indexed_guarded.h"

namespace unsq_eve {
namespace _min_element {

template <typename Traits, typename I, typename Selection>
struct min_body {
  using T = typename Traits::type;
  using wide_read = eve::wide<value_type<I>, width_t<Traits>>;
  using wide = typename Traits::wide;
  using logical = eve::logical<wide>;
  using wide_idx = wide_index_t<iteration_traits_t<Traits>>;

  Selection sel;

  I best_base;
  wide_idx best_idx;
  wide best;

  I base;

  std::array<wide, Traits::unroll()> regs;
  std::array<wide_idx, Traits::unroll()> idxs;

  min_body(I f, Selection sel)
      : sel{sel}, best_base(f), best_idx{0u}, best{*f} {
    regs.fill(best);
    // idxs are deliberetly unitialized since I'm not going to
    // apply their value if it's not actually less.
  }

  void set_base(I _base) { base = _base; }

  template <typename Ptr, std::size_t reg_idx, typename Ignore>
  EVE_FORCEINLINE bool small_step(Ptr from, indx_c<reg_idx>, wide_idx wide_i,
                                  Ignore ignore) {
    wide_read read;

    if constexpr (std::is_same_v<Ignore, eve_extra::ignore_none_t>) {
      read = wide_read{from};
    } else {
      read = eve_extra::load_unsafe(from, eve::as_<wide_read>{});
    }

    wide xs = eve::convert(read, eve::as_<T>{});
    xs = eve_extra::replace_ignored(xs, ignore, regs[reg_idx]);

    wide mins = sel(regs[reg_idx], xs);

    idxs[reg_idx] = eve::if_else(regs[reg_idx] == mins, idxs[reg_idx], wide_i);
    regs[reg_idx] = mins;

    return false;
  }

  EVE_FORCEINLINE void index_overflow() {
    wide combined = eve_extra::segment_reduction(regs, sel);
    combined = sel(best, combined);

    if (eve::all(combined == best)) return;

    best = eve_extra::reduce_wide(combined, sel);

    const wide_idx max_idx{std::numeric_limits<index_t<Traits>>::max()};

    for (std::size_t i = 0; i != Traits::unroll(); ++i) {
      idxs[i] = eve::if_else(best == regs[i], idxs[i], max_idx);
    }

    best_base = base;
    best_idx = eve_extra::segment_reduction(idxs, eve::min);
  }

  void before_big_steps() {}

  template <typename Ptr>
  void start_big_step(Ptr) {}

  template <typename Ptr, std::size_t reg_idx>
  EVE_FORCEINLINE bool big_step(Ptr ptr, indx_c<reg_idx> reg_i,
                                wide_idx wide_i) {
    return small_step(ptr, reg_i, wide_i, eve::ignore_none);
  }

  template <typename Ptr>
  bool complete_big_step(Ptr) {
    return false;
  }

  void after_big_steps() {}

  EVE_FORCEINLINE I compute_result() {
    index_overflow();
    best_idx = eve_extra::reduce_wide(best_idx, eve::min);
    return best_base + best_idx.front();
  }
};

}  // namespace _min_element

template <typename Traits, contigious_iterator I,
          wide_selection_for<Traits> Selection>
EVE_FORCEINLINE I min_element(I _f, I _l, Selection sel) {
  if (_f == _l) return _f;

  auto [f, l] = drill_down_range(_f, _l);

  _min_element::min_body<Traits, Pointer<I>, Selection> body(f, sel);
  body = iteration_indexed_aligned<iteration_traits_t<Traits>>(f, l, body);

  return undo_drill_down(_f, body.compute_result());
}

template <typename Traits, contigious_iterator I>
EVE_FORCEINLINE I min_element(I f, I l) {
  return min_element<Traits>(f, l, eve::min);
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_MIN_ELEMENT_H_
