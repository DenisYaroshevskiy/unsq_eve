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
#include "unsq_eve/unroll.h"
#include "unsq_eve/iteration_traits.h"

#ifndef UNSQ_EVE_ITERATION_UNGUARDED_H_
#define UNSQ_EVE_ITERATION_UNGUARDED_H_

namespace unsq_eve {

template <typename Traits, typename T, typename Delegate>
// require IterationAlignedDelegate<P>
Delegate iteration_aligned_unguarded(T* f, Delegate delegate) {
  using wide = eve::wide<value_type<T*>, width_t<Traits>>;

  auto aligned_f = eve_extra::previous_aligned_address(eve::as_<wide>{}, f);

  // Deal with first bit, maybe not fully in the data
  {
    std::size_t to_ignore = static_cast<std::size_t>(f - aligned_f.get());
    auto ignore = eve_extra::ignore_first_n{to_ignore};
    if (delegate.small_step(aligned_f, indx_c<0>{}, ignore)) return delegate;
  }
  aligned_f += Traits::width();

  // Everything else is on the caller.
  unroll_iteration<Traits>(aligned_f, [&](auto cur, auto reg_idx) mutable {
    return delegate.small_step(cur, reg_idx, eve_extra::ignore_nothing{});
  });

  return delegate;
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ITERATION_UNGUARDED_H_
