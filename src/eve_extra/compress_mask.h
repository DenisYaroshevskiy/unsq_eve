
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

#ifndef EVE_EXTRA_COMPRESS_MASK_H_
#define EVE_EXTRA_COMPRESS_MASK_H_

#include <immintrin.h>
#include <cstdint>
#include <utility>

namespace eve_extra {

// Based on: https://stackoverflow.com/a/36951611/5021064
// Explanation (a bit outdated): https://stackoverflow.com/a/61431303/5021064
// Mask functions return the compressed indexes and the popcount.

/*
  If we write an index into every half byte, then get them to be
  in an 16 byte block like 0x00fe
  We can get them to be 0x0f0e by:
  0x00fe => (0x00fe) << 4 | 0xfe & 0x0f0f = 0x0f0e
 */

namespace _compress_mask {

template <typename T>
std::uint64_t expand_mmask_shuffle_epi8(std::uint32_t mmask) {
  if constexpr (sizeof(T) <= 2)
    return _pdep_u64(mmask, 0x1111111111111111) * 0xf;
  if constexpr (sizeof(T) == 4)
    return _pdep_u64(mmask, 0x0001000100010001) * 0xffff;
  if constexpr (sizeof(T) == 8)
    return _pdep_u64(mmask, 0x0000000100000001) * 0xffffffff;
}

template <typename T>
std::uint64_t expand_mmask_permutevar8x32(std::uint32_t mmask) {
  if constexpr (sizeof(T) == 4)
    return _pdep_u64(mmask, 0x0101'0101'0101'0101) * 0xff;
  if constexpr (sizeof(T) == 8)
    return _pdep_u64(mmask, 0x0001'0001'0001'0001) * 0xffff;
}

}  // namespace _compress_mask

template <typename T>
std::pair<__m128i, std::uint8_t> compress_mask_for_shuffle_epi8(
    std::uint32_t mmask) {
  const std::uint64_t mmask_expanded =
      _compress_mask::expand_mmask_shuffle_epi8<T>(mmask);

  std::uint8_t offset = static_cast<std::uint8_t>(_mm_popcnt_u32(mmask));
  if constexpr (sizeof(T) == 2) offset /= 2;

  const std::uint64_t compressed_idxes = _pext_u64(
      0xfedcba9876543210, mmask_expanded);  // Do the @PeterCordes answer

  const __m128i as_lower_8byte =
      _mm_cvtsi64_si128(compressed_idxes);  // 0...0|compressed_indexes
  const __m128i as_16bit =
      _mm_cvtepu8_epi16(as_lower_8byte);  // Fill int the shorts
  const __m128i shift_by_4 = _mm_slli_epi16(as_16bit, 4);       // indexes << 4
  const __m128i combined = _mm_or_si128(shift_by_4, as_16bit);  // | indexes
  const __m128i filter = _mm_set1_epi16(0x0f0f);                // 0x0f0f
  const __m128i res = _mm_and_si128(combined, filter);          // & 0xf0f

  return {res, offset};
}

template <typename T>
std::pair<__m256i, std::uint8_t> compress_mask_for_permutevar8x32(
    std::uint32_t mmask) {
  const std::uint64_t mmask_expanded =
      _compress_mask::expand_mmask_permutevar8x32<T>(mmask);

  const std::uint8_t offset = static_cast<std::uint8_t>(_mm_popcnt_u32(mmask));

  const std::uint64_t compressed_idxes = _pext_u64(
      0x0706050403020100, mmask_expanded);  // Do the @PeterCordes answer

  const __m128i as_lower_8byte = _mm_cvtsi64_si128(compressed_idxes);
  const __m256i expanded = _mm256_cvtepu8_epi32(as_lower_8byte);
  return {expanded, offset};
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_COMPRESS_MASK_H_
