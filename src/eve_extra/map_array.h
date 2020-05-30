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

#ifndef EVE_EXTRA_UNROLL_H_
#define EVE_EXTRA_UNROLL_H_

#include <array>
#include <type_traits>

namespace eve_extra {
namespace _map_array {

template <typename T, std::size_t N, typename Op, std::size_t... idxs>
auto do_map_array(const std::array<T, N>& in, Op op,
                  std::index_sequence<idxs...>) {
  return std::array{op(in[idxs])...};
}

}  // namespace _map_array

template <typename T, std::size_t N, typename Op>
auto map_array(const std::array<T, N>& in, Op op) {
  return _map_array::do_map_array(in, op, std::make_index_sequence<N>{});
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_UNROLL_H_
