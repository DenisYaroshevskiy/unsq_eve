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

#ifndef UNSQ_EVE_TUPLE_H_
#define UNSQ_EVE_TUPLE_H_

#include "unsq_eve/type_list.h"

#include <compare>
#include <cstddef>
#include <ostream>
#include <type_traits>

namespace unsq_eve {

template <typename... Ts>
struct tuple;

namespace _tuple {

template <std::ptrdiff_t I, typename T>
struct indexed_element_t {
  T body;

  constexpr auto operator<=>(const indexed_element_t&) const = default;
};

template <std::ptrdiff_t I, typename T>
constexpr T& get(_tuple::indexed_element_t<I, T>& x) {
  return x.body;
}

template <std::ptrdiff_t I, typename T>
constexpr const T& get(const _tuple::indexed_element_t<I, T>& x) {
  return x.body;
}

template <typename...>
struct impl;

template <std::ptrdiff_t... from0_n, typename... Ts>
struct impl<std::integer_sequence<std::ptrdiff_t, from0_n...>, Ts...>
    : indexed_element_t<from0_n, Ts>... {
  constexpr impl() = default;

  constexpr explicit impl(Ts... xs) : indexed_element_t<from0_n, Ts>{xs}... {}

  constexpr auto operator<=>(const impl&) const = default;
};

template <typename... Ts>
using impl_t =
    impl<std::make_integer_sequence<std::ptrdiff_t, sizeof...(Ts)>, Ts...>;

struct none_t {};

template <typename T>
struct tuple_cat_impl {
  T x;

  tuple_cat_impl(T x) : x(x) {}
};

template <typename T, typename U>
auto operator+(tuple_cat_impl<T> x, U y) {
  return tuple_cat_impl{tuple_cat((const T&)x, y)};
}

template <typename U>
auto operator+(tuple_cat_impl<none_t>, U y) {
  return tuple_cat_impl{y};
}

template <typename T>
struct is_tuple : std::false_type {};

template <typename... Ts>
struct is_tuple<tuple<Ts...>> : std::true_type {};

template <typename T>
constexpr bool is_tuple_v = is_tuple<T>::value;

}  // namespace _tuple

template <typename... Ts, typename... Us>
constexpr tuple<Ts..., Us...> tuple_cat(tuple<Ts...> x, tuple<Us...> y) {
  return [&]<std::ptrdiff_t... x_idx, std::ptrdiff_t... y_idx>(
      std::integer_sequence<std::ptrdiff_t, x_idx...>,
      std::integer_sequence<std::ptrdiff_t, y_idx...>) {
    return tuple{get<x_idx>(x)..., get<y_idx>(y)...};
  }
  (std::make_integer_sequence<std::ptrdiff_t, sizeof...(Ts)>{},
   std::make_integer_sequence<std::ptrdiff_t, sizeof...(Us)>{});
}

template <typename... Ts, typename U>
constexpr tuple<Ts..., U> tuple_cat(tuple<Ts...> x, U y) {
  return [&]<std::ptrdiff_t... x_idx>(
      std::integer_sequence<std::ptrdiff_t, x_idx...>) {
    return tuple{get<x_idx>(x)..., y};
  }
  (std::make_integer_sequence<std::ptrdiff_t, sizeof...(Ts)>{});
}

template <typename T, typename... Us>
constexpr tuple<T, Us...> tuple_cat(T x, tuple<Us...> y) {
  return [&]<std::ptrdiff_t... y_idx>(
      std::integer_sequence<std::ptrdiff_t, y_idx...>) {
    return tuple{x, get<y_idx>(y)...};
  }
  (std::make_integer_sequence<std::ptrdiff_t, sizeof...(Us)>{});
}

template <typename T, typename U>
constexpr tuple<T, U> tuple_cat(T x, U y) {
  return tuple{x, y};
}

template <typename... Ts>
constexpr auto tuple_cat(Ts... xs) {
  return (_tuple::tuple_cat_impl{_tuple::none_t{}} + ... + xs).x;
}

template <typename... Ts>
constexpr auto tuple_flatten(tuple<Ts...> x) {
  auto recurse = []<typename T>(const T& elem) {
    if constexpr (_tuple::is_tuple_v<T>) {
      return tuple_flatten(elem);
    } else {
      return elem;
    }
  };
  return [&]<std::ptrdiff_t... idxs>(
      std::integer_sequence<std::ptrdiff_t, idxs...>) {
    return tuple_cat(recurse(get<idxs>(x)) ...);
  }
  (std::make_integer_sequence<std::ptrdiff_t, sizeof...(Ts)>{});
}

template <typename... Ts>
struct tuple : _tuple::impl_t<Ts...> {
  using base = _tuple::impl_t<Ts...>;

  using base::base;

  friend std::ostream& operator<<(std::ostream& out, const tuple& x) {
    out << "[";

    [&]<std::ptrdiff_t... for0_n>(
        std::integer_sequence<std::ptrdiff_t, for0_n...>) {
      ((out << (for0_n ? ", " : "") << get<for0_n>(x)), ...);
    }
    (std::make_integer_sequence<std::ptrdiff_t, sizeof...(Ts)>{});

    out << "]";
    return out;
  }

  constexpr auto operator<=>(const tuple&) const = default;
};

template <typename... Ts>
tuple(Ts... xs) -> tuple<Ts...>;

}  // namespace unsq_eve

#endif  // UNSQ_EVE_TUPLE_H_
