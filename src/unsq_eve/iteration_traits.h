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

#ifndef UNSQ_EVE_ITERATION_TRAITS_H_
#define UNSQ_EVE_ITERATION_TRAITS_H_

#include <iterator>

namespace unsq_eve {

template <std::size_t i>
using indx_c = std::integral_constant<std::size_t, i>;

template <std::size_t _width, std::size_t _unroll>
struct iteration_traits {
  static constexpr indx_c<_width> width;
  static constexpr indx_c<_unroll> unroll;
};

template <typename I>
using ValueType = typename std::iterator_traits<I>::value_type;

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ITERATION_TRAITS_H_
