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

#ifndef UNSQ_EVE_ITERATION_TWO_SIDES_H_
#define UNSQ_EVE_ITERATION_TWO_SIDES_H_

#include <algorithm>

#include "eve_extra/eve_extra.h"
#include "unsq_eve/iteration_traits.h"

namespace _iteration_two_sides_parallel {

template <typename Traits, typename T, typename Delegate>
EVE_FORCEINLINE Delegate less_then_chunk(T* f, T* l, Delegate delegate) {
  if (eve_extra::end_of_page(f) - f < static_cast<int>(Traits::chunk_size())) {
    T* read_from = l - Traits::chunk_size();
    delegate.small_array_step(read_from, eve::ignore_first_{f - read_from});
    return delegate;
  }
  delegate.small_array_step(f, eve::ignore_last_{f + Traits::chunk_size() - l});
  return delegate;
}

}  // namespace _iteration_two_sides_parallel

template <typename Traits, typename T, typename Delegate>
// require IterationTwoSidesParallelDelegate<Delegate>
EVE_FORCEINLINE Delegate iteration_two_sides_parallel(T* f, T* l,
                                                      Delegate delegate) {
  if (l - f <= static_cast<int>(Traits::chunk_size())) {
    return _iteration_two_sides_parallel::less_then_chunk<Traits>(f, l,
                                                                  delegate);
  }

  while (true) {
    l -= Traits::chunk_size();
    delegate.small_step(f, l);
    f += Traits::chunk_size();
    if (f > l) break;
  }

  return delegate;
}

#endif  // UNSQ_EVE_ITERATION_TWO_SIDES_H_
