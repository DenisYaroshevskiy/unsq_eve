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

#ifndef EVE_EXTRA_REVERSE_H_
#define EVE_EXTRA_REVERSE_H_

#include <immintrin.h>

#include <eve/eve.hpp>

#include "eve_extra/concepts.h"
#include "eve_extra/mm.h"
#include <eve/function/swap_adjacent_group.hpp>

namespace eve_extra {
namespace _reverse {

template <std::size_t element_size>
__m128i reverse_16_bytes_mask() {
  if constexpr (element_size == 1) {
    return eve::wide<char, eve::fixed<16>>([](int i, int) { return 15 - i; })
        .storage();
  }
  if constexpr (element_size == 2) {
    return _mm_set_epi8(1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14);
  }
}

inline __m256i reverse_32_bytes_4_byte_elements_mask() {
  return eve::wide<int, eve::fixed<8>>([](int i, int) { return 7 - i; })
      .storage();
}

}  // namespace _reverse

template <wide_16_bytes Wide>
Wide reverse(const Wide& wide) requires(element_size_v<Wide> < 4) {
  const __m128i raw = mm::cast_to_integral(wide.storage());

  const __m128i mask = _reverse::reverse_16_bytes_mask<element_size_v<Wide>>();
  const __m128i shuffled = _mm_shuffle_epi8(raw, mask);

  return Wide(mm::cast<typename Wide::storage_type>(shuffled));
}

template <wide_32_bytes Wide>
Wide reverse(const Wide& wide) requires(element_size_v<Wide> < 4) {
  const __m256i raw = mm::cast_to_integral(wide.storage());

  const __m128i mask16 =
      _reverse::reverse_16_bytes_mask<element_size_v<Wide>>();
  const __m256i mask = _mm256_set_m128i(mask16, mask16);

  const Wide each_half{
      mm::cast<typename Wide::storage_type>(_mm256_shuffle_epi8(raw, mask))};

  return eve::swap_adjacent_group(each_half, eve::lane<Wide::static_size / 2>);
}

template <wide_16_bytes Wide>
Wide reverse(const Wide& wide) requires(element_size_v<Wide> == 4) {
  const __m128i raw = mm::cast_to_integral(wide.storage());

  const auto mask = _MM_SHUFFLE(0, 1, 2, 3);
  const __m128i shuffled = _mm_shuffle_epi32(raw, mask);

  return Wide(mm::cast<typename Wide::storage_type>(shuffled));
}

template <wide_32_bytes Wide>
Wide reverse(const Wide& wide) requires(element_size_v<Wide> == 4) {
  const __m256i raw = mm::cast_to_integral(wide.storage());

  const __m256i mask = _reverse::reverse_32_bytes_4_byte_elements_mask();
  const __m256i shuffled = _mm256_permutevar8x32_epi32(raw, mask);

  return Wide(mm::cast<typename Wide::storage_type>(shuffled));
}

template <wide_16_bytes Wide>
Wide reverse(const Wide& wide) requires(element_size_v<Wide> == 8) {
  const __m128i raw = mm::cast_to_integral(wide.storage());

  const auto mask = _MM_SHUFFLE(1, 0, 3, 2);
  const __m128i shuffled = _mm_shuffle_epi32(raw, mask);

  return Wide(mm::cast<typename Wide::storage_type>(shuffled));
}

template <wide_32_bytes Wide>
Wide reverse(const Wide& wide) requires(element_size_v<Wide> == 8) {
  const __m256i raw = mm::cast_to_integral(wide.storage());

  const auto mask = _MM_SHUFFLE(0, 1, 2, 3);
  const __m256i shuffled = _mm256_permute4x64_epi64(raw, mask);

  return Wide(mm::cast<typename Wide::storage_type>(shuffled));
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_REVERSE_H_
