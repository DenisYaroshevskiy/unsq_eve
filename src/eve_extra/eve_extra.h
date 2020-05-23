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

#include <iostream>
#include <optional>
#include <type_traits>

#include <eve/eve.hpp>
#include <eve/function/load.hpp>
#include <eve/memory/align.hpp>

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

struct ignore_last_n {
  std::size_t n;
};

struct ignore_first_last {
  std::size_t first_n;
  std::size_t last_n;
};

constexpr ignore_first_last combine(ignore_first_n x, ignore_last_n y) {
  return ignore_first_last{x.n, y.n};
}

constexpr ignore_first_last combine(ignore_last_n x, ignore_first_n y) {
  return combine(y, x);
}

namespace _eve_extra {

template <typename Register>
std::uint32_t movemask(Register reg) {
  if constexpr (sizeof(reg) == 16) {
    return _mm_movemask_epi8(reg);
  } else {
    return _mm256_movemask_epi8(reg);
  }
}

template<typename T, typename N, typename ABI>
auto extra_wide_movemask(eve::logical<eve::wide<T, N, ABI>> vbool) {
  using storage_type = typename eve::logical<eve::wide<T, N, ABI>>::storage_type;
  static constexpr std::size_t replication = storage_type::replication;

  static_assert(replication <= 8,
                "Can't do one register operation for more than 8");

  const auto& segments = vbool.storage().segments;

  static constexpr std::size_t mmask_count = replication > 4 ? 8 : 4;

  eve::wide<std::uint32_t, eve::fixed<mmask_count>> mmasks {0};
  for (std::size_t i = 0; i != replication; ++i) {
    mmasks[i] = movemask(segments[i].storage());
  }

  return mmasks;
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

  std::uint32_t ignore_mask = ~set_lower_n_bits(ignore.n * sizeof(scalar));
  return ignore_mask & mmask;
}

template <typename Logical>
std::uint32_t clear_ingored(std::uint32_t mmask, ignore_last_n ignore) {
  using scalar = typename Logical::value_type;

  std::uint32_t ignore_mask =
      set_lower_n_bits(sizeof(typename Logical::storage_type) - ignore.n * sizeof(scalar));
  return ignore_mask & mmask;
}

template <typename Logical>
std::uint32_t clear_ingored(std::uint32_t mmask, ignore_first_last ignore) {
  mmask = clear_ingored<Logical>(mmask, ignore_first_n{ignore.first_n});
  return clear_ingored<Logical>(mmask, ignore_last_n{ignore.last_n});
};

}  // namespace _eve_extra

template<typename T, typename N, typename ABI, typename Ignore>
std::optional<std::size_t> first_true(eve::logical<eve::wide<T, N, ABI>> logical,
                                      Ignore ignore) {
  if constexpr (eve::detail::is_aggregated_v<ABI>) {
    static_assert(std::is_same_v<Ignore, ignore_nothing>,
                  "ignore is not supported for extra wide");

  } else {
    using logical_t = eve::logical<eve::wide<T, N, ABI>>;
    std::uint32_t mmask = _eve_extra::movemask(logical.mask());
    mmask = _eve_extra::clear_ingored<logical_t>(mmask, ignore);

    if (!mmask) return {};
    return __builtin_ctz(mmask) / sizeof(typename logical_t::value_type);
  }
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_LOAD_UNSAFE_H_
