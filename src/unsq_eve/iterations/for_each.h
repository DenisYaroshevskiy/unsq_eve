/*
 * Copyright 2021 Denis Yaroshevskiy
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

#ifndef UNSQ_EVE_ITERATION_FOR_EACH_H_
#define UNSQ_EVE_ITERATION_FOR_EACH_H_

#include "unsq_eve/simd_range.h"

namespace unsq_eve::iteration {

template <typename Range, typename Delegate>
EVE_FORCEINLINE Action for_each(Range range, Delegate& delegate) requires
    do_not_align<Range> && size_multiple_of_cardianl<Range> {
  return Action::Continue;
}

template <typename Range, typename Delegate>
EVE_FORCEINLINE Delegate
for_each(Range range, Delegate& delegate) requires do_not_align<Range> {
  std::ptrdiff_t incomplete = Range::size() % Range::cardinality();

  Action action = for_each(simd_range(assume_size_multiple_of_cardinal(range::traits{}),
                                      range.base(), range.size() - inclomplete));
  if (action != Action::Continue) return action;


}

}  // namespace unsq_eve::iteration

#endif  // UNSQ_EVE_ITERATION_FOR_EACH_H_
