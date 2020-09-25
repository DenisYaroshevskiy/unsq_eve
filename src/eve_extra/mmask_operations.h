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

#include <eve/conditional.hpp>
#include <eve/eve.hpp>
#include <eve/function/logical_and.hpp>

#include "eve_extra/concepts.h"
#include "eve_extra/constants.h"
#include "eve_extra/mm.h"

#include <iostream>

namespace eve_extra {

template <native_logical Logical>
std::uint32_t clear_ignored(std::uint32_t mmask, eve::ignore_none_) {
  return mmask;
}

constexpr std::uint32_t set_lower_n_bits(std::uint32_t n) {
  std::uint64_t res{1};
  res <<= n;
  res -= 1;
  return static_cast<std::uint32_t>(res);
}

template <native_logical Logical>
std::uint32_t clear_ignored(std::uint32_t mmask, eve::ignore_first_ ignore) {
  using scalar = typename Logical::value_type;

  std::uint32_t ignore_mask = ~set_lower_n_bits(ignore.count_ * sizeof(scalar));
  return ignore_mask & mmask;
}

template <native_logical Logical>
std::uint32_t clear_ignored(std::uint32_t mmask, eve::ignore_last_ ignore) {
  using scalar = typename Logical::value_type;

  std::uint32_t ignore_mask = set_lower_n_bits(
      sizeof(typename Logical::storage_type) - ignore.count_ * sizeof(scalar));
  return ignore_mask & mmask;
}

template <native_logical Logical>
std::uint32_t clear_ignored(std::uint32_t mmask, eve::ignore_extrema_ ignore) {
  mmask =
      clear_ignored<Logical>(mmask, eve::ignore_first_{ignore.first_count_});
  return clear_ignored<Logical>(mmask, eve::ignore_last_{ignore.last_count_});
}

template <eve_logical Logical>
std::uint32_t extended_movemask(Logical logical) {
  return mm::movemask(logical.storage());
}

template <eve_logical Logical>
std::uint32_t extended_movemask(eve::if_not_<Logical> logical) {
  using scalar = typename Logical::value_type;
  return set_lower_n_bits(Logical::static_size * sizeof(scalar)) &
         ~extended_movemask(logical.condition_);
}

template <typename T>
concept extended_logical = requires(const T& x) {
  {extended_movemask(x)};
};

namespace _mmask_operations {
template <typename Wide>
auto do_signed_integer_wide() {
  using T = typename Wide::value_type;
  using N = typename Wide::cardinal_type;
  using ABI = typename Wide::abi_type;

  if constexpr (sizeof(T) == 1) {
    return eve::wide<std::int8_t, N, ABI>{};
  } else if constexpr (sizeof(T) == 2) {
    return eve::wide<std::int16_t, N, ABI>{};
  } else if constexpr (sizeof(T) == 4) {
    return eve::wide<std::int32_t, N, ABI>{};
  } else if constexpr (sizeof(T) == 8) {
    return eve::wide<std::int64_t, N, ABI>{};
  }
}

template <typename Wide>
using signed_integer_wide =
    decltype(_mmask_operations::do_signed_integer_wide<Wide>());

template <typename Wide>
Wide ignore_first_broadcast(eve::ignore_first_ ignore) {
  using T = typename Wide::value_type;
  return Wide{static_cast<T>(ignore.count_) - 1};
}

template <typename Wide>
Wide ignore_last_broadcast(eve::ignore_last_ ignore) {
  using T = typename Wide::value_type;

  T last_idx = static_cast<T>(Wide::static_size);
  T offset = static_cast<T>(ignore.count_);

  return Wide{last_idx - offset};
}

}  // namespace _mmask_operations

template <eve_logical Logical>
Logical ignore_broadcast(eve::ignore_none_) {
  return eve::ignore_none.mask(eve::as_<wide_for_logical_t<Logical>>{});
}

template <eve_logical Logical>
Logical ignore_broadcast(eve::ignore_first_ ignore) {
  return ignore.mask(eve::as_<wide_for_logical_t<Logical>>{});
}

template <eve_logical Logical>
Logical ignore_broadcast(eve::ignore_last_ ignore) {
  return ignore.mask(eve::as_<wide_for_logical_t<Logical>>{});
}

template <eve_logical Logical>
Logical ignore_broadcast(eve::ignore_extrema_ ignore) {
  return ignore.mask(eve::as_<wide_for_logical_t<Logical>>{});
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_MMASK_OPERATIONS_H_
