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

template <typename Traits, typename T, typename P>
// require ContigiousIterator<I> && IterationAlignedDelegate<P>
P iteration_aligned(T* f, T* l, P p) {
  using wide = eve::wide<ValueType<T*>, eve::fixed<Traits::width()>>;
  using extra_wide =
      eve::wide<ValueType<T*>, eve::fixed<Traits::width() * Traits::unroll()>>;

  auto aligned_f = eve_extra::previous_aligned_address(eve::as_<wide>{}, f);
  auto aligned_l = eve_extra::previous_aligned_address(eve::as_<wide>{}, l);

  // Deal with first bit, maybe not fully in the data
  eve_extra::ignore_first_n ignore_first{
      static_cast<std::size_t>(f - aligned_f.get())};

  if (aligned_f.get() != aligned_l.get()) {
    if (p.small_step(aligned_f, ignore_first)) return p;
    ignore_first = eve_extra::ignore_first_n{0};
    aligned_f += Traits::width();

    std::ptrdiff_t unrolled_steps =
        (aligned_l.get() - aligned_f.get()) / extra_wide::static_size;

    while (unrolled_steps) {
      if (p.big_step(aligned_f, eve_extra::ignore_nothing{})) return p;
      --unrolled_steps;
      aligned_f += extra_wide::static_size;
    }

    while (aligned_f.get() != aligned_l.get()) {
      p.small_step(aligned_f, eve_extra::ignore_nothing{});
      aligned_f += Traits::width();
    }

    if (aligned_l.get() == l) return p;
  }

  eve_extra::ignore_last_n ignore_last{
      static_cast<std::size_t>(aligned_l.get() + Traits::width() - l)};
  p.small_step(aligned_l, eve_extra::combine(ignore_first, ignore_last));
  return p;
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ITERATION_GUARDED_H_
