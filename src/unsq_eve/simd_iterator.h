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

#include <algorithm>
#include <eve/eve.hpp>
#include <eve/function/load.hpp>

namespace unsq_eve {

template <typename, typename>
struct simd_iterator;

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

template <typename T>
struct is_simd_iterator_impl : std::false_type {};

template <typename T, typename U>
struct is_simd_iterator_impl<simd_iterator<T, U>> : std::true_type {};

template <typename T>
concept is_simd_iterator = is_simd_iterator_impl<T>::value;

}  // namespace _simd_iterator

template <typename... Ts>
constexpr auto common_cardinality() {
  auto cardinalities =
      tuple_map(unsq_eve::tuple<std::type_identity<Ts>...>{},
                []<typename T>(std::type_identity<T>) {
                  if constexpr (_simd_iterator::is_simd_iterator<T>)
                    return typename T::cardinality{};
                  else
                    return eve::expected_cardinal_t<std::remove_cvref_t<decltype(*std::declval<T>())>>{};
                });

  std::ptrdiff_t res = get<0>(cardinalities)();

  tuple_iter_flat(cardinalities, [&](auto n) { res = std::min(res, n()); });
  return res;
}

template <typename... Ts, typename N>
struct simd_iterator<unsq_eve::tuple<Ts...>, N> {
  unsq_eve::tuple<Ts...> components;
  using cardinality = N;

  simd_iterator() = default;

  simd_iterator(Ts... xs) : components(xs...) {}

  friend auto load(simd_iterator it) { return load(eve::ignore_none, it, N{}); }

  friend auto load(eve::relative_conditional_expr auto cond, simd_iterator it) {
    return load(cond, it, N{});
  }

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

template <typename... Ts>
simd_iterator(Ts...) -> simd_iterator<unsq_eve::tuple<Ts...>,
                                      eve::fixed<common_cardinality<Ts...>()>>;

}  // namespace unsq_eve

#endif  // UNSQ_EVE_SIMD_ITERATOR_H_
