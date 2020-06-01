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

#ifndef EVE_EXTRA_SHIFT_WITH_H_
#define EVE_EXTRA_SHIFT_WITH_H_

#include "eve_extra/concepts.h"
#include "eve_extra/mm.h"

namespace eve_extra {
namespace _shift_with {

template <std::size_t byte_shift>
__m256i alignr256_emulated(__m256i a, __m256i b) {
  __m256i b1_a0 = _mm256_permute2x128_si256(a, b, 0x03);
  if constexpr (byte_shift == 16)
    return b1_a0;
  else if constexpr (byte_shift < 16)
    return _mm256_alignr_epi8(b1_a0, b, byte_shift);
  else
    return _mm256_alignr_epi8(a, b1_a0, byte_shift - 16);
}

}  // namespace _shift_with

template <std::size_t shift, native_wide Wide>
Wide shift_pair_right(Wide lhs, Wide rhs) {
  using T = typename Wide::value_type;

  mm::reg auto lhs_raw = lhs.storage();
  mm::reg auto rhs_raw = rhs.storage();
  using raw_t = decltype(lhs_raw);

  mm::integral_reg auto lhs_reg = mm::cast_to_integral(lhs_raw);
  mm::integral_reg auto rhs_reg = mm::cast_to_integral(rhs_raw);

  mm::integral_reg auto res = [&] {
    if constexpr (sizeof(lhs_reg) == 16)
      return _mm_alignr_epi8(rhs_reg, lhs_reg, 16 - sizeof(T) * shift);
    else
      return _shift_with::alignr256_emulated<32 - sizeof(T) * shift>(rhs_reg,
                                                                     lhs_reg);
  }();

  return Wide{mm::cast<raw_t>(res)};
}

template <std::size_t shift, wide_16_bytes Wide>
Wide shift_pair_right_in_groups(Wide lhs, Wide rhs) {
  return shift_pair_right<shift>(lhs, rhs);
}

template <std::size_t shift, wide_32_bytes Wide>
Wide shift_pair_right_in_groups(Wide lhs, Wide rhs) {
  using T = typename Wide::value_type;

  mm::reg auto lhs_raw = lhs.storage();
  mm::reg auto rhs_raw = rhs.storage();
  using raw_t = decltype(lhs_raw);

  __m256i lhs_reg = mm::cast_to_integral(lhs_raw);
  __m256i rhs_reg = mm::cast_to_integral(rhs_raw);
  __m256i res = _mm256_alignr_epi8(rhs_reg, lhs_reg, 16 - sizeof(T) * shift);

  return Wide{mm::cast<raw_t>(res)};
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_SHIFT_WITH_H_
