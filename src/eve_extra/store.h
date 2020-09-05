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
#include <cstring>
#include <type_traits>

#include <immintrin.h>

#include <eve/function/store.hpp>

#include "eve_extra/concepts.h"
#include "eve_extra/mm.h"
#include "eve_extra/mmask_operations.h"

namespace eve_extra {
namespace _store {

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
void store(const Wide& wide, Ptr ptr, eve::ignore_none_) {
  eve::store(wide, ptr);
}

template <native_wide Wide, typename Ptr, typename Ignore>
void store(const Wide& wide, Ptr ptr, Ignore ignore) {
  using T = typename Wide::value_type;
  static_assert(std::is_same_v<T, std::decay_t<decltype(*ptr)>>);
  T* raw_ptr = _store::raw_pointer(ptr);

  if constexpr (sizeof(T) >= 4) {
    const auto mask = ignore_broadcast<eve::logical<Wide>>(ignore).storage();
    const auto reg = wide.storage();

    mm::maskstore(raw_ptr, mask, reg);
    return;
  }

  std::size_t start = 0, n = Wide::static_size;
  if constexpr (std::is_same_v<Ignore, eve::ignore_first_>) {
    start += ignore.count_;
    n -= ignore.count_;
  } else if constexpr (std::is_same_v<Ignore, eve::ignore_last_>) {
    n -= ignore.count_;
  } else {
    static_assert(std::is_same_v<Ignore, eve::ignore_extrema_>);
    start += ignore.first_count_;
    n -= ignore.first_count_ + ignore.last_count_;
  }

  // memcpy requires not null for pointers - this is the easiest check
  if (!n) return;
  std::memcpy(raw_ptr + start, wide.begin() + start, n * sizeof(T));
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_STORE_H_
