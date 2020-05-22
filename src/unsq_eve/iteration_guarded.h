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

#ifndef UNSQ_EVE_ITERATION_GUARDED_H_
#define UNSQ_EVE_ITERATION_GUARDED_H_

namespace unsq_eve {

template <typename Traits, typename T, typename P>
// require ContigiousIterator<I> &&
//         Predictate<P, wide<ValueType<I, width>>, index_c, ignore>
P iteration_aligned(T* f, T* l, P p) {
  using wide = eve::wide<ValueType<T*>, eve::fixed<Traits::width>>;

}

}  // namespace unsq_eve


#endif  // UNSQ_EVE_ITERATION_GUARDED_H_
