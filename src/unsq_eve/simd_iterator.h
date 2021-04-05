/*
 * Copyright 2021 Denis Yaroshevskiy
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

#ifndef UNSQ_EVE_SIMD_ITERATOR_H_
#define UNSQ_EVE_SIMD_ITERATOR_H_

#include "eve_extra/eve_extra.h"
#include "unsq_eve/tuple.h"

#include <eve/eve.hpp>
#include <eve/function/load.hpp>

namespace unsq_eve {

namespace _simd_iterator {

auto do_load(eve::relative_conditional_expr auto cond, auto* ptr, auto N) {
  return eve::load[cond](ptr, N);
}

template <typename T, std::size_t A>
auto do_load(eve::relative_conditional_expr auto cond,
             eve::aligned_ptr<T, A> ptr, auto N) {
  return eve::load[cond](ptr, N);
}

auto do_load(eve::relative_conditional_expr auto cond, auto x, auto N) {
  return load(cond, x, N);
}

}  // namespace _simd_iterator

template <typename... Ts>
struct simd_iterator {
  unsq_eve::tuple<Ts...> components;

  simd_iterator() = default;

  simd_iterator(Ts... xs) : components(xs...) {}

  friend auto load(simd_iterator it, auto n) {
    return load(eve::ignore_none, it, n);
  }

  friend auto load(eve::relative_conditional_expr auto cond, simd_iterator it,
                   auto n) {
    return tuple_map_flat(it.components, [&](auto e) {
      return _simd_iterator::do_load(cond, e, n);
    });
  };

  simd_iterator& operator+=(std::ptrdiff_t n) {
    components = tuple_map(components, [n](auto e) {
      e += n;
      return e;
    });
    return *this;
  }

  friend simd_iterator operator+(const simd_iterator& x, std::ptrdiff_t n) {
    auto tmp = x;
    tmp += n;
    return tmp;
  }

  friend simd_iterator operator+(std::ptrdiff_t n, const simd_iterator& x) {
    return x + n;
  }
};

}  // namespace unsq_eve

#endif  // UNSQ_EVE_SIMD_ITERATOR_H_
