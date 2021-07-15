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

#ifndef EVE_EXTRA_SCAN_H_
#define EVE_EXTRA_SCAN_H_

#include "eve_extra/concepts.h"
#include "eve_extra/shift_pair.h"

#include <iostream>

namespace eve_extra {

// Took the idea from: https://stackoverflow.com/a/19496697/5021064
// [a b c d]
// + [0 a b c]
// [a (a + b) (b + c) (c + d)]
// >> 2 [0 0 a (a + b)]
// [a (a + b) (a + b + c) (a + b + c + d)]

namespace _scan_wide {

template <std::size_t group_size, native_wide Wide, typename Op>
Wide inclusive_impl(Wide x, Op op, Wide zero) {
  if constexpr (group_size == 1)
    return x;
  else {
    x = inclusive_impl<group_size / 2>(x, op, zero);
    x = op(x, shift_pair_right_in_groups<group_size / 2>(zero, x));
    return x;
  }
}

}  // namespace _scan_wide

template <wide_16_bytes Wide, typename Op>
Wide inclusive_scan_wide(Wide x, Op op, Wide zero) {
  return _scan_wide::inclusive_impl<Wide::size()>(x, op, zero);
}

template <wide_32_bytes Wide, typename Op>
Wide inclusive_scan_wide(Wide x, Op op, Wide zero) {
  x = _scan_wide::inclusive_impl<Wide::size() / 2>(x, op, zero);
  Wide left_sum_broadcasted{x.get(Wide::size() / 2 - 1)};

  return op(
      x, shift_pair_right<Wide::size() / 2>(zero, left_sum_broadcasted));
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_SCAN_H_
