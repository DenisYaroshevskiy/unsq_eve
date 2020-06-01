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

#ifndef EVE_EXTRA_STORE_H_
#define EVE_EXTRA_STORE_H_

#include <cstdint>
#include <type_traits>

#include <immintrin.h>

#include <eve/function/store.hpp>

#include "eve_extra/concepts.h"
#include "eve_extra/mm.h"
#include "eve_extra/mmask_operations.h"

namespace eve_extra {
namespace _store {

template <typename T, typename Mask, typename Register>
void maskstore(T* to, Mask mask, Register reg) requires(std::integral<T> &&
                                                        sizeof(T) >= 4 &&
                                                        sizeof(T) <= 8) {
  static_assert(sizeof(Mask) == sizeof(Register));

  if constexpr (sizeof(T) == 4 && sizeof(Register) == 16)
    _mm_maskstore_epi32(reinterpret_cast<std::int32_t*>(to), mask, reg);
  if constexpr (sizeof(T) == 4 && sizeof(Register) == 32)
    _mm256_maskstore_epi32(reinterpret_cast<std::int32_t*>(to), mask, reg);
  if constexpr (sizeof(T) == 8 && sizeof(Register) == 16)
    _mm_maskstore_epi64(reinterpret_cast<long long*>(to), mask, reg);
  if constexpr (sizeof(T) == 8 && sizeof(Register) == 32)
    _mm256_maskstore_epi64(reinterpret_cast<long long*>(to), mask, reg);
}

template <typename T, typename Mask, typename Register>
void maskstore(T* to, Mask mask,
               Register reg) requires(std::floating_point<T>) {
  static_assert(sizeof(Mask) == sizeof(Register));

  if constexpr (std::is_same_v<T, float> && sizeof(Register) == 16)
    _mm_maskstore_ps(to, mask, reg);
  if constexpr (std::is_same_v<T, float> && sizeof(Register) == 32)
    _mm256_maskstore_ps(to, mask, reg);
  if constexpr (std::is_same_v<T, double> && sizeof(Register) == 16)
    _mm_maskstore_pd(to, mask, reg);
  if constexpr (std::is_same_v<T, double> && sizeof(Register) == 32)
    _mm256_maskstore_pd(to, mask, reg);
}

template <typename T, typename Register>
void maskmove(T* to, __m128i mask, Register reg) {
  _mm_maskmoveu_si128(mm::cast_to_integral(reg), mask,
                      reinterpret_cast<char*>(to));
}

template <typename T, std::size_t A>
T* raw_pointer(eve::aligned_ptr<T, A> ptr) {
  return ptr.get();
}

template <typename T>
T* raw_pointer(T* ptr) {
  return ptr;
}

}  // namespace _store

template <eve_wide Wide, typename Ptr>
void store(const Wide& wide, Ptr ptr, ignore_nothing) {
  eve::store(wide, ptr);
}

template <native_wide Wide, typename Ptr, typename Ignore>
void store(const Wide& wide, Ptr ptr, Ignore ignore) {
  using T = typename Wide::value_type;
  static_assert(std::is_same_v<T, std::decay_t<decltype(*ptr)>>);

  const auto mask = ignore_broadcast<eve::logical<Wide>>(ignore).storage();
  const auto reg = wide.storage();

  if constexpr (sizeof(T) >= 4) {
    _store::maskstore(_store::raw_pointer(ptr), mask, reg);
  } else if constexpr (sizeof(reg) == 16) {
    _store::maskmove(_store::raw_pointer(ptr), mask, reg);
  } else {
    __m256i _reg = reg;

    const __m128i low = _mm256_extracti128_si256(_reg, 0);
    const __m128i high = _mm256_extracti128_si256(_reg, 1);
    const __m128i low_mask = _mm256_extracti128_si256(mask, 0);
    const __m128i high_mask = _mm256_extracti128_si256(mask, 1);

    T* to = _store::raw_pointer(ptr);
    _store::maskmove(to, low_mask, low);
    to += 16 / sizeof(T);
    _store::maskmove(to, high_mask, high);
  }
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_STORE_H_
