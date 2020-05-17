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

#ifndef EVE_EXTRA_LOAD_UNSAFE_H_
#define EVE_EXTRA_LOAD_UNSAFE_H_

#include <optional>
#include <type_traits>

#include <eve/eve.hpp>
#include <eve/memory/align.hpp>
#include <eve/function/load.hpp>

namespace eve_extra {

template <typename P, typename Tgt>
__attribute__((no_sanitize_address)) auto load_unsafe(P p,
                                                      const Tgt& tgt) noexcept {
  return eve::load(p, tgt);
}

constexpr std::ptrdiff_t page_size() { return 1 << 12; }

template <typename T>
T* end_of_page(T* addr) {
  std::uintptr_t upage_size = page_size();
  std::uintptr_t mask = ~(upage_size - 1);
  return reinterpret_cast<T*>((reinterpret_cast<std::uintptr_t>(addr) & mask) +
                              upage_size);
}

template <typename U, typename N, typename T>
auto previous_aligned_address(const eve::as_<eve::wide<U, N>>&, T* p) {
  static_assert(std::is_same_v<std::decay_t<T>, U>);

  static constexpr eve::under A{alignof(eve::wide<U, N>)};
  return eve::aligned_ptr<T, A.value>{eve::align(p, A)};
}

struct ignore_nothing {};

struct ignore_first_n {
  std::size_t n;
};

namespace _eve_extra {

template <typename Logical>
std::uint32_t movemask(Logical logical) {
  if constexpr (sizeof(Logical) == 16) {
    return _mm_movemask_epi8((__m128i)logical.storage());
  } else {
    return _mm256_movemask_epi8((__m256i)logical.storage());
  }
}

template <typename Logical>
std::uint32_t clear_ingored(std::uint32_t mmask, ignore_nothing) {
  return mmask;
}

constexpr std::uint32_t set_lower_n_bits(std::uint32_t n) {
  std::uint64_t res{1};
  res <<= n;
  res -= 1;
  return static_cast<std::uint32_t>(res);
}

template <typename Logical>
std::uint32_t clear_ingored(std::uint32_t mmask, ignore_first_n ignore) {
  using scalar = typename Logical::value_type;
  return ~set_lower_n_bits(ignore.n * sizeof(scalar)) & mmask;
}

}  // namespace _eve_extra

template <typename Logical, typename Ignore>
std::optional<std::size_t> first_true(Logical logical,
                                      Ignore ignore) {
  std::uint32_t mmask = _eve_extra::movemask(logical);
  mmask = _eve_extra::clear_ingored<Logical>(mmask, ignore);

  if (!mmask) return {};
  return __builtin_ctz(mmask) / sizeof(typename Logical::value_type);
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_LOAD_UNSAFE_H_
