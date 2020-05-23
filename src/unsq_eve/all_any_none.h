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

#ifndef UNSQ_EVE_ALL_ANY_NONE_H_
#define UNSQ_EVE_ALL_ANY_NONE_H_

#include "eve_extra/eve_extra.h"

#include "unsq_eve/iteration_unguarded.h"

namespace unsq_eve {
namespace _all_any_none {

}  // namespace _all_any_none

template <typename Traits, typename I, typename PV>
// require ContigiousIterator<I> && VectorPredicate<PV, ValueType<I>>
bool any_of(I _f, I _l, PV p) {

}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ALL_ANY_NONE_H_
