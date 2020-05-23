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

#ifndef EVE_EXTRA_MMASK_OPERATIONS_H_
#define EVE_EXTRA_MMASK_OPERATIONS_H_

#include <eve/eve.hpp>

namespace eve_extra {

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

  std::uint32_t ignore_mask = set_lower_n_bits(
      sizeof(typename Logical::storage_type) - ignore.n * sizeof(scalar));
  return ignore_mask & mmask;
}

template <typename Logical>
std::uint32_t clear_ingored(std::uint32_t mmask, ignore_first_last ignore) {
  mmask = clear_ingored<Logical>(mmask, ignore_first_n{ignore.first_n});
  return clear_ingored<Logical>(mmask, ignore_last_n{ignore.last_n});
};

}  // namespace _eve_extra

template <typename Register>
std::uint32_t movemask(Register reg) {
  if constexpr (sizeof(reg) == 16) {
    return _mm_movemask_epi8(reg);
  } else {
    return _mm256_movemask_epi8(reg);
  }
}

template <typename T, typename N, typename ABI>
auto extra_wide_movemask(eve::logical<eve::wide<T, N, ABI>> vbool) {
  using storage_type =
      typename eve::logical<eve::wide<T, N, ABI>>::storage_type;
  static constexpr std::size_t replication = storage_type::replication;

  static_assert(replication <= 8,
                "Can't do one register operation for more than 8");

  const auto& segments = vbool.storage().segments;

  static constexpr std::size_t mmask_count = replication > 4 ? 8 : 4;

  eve::wide<std::uint32_t, eve::fixed<mmask_count>> mmasks{0};
  for (std::size_t i = 0; i != replication; ++i) {
    mmasks[i] = movemask(segments[i].storage());
  }

  return mmasks;
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_MMASK_OPERATIONS_H_
