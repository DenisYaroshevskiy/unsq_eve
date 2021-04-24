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

#ifndef UNSQ_EVE_simd_iterator_H_
#define UNSQ_EVE_simd_iterator_H_

#include "eve_extra/eve_extra.h"
#include "unsq_eve/tuple.h"

#include <algorithm>
#include <compare>

#include <eve/eve.hpp>
#include <eve/function/load.hpp>

namespace unsq_eve {

template <typename, typename>
struct simd_iterator;

}  // namespace unsq_eve

namespace std {

template <typename... Ts>
struct tuple_size<unsq_eve::simd_iterator<Ts...>>
    : tuple_size<typename unsq_eve::simd_iterator<Ts...>::components_t> {};

template <std::size_t idx, typename... Ts>
struct tuple_element<idx, unsq_eve::simd_iterator<Ts...>>
    : tuple_element<idx,
                    typename unsq_eve::simd_iterator<Ts...>::components_t> {};

template <std::size_t idx, typename... Ts>
struct tuple_element<idx, const unsq_eve::simd_iterator<Ts...>>
    : tuple_element<
          idx, const typename unsq_eve::simd_iterator<Ts...>::components_t> {};

}  // namespace std

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

template <typename T>
struct is_simd_iterator_impl : std::false_type {};

template <typename T, typename U>
struct is_simd_iterator_impl<simd_iterator<T, U>> : std::true_type {};

template <typename T>
concept is_simd_iterator = is_simd_iterator_impl<T>::value;

}  // namespace _simd_iterator

template <std::size_t I, typename T>
requires _simd_iterator::is_simd_iterator<std::remove_cvref_t<T>>
decltype(auto) get(T&& x) { return get<I>(std::forward<T>(x).components); }

template <typename... Ts>
constexpr auto common_cardinality() {
  auto cardinalities =
      tuple_map(unsq_eve::tuple<std::type_identity<Ts>...>{},
                []<typename T>(std::type_identity<T>) {
                  if constexpr (_simd_iterator::is_simd_iterator<T>)
                    return typename T::cardinality{};
                  else
                    return eve::expected_cardinal_t<
                        std::remove_cvref_t<decltype(*std::declval<T>())>>{};
                });

  std::ptrdiff_t res = get<0>(cardinalities)();

  tuple_iter_flat(cardinalities, [&](auto n) { res = std::min(res, n()); });
  return res;
}

template <typename... Ts, typename N>
struct simd_iterator<unsq_eve::tuple<Ts...>, N> {
  using componets_t = unsq_eve::tuple<Ts...>;
  componets_t components;

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

  simd_iterator& operator-=(std::ptrdiff_t n) {
    components = tuple_map(components, [n](auto e) {
      e -= n;
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

  friend simd_iterator operator-(const simd_iterator& x, std::ptrdiff_t n) {
    auto tmp = x;
    tmp -= n;
    return tmp;
  }

  friend std::ptrdiff_t operator-(const simd_iterator& x,
                                  const simd_iterator& y) {
    return get<0>(x) - get<0>(y);
  }

  friend auto operator==(const simd_iterator& x, const simd_iterator& y) {
    return get<0>(x) == get<0>(y);
  }

  friend auto operator<=>(const simd_iterator& x, const simd_iterator& y) {
    return get<0>(x) <=> get<0>(y);
  }
};

template <typename... Ts>
simd_iterator(Ts...) -> simd_iterator<unsq_eve::tuple<Ts...>,
                                      eve::fixed<common_cardinality<Ts...>()>>;

}  // namespace unsq_eve

#endif  // UNSQ_EVE_simd_iterator_H_
