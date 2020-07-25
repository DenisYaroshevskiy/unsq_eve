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

#ifndef EVE_EXTRA_COMPRESS_STORE_H_
#define EVE_EXTRA_COMPRESS_STORE_H_

#include <immintrin.h>
#include <array>

#include <eve/eve.hpp>

#include "eve_extra/compress_mask.h"
#include "eve_extra/concepts.h"
#include "eve_extra/mm.h"
#include "eve_extra/mmask_operations.h"
#include "eve_extra/store.h"

namespace eve_extra {
namespace _compress_store {

template <typename T, mm::integral_reg Reg>
T* compress_store_impl(Reg reg, T* out,
                       std::uint32_t mmask) requires(sizeof(Reg) == 16) {
  auto [mask, offset] = compress_mask_for_shuffle_epi8<T>(mmask);
  const Reg shuffled = _mm_shuffle_epi8(reg, mask);

  _mm_storeu_si128(reinterpret_cast<__m128i*>(out), shuffled);

  return out + offset;
}

template <typename T, mm::integral_reg Reg>
T* compress_store_impl(Reg reg, T* out,
                       std::uint32_t mmask) requires(sizeof(T) >= 4 &&
                                                     sizeof(Reg) == 32) {
  auto [mask, offset] = compress_mask_for_permutevar8x32<T>(mmask);
  const Reg shuffled = _mm256_permutevar8x32_epi32(reg, mask);
  _mm256_storeu_si256(reinterpret_cast<__m256i*>(out), shuffled);
  return out + offset;
}

template <typename T, mm::integral_reg Reg>
T* compress_store_impl(Reg reg, T* out,
                       std::uint32_t mmask) requires(sizeof(T) < 4 &&
                                                     sizeof(Reg) == 32) {
  __m128i top = _mm256_extracti128_si256(reg, 0);
  __m128i bottom = _mm256_extracti128_si256(reg, 1);

  out = compress_store_impl(top, out, mmask & 0xffff);
  return compress_store_impl(bottom, out, mmask >> 16);
}

}  // namespace _compress_store

template <native_wide Wide, std::same_as<typename Wide::value_type> T,
          typename Ignore>
T* compress_store_precise(const Wide& wide, T* out,
                          const eve::logical<Wide>& wide_mask, Ignore ignore) {
  const auto reg = mm::cast_to_integral(wide.storage());
  std::uint32_t mmask = movemask(wide_mask.storage());
  mmask = clear_ingored<eve::logical<Wide>>(mmask, ignore);

  if constexpr (std::same_as<Ignore, ignore_first_n>) {
    out += ignore.n;
  } else if constexpr (std::same_as<Ignore, ignore_first_last>) {
    out += ignore.first_n;
  }

  Wide buffer;
  T* up_to = _compress_store::compress_store_impl(reg, buffer.begin(), mmask);

  // std::copy but memcpy instead of memmove
  std::size_t n = up_to - buffer.begin();

  eve_extra::store(buffer, out, ignore_last_n{Wide::static_size - n});
  return out + n;
}

template <native_wide Wide, std::same_as<typename Wide::value_type> T,
          typename Ignore>
T* compress_store_unsafe(const Wide& wide, T* out,
                         const eve::logical<Wide>& wide_mask, Ignore ignore) {
  if constexpr (!std::same_as<Ignore, ignore_nothing>) {
    return compress_store_precise(wide, out, wide_mask, ignore);
  } else {
    const auto reg = mm::cast_to_integral(wide.storage());
    const std::uint32_t mmask = movemask(wide_mask.storage());

    return _compress_store::compress_store_impl(reg, out, mmask);
  }
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_COMPRESS_STORE_H_
