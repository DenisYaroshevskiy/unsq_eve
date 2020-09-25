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

#include <eve/conditional.hpp>
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
          extended_logical Mask, typename Ignore>
T* compress_store_precise(const Wide& wide, T* out, const Mask& wide_mask,
                          Ignore ignore) {
  const auto reg = mm::cast_to_integral(wide.storage());
  std::uint32_t mmask = extended_movemask(wide_mask);
  mmask = clear_ignored<eve::logical<Wide>>(mmask, ignore);

  if constexpr (std::same_as<Ignore, eve::ignore_first_>) {
    out += ignore.count_;
  } else if constexpr (std::same_as<Ignore, eve::ignore_extrema_>) {
    out += ignore.first_count_;
  }

  Wide buffer;
  T* up_to = _compress_store::compress_store_impl(reg, buffer.begin(), mmask);

  // std::copy but memcpy instead of memmove
  int n = up_to - buffer.begin();

  eve_extra::store(buffer, out,
                   eve::ignore_last_{static_cast<int>(Wide::static_size - n)});
  return out + n;
}

template <native_wide Wide, std::same_as<typename Wide::value_type> T,
          extended_logical Mask, typename Ignore>
T* compress_store_unsafe(const Wide& wide, T* out, const Mask& wide_mask,
                         Ignore ignore) {
  if constexpr (!std::same_as<Ignore, eve::ignore_none_>) {
    return compress_store_precise(wide, out, wide_mask, ignore);
  } else {
    const auto reg = mm::cast_to_integral(wide.storage());
    const std::uint32_t mmask = extended_movemask(wide_mask);

    return _compress_store::compress_store_impl(reg, out, mmask);
  }
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_COMPRESS_STORE_H_
