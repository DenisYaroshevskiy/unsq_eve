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

#ifndef UNSQ_EVE_REMOVE_H_
#define UNSQ_EVE_REMOVE_H_

#include <eve/conditional.hpp>
#include <eve/function/convert.hpp>

#include "eve_extra/eve_extra.h"
#include "unsq_eve/concepts.h"
#include "unsq_eve/iteration_guarded.h"
#include "unsq_eve/predicate_helpers.h"

#include <iostream>

namespace unsq_eve {
namespace _remove {

template <typename Traits, typename I, typename PV>
struct body {
  using T = typename Traits::type;
  using wide_read = eve::wide<value_type<I>, width_t<Traits>>;
  using wide = typename Traits::wide;
  using logical_wide = eve::logical<wide>;
  using logical_wide_read = eve::logical<wide_read>;

  PV p;

  I out;
  std::array<wide, Traits::unroll()> regs;

  explicit body(PV p) : p(p) {}

  void set_base(I base) { out = base; }

  template <typename Ptr, std::size_t idx, typename Ignore>
  EVE_FORCEINLINE bool small_step(Ptr ptr, indx_c<idx>, Ignore ignore) {
    wide_read read;

    if constexpr (std::is_same_v<Ignore, eve_extra::ignore_nothing>) {
      read = wide_read{ptr};
    } else {
      read = eve_extra::load_unsafe(ptr, eve::as_<wide_read>{});
    }

    wide xs = eve::convert(read, eve::as_<T>{});
    const eve::logical<wide> mask = p(xs);
    const eve::logical<wide_read> read_mask =
        eve::convert(mask, eve::as_<typename logical_wide_read::value_type>{});

    out = eve_extra::compress_store_unsafe(read, out, eve::if_not_(read_mask),
                                           ignore);

    return false;
  }

  void before_big_steps() {}

  template <typename Ptr>
  void start_big_step(Ptr) {}

  template <typename Ptr, std::size_t _idx>
  EVE_FORCEINLINE bool big_step(Ptr ptr, indx_c<_idx> idx) {
    return small_step(ptr, idx, eve_extra::ignore_nothing{});
  }

  template <typename Ptr>
  bool complete_big_step(Ptr) {
    return false;
  }

  void after_big_steps() {}
};

}  // namespace _remove

template <typename Traits, contigious_iterator I, wide_predicate_for<Traits> PV>
EVE_FORCEINLINE I remove_if(I _f, I _l, PV p) {
  if (_f == _l) return _f;

  auto [f, l] = drill_down_range(_f, _l);

  _remove::body<Traits, Pointer<I>, PV> body{p};
  Pointer<I> out =
      iteration_aligned<iteration_traits_t<Traits>>(f, l, body).out;

  return undo_drill_down(_f, out);
}

template <typename Traits, contigious_iterator I,
          std::convertible_to<value_type<I>> T>
EVE_FORCEINLINE I remove(I f, I l, const T& x) {
  return unsq_eve::remove_if<Traits>(f, l, equal_to<Traits, I>(x));
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_REMOVE_H_
