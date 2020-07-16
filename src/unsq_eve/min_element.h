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
#include <iostream>

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

  I best_f;
  wide best;

  I base_f;

  std::array<wide, Traits::unroll()> regs;
  std::array<wide_idx, Traits::unroll()> idxs;

  min_body(I f, Selection sel) : sel{sel}, best_f(f), best{*f} {
    regs.fill(best);
  }

  void set_base(I base) {
    base_f = base;
    // std::cout << "New base_f - best_f: " << base_f - best_f << std::endl;
  }

  template <typename Ptr, std::size_t reg_idx, typename Ignore>
  EVE_FORCEINLINE bool step(Ptr from, indx_c<reg_idx>, wide_idx wide_i,
                            Ignore ignore) {
    // std::cout << "from.get() - best_f: " << from.get() - best_f << std::endl;

    wide_read read;

    if constexpr (std::is_same_v<Ignore, eve_extra::ignore_nothing>) {
      read = wide_read{from};
    } else {
      read = eve_extra::load_unsafe(from, eve::as_<wide_read>{});
    }

    wide xs = eve::convert(read, eve::as_<T>{});
    xs = eve_extra::replace_ignored(xs, ignore, regs[reg_idx]);
    // std::cout << "xs:     " << xs << std::endl;
    // std::cout << "wide_i: " << wide_i << std::endl;

    wide mins = sel(regs[reg_idx], xs);

    idxs[reg_idx] = eve::if_else(regs[reg_idx] == mins, idxs[reg_idx], wide_i);
    regs[reg_idx] = mins;

    return false;
  }

  template <typename Ptr, typename Ignore>
  EVE_FORCEINLINE bool small_step(Ptr from, wide_idx wide_i, Ignore ignore) {
    return step(from, indx_c<0>{}, wide_i, ignore);
  }

  EVE_FORCEINLINE void index_overflow() {
    // std::cout << "base_f - best_f: " << base_f - best_f << std::endl;

    wide combined = eve_extra::segment_reduction(regs, sel);
    combined = sel(best, combined);

    // std::cout << "Previous best: " << best << std::endl;
    // std::cout << "Combined by element: " << combined << std::endl;

    if (eve::all(combined == best)) return;

    best = eve_extra::reduce_wide(combined, sel);

    const wide_idx max_idx{std::numeric_limits<index_t<Traits>>::max()};

    for (std::size_t i = 0; i != Traits::unroll(); ++i) {
      idxs[i] = eve::if_else(best == regs[i], idxs[i], max_idx);
    }

    wide_idx res_idx = eve_extra::segment_reduction(idxs, eve::min);
    res_idx = eve_extra::reduce_wide(res_idx, eve::min);

    best_f = base_f + res_idx.back();

    // std::cout << "best: " << best << std::endl;
    // std::cout << "combined idx: " << res_idx << std::endl;
  }

  void before_big_steps() {}

  template <typename Ptr>
  void start_big_step(Ptr) {}

  template <typename Ptr, std::size_t reg_idx>
  EVE_FORCEINLINE bool big_step(Ptr ptr, indx_c<reg_idx> reg_i,
                                wide_idx wide_i) {
    return step(ptr, reg_i, wide_i, eve_extra::ignore_nothing{});
  }

  template <typename Ptr>
  bool complete_big_step(Ptr) {
    return false;
  }

  void after_big_steps() {}

  EVE_FORCEINLINE I compute_result() {
    // std::cout << "compute result" << std::endl;
    index_overflow();
    return best_f;
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
