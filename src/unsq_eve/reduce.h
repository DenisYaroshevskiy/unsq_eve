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

#ifndef UNSQ_EVE_REDUCE_H_
#define UNSQ_EVE_REDUCE_H_

#include <eve/function/add.hpp>

#include "unsq_eve/concepts.h"
#include "unsq_eve/transform_reduce.h"

namespace unsq_eve {

template <typename Traits, contigious_iterator I,
          std::convertible_to<value_type<I>> T, typename F>
std::common_type_t<T, value_type<I>> reduce(I f, I l, const T& zero, F op) {
  return unsq_eve::transform_reduce<Traits>(f, l, zero, op,
                                            [](const auto& xs) { return xs; });
}

template <typename Traits, contigious_iterator I,
          std::convertible_to<value_type<I>> T>
std::common_type_t<T, value_type<I>> reduce(I f, I l, const T& zero) {
  return unsq_eve::reduce<Traits>(f, l, zero, eve::add);
}

template <typename Traits, contigious_iterator I>
value_type<I> reduce(I f, I l) {
  return unsq_eve::reduce<Traits>(f, l, value_type<I>{});
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_REDUCE_H_
