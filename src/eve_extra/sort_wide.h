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

#ifndef EVE_EXTRA_SORT_WIDE_H_
#define EVE_EXTRA_SORT_WIDE_H_

#include <eve/eve.hpp>
#include <eve/function/max.hpp>
#include <eve/function/min.hpp>
#include <eve/function/reverse.hpp>
#include <eve/function/swap_adjacent_groups.hpp>

#include "eve_extra/mm.h"

/* Work in progress */

namespace eve_extra {

template <eve::simd_value Wide>
Wide sort_2_adjacent(const Wide& abcd)
{
  Wide badc = eve::swap_adjacent_groups(abcd, eve::lane<1>);
  Wide mins = eve::min(abcd, badc);
  Wide maxs = eve::max(abcd, badc);
  return eve::if_else(eve::logical<Wide>([](int i, int) {
    return i & 1;
  }), maxs, mins);
}

template <eve::simd_value Wide>
Wide splice_halves(Wide abxx, Wide xxcd)
{
  return Wide(
    _mm256_permute2f128_si256(abxx, xxcd, 0x30));
}

template <eve::simd_value Wide>
Wide sort_4(Wide x) {
  x = sort_2_adjacent(x);

  Wide y = eve::reverse(x);

  Wide mins = eve::min(x, y);
  Wide maxs = eve::max(x, y);
  x = splice_halves(mins, maxs);

  return sort_2_adjacent(x);
}

}  // namespace eve_extra


#endif  // EVE_EXTRA_SORT_WIDE_H_
