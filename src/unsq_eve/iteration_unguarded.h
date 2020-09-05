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

#include "unsq_eve/iteration_traits.h"
#include "unsq_eve/unroll.h"

#ifndef UNSQ_EVE_ITERATION_UNGUARDED_H_
#define UNSQ_EVE_ITERATION_UNGUARDED_H_

namespace unsq_eve {

template <typename Traits, typename T, typename Delegate>
// require IterationAlignedDelegate<P>
EVE_FORCEINLINE Delegate iteration_aligned_unguarded(T* f, Delegate delegate) {
  auto aligned_f = Traits::previous_aligned_address(f);

  // Deal with first bit, maybe not fully in the data
  {
    eve::ignore_first_ ignore(f - aligned_f.get());
    if (delegate.small_step(aligned_f, indx_c<0>{}, ignore)) return delegate;
  }
  aligned_f += Traits::chunk_size();

  // Everything else is on the caller.
  unroll_iteration<Traits>(aligned_f, [&](auto cur, auto reg_idx) mutable {
    return delegate.small_step(cur, reg_idx, eve::ignore_none);
  });

  return delegate;
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ITERATION_UNGUARDED_H_
