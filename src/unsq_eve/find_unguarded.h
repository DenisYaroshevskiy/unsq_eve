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

#ifndef UNSQ_EVE_FIND_UNGUARDED_H_
#define UNSQ_EVE_FIND_UNGUARDED_H_

#include <array>

#include "eve_extra/eve_extra.h"

#include "unsq_eve/iteration_unguarded.h"
#include "unsq_eve/predicate_helpers.h"

namespace unsq_eve {
namespace _find_unguarded {

template <typename Traits, typename StrippedI, typename PV>
// require ContigiousIterator<I> && VectorPredicate<PV, ValueType<I>>
struct find_if_body {
  using wide = eve::wide<ValueType<StrippedI>, width_t<Traits>>;

  PV p;
  StrippedI found;

  std::array<wide, Traits::unroll()> regs;

  find_if_body(PV p, StrippedI found) : p(p), found(found) {}

  template <typename Ptr, std::size_t idx, typename Ignore>
  bool operator()(Ptr from, indx_c<idx>, Ignore ignore) {
    regs[idx] = eve_extra::load_unsafe(from, eve::as_<wide>{});

    const std::optional match = first_true(p(regs[idx]), ignore);
    if (!match) return false;

    found = &*from + *match;
    return true;
  }
};

}  // namespace _find_unguarded

template <typename Traits, typename I, typename PV>
// require ContigiousIterator<I> && VectorPredicate<PV, ValueType<I>>
I find_if_unguarded(I _f, PV p) {
  auto* f = drill_down(_f);

  _find_unguarded::find_if_body<Traits, decltype(f), PV> body{p, f};
  auto* found = iteration_aligned_unguarded<Traits>(f, body).found;

  return undo_drill_down(_f, found);
}

template <typename Traits, typename I, typename T>
// require ContigiousIterator<I> && Convertible<T, ValueType<P>>
I find_unguarded(I f, const T& x) {
  return unsq_eve::find_if_unguarded<Traits>(f, equal_to<Traits, I>(x));
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_FIND_UNGUARDED_H_
