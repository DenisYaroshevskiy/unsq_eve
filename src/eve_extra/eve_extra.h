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
#include <eve/function/any.hpp>
#include <eve/function/load.hpp>
#include <eve/memory/align.hpp>

#include "eve_extra/mmask_operations.h"

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

template <typename T, typename N, typename ABI, typename Ignore>
std::optional<std::size_t> first_true(
    eve::logical<eve::wide<T, N, ABI>> logical, Ignore ignore) {
  if constexpr (eve::detail::is_aggregated_v<ABI>) {
    static_assert(std::is_same_v<Ignore, ignore_nothing>,
                  "ignore is not supported for extra wide");

  } else {
    using logical_t = eve::logical<eve::wide<T, N, ABI>>;
    std::uint32_t mmask = eve_extra::movemask(logical.mask());
    mmask = _eve_extra::clear_ingored<logical_t>(mmask, ignore);

    if (!mmask) return {};
    return __builtin_ctz(mmask) / sizeof(typename logical_t::value_type);
  }
}

template <typename T, typename N, typename ABI, typename Ignore>
bool any(eve::logical<eve::wide<T, N, ABI>> logical, Ignore ignore) {
  using logical_t = eve::logical<eve::wide<T, N, ABI>>;

  if constexpr (eve::detail::is_aggregated_v<ABI>) {
    static_assert(std::is_same_v<Ignore, ignore_nothing>,
                  "ignore is not supported for extra wide");
    auto wide_mmask = extra_wide_movemask(logical);
    decltype(wide_mmask) zeroes{0};
    return eve::any(wide_mmask > zeroes);
  } else {
    std::uint32_t mmask = eve_extra::movemask(logical.mask());
    mmask = _eve_extra::clear_ingored<logical_t>(mmask, ignore);
    return mmask;
  }
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_LOAD_UNSAFE_H_
