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

#ifndef EVE_EXTRA_MM_H_
#define EVE_EXTRA_MM_H_

#include <immintrin.h>

namespace eve_extra {
namespace mm {

template <typename T, typename... Args>
concept one_of = (std::is_same_v<T, Args> || ...);

template <typename Register>
concept integral_reg = one_of<Register, __m128i, __m256i>;

template <typename Register>
concept float_reg = one_of<Register, __m128, __m256>;

template <typename Register>
concept double_reg = one_of<Register, __m128d, __m256d>;

template <typename Register>
concept reg =
    integral_reg<Register> || float_reg<Register> || double_reg<Register>;

template <integral_reg Reg>
auto cast_to_integral(Reg x) {
  return x;
}

template <float_reg Reg>
auto cast_to_integral(Reg x) {
  if constexpr (std::is_same_v<Reg, __m128>)
    return _mm_castps_si128(x);
  else
    return _mm256_castps_si256(x);
}

template <double_reg Reg>
auto cast_to_integral(Reg x) {
  if constexpr (std::is_same_v<Reg, __m128d>)
    return _mm_castpd_si128(x);
  else
    return _mm256_castpd_si256(x);
}

template <integral_reg Reg>
auto cast_to_float(Reg x) {
  if constexpr (std::is_same_v<Reg, __m128i>)
    return _mm_castsi128_ps(x);
  else
    return _mm256_castsi256_ps(x);
}

template <float_reg Reg>
auto cast_to_float(Reg x) {
  return x;
}

template <double_reg Reg>
auto cast_to_float(Reg x) {
  if constexpr (std::is_same_v<Reg, __m128d>)
    return _mm_castpd_ps(x);
  else
    return _mm256_castpd_ps(x);
}

template <integral_reg Reg>
auto cast_to_double(Reg x) {
  if constexpr (std::is_same_v<Reg, __m128i>)
    return _mm_castsi128_pd(x);
  else
    return _mm256_castsi256_pd(x);
}

template <float_reg Reg>
auto cast_to_double(Reg x) {
  if constexpr (std::is_same_v<Reg, __m128>)
    return _mm_castps_pd(x);
  else
    return _mm256_castps_pd(x);
}

template <double_reg Reg>
auto cast_to_double(Reg x) {
  return x;
}

template <integral_reg To, reg From>
To cast(From x) {
  return cast_to_integral(x);
}

template <float_reg To, reg From>
To cast(From x) {
  return cast_to_float(x);
}

template <double_reg To, reg From>
To cast(From x) {
  return cast_to_double(x);
}

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

}  // namespace mm
}  // namespace eve_extra

#endif  // EVE_EXTRA_MM_H_
