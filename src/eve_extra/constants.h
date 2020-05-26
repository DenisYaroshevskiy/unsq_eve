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

#ifndef EVE_EXTRA_CONSTANTS_H_
#define EVE_EXTRA_CONSTANTS_H_

#include <eve/eve.hpp>

namespace eve_extra {
namespace _constants {

template <typename T, std::size_t N>
constexpr auto iota = [] {
  std::array<T, N> res = {};
  for (T i = 0; i < static_cast<T>(N); ++i) {
    res[i] = i;
  }
  return res;
}();

}  // namespace _constants

// Should dissapear
template <typename T, typename N>
auto iota(const eve::as_<eve::wide<T, N>>&) {
  return eve::wide<T, N>{_constants::iota<T, N{}()>.begin()};
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_CONSTANTS_H_
