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

#ifndef EVE_EXTRA_REDUCE_WIDE_H_
#define EVE_EXTRA_REDUCE_WIDE_H_

#include "eve_extra/concepts.h"

#include <eve/function/swap_adjacent_group.hpp>

namespace eve_extra {
namespace _reduce_wide {

template <std::ptrdiff_t current_group_size, typename Wide, typename Op>
Wide do_reduce_wide(Wide x, Op op) {
  Wide y = eve::swap_adjacent_group(x, eve::lane<current_group_size>);
  x = op(x, y);
  if constexpr (current_group_size == 1) {
    return x;
  } else {
    return do_reduce_wide<current_group_size / 2>(x, op);
  }
}

}  // namespace _reduce_wide

template <eve_wide Wide, typename Op>
Wide reduce_wide(Wide x, Op op) {
  return _reduce_wide::do_reduce_wide<Wide::static_size / 2>(x, op);
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_REDUCE_WIDE_H_
