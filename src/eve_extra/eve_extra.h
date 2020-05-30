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
#include <eve/function/load.hpp>
#include <eve/memory/align.hpp>

#include "eve_extra/constants.h"
#include "eve_extra/first_true.h"
#include "eve_extra/mmask_operations.h"
#include "eve_extra/reduce_wide.h"
#include "eve_extra/replace_ignored.h"
#include "eve_extra/swap_adjacent_groups.h"

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
auto previous_aligned_address(const eve::as_<eve::wide<U, N>>&, T* p) requires(
    std::is_same_v<std::decay_t<T>, U>) {
  static constexpr eve::under A{alignof(eve::wide<U, N>)};
  return eve::aligned_ptr<T, as_integer(A)>{eve::align(p, A)};
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_LOAD_UNSAFE_H_
