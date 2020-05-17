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
#include "unsq_eve/iteration_main_loop_unrolled.h"
#include "unsq_eve/iteration_traits.h"

#ifndef UNSQ_EVE_ITERATION_UNGUARDED_H_
#define UNSQ_EVE_ITERATION_UNGUARDED_H_

namespace unsq_eve {

template <typename Traits, typename I, typename P>
// require ContigiousIterator<I> &&
//         Predictate<P, wide<ValueType<I, width>>, index_c, ignore>
P iteration_aligned_unguarded(I f, P p) {
  using wide = eve::wide<ValueType<I>, eve::fixed<Traits::width>>;

  auto aligned_f = eve_extra::previous_aligned_address(eve::as_<wide>{}, f);
  using aligned_ptr = decltype(aligned_f);

  // Deal with first bit, maybe not fully in the data
  {
    std::size_t to_ignore = static_cast<std::size_t>(f -  aligned_f.get());
    auto ignore = eve_extra::ignore_first_n { to_ignore };
    if (p(aligned_f, indx_c<0>{}, ignore)) return p;
  }

  // Everything else is on the caller.
  iteration_main_loop_unrolled_unguarded<Traits>(
      aligned_f.get(), [&](auto* cur, auto reg_idx) mutable {
        return p(aligned_ptr(cur), reg_idx, eve_extra::ignore_nothing{});
      });

  return p;
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ITERATION_UNGUARDED_H_
