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
#include <concepts>
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

  constexpr explicit impl(Ts... xs) requires (sizeof...(Ts) > 0)
    : indexed_element_t<from0_n, Ts>{xs}... {}

  constexpr auto operator<=>(const impl&) const = default;
};

template <typename... Ts>
using impl_t =
    impl<std::make_integer_sequence<std::ptrdiff_t, sizeof...(Ts)>, Ts...>;

template <typename T>
struct is_tuple : std::false_type {};

template <typename... Ts>
struct is_tuple<tuple<Ts...>> : std::true_type {};

template <typename T>
constexpr bool is_tuple_v = is_tuple<T>::value;

template <typename T>
constexpr std::ptrdiff_t flat_tuple_size_impl() {
  if constexpr (!_tuple::is_tuple_v<T>)
    return 1;
  else {
    return []<typename... Ts>(std::type_identity<tuple<Ts...>>) {
      return (0 + ... + flat_tuple_size_impl<Ts>());
    }
    (std::type_identity<T>{});
  }
}

}  // namespace _tuple

// --------------------------------------------------------
// tuple_cat: similar to std::tuple_cat but allows for not just
// unsq_eve::tuple as elements but also for just single types that are treated
// as tuple of one element.

template <typename... Ts, typename... Us>
constexpr tuple<Ts..., Us...> tuple_cat(tuple<Ts...> x, tuple<Us...> y) {
  return [&]<std::ptrdiff_t... x_idx, std::ptrdiff_t... y_idx>(
      std::integer_sequence<std::ptrdiff_t, x_idx...>,
      std::integer_sequence<std::ptrdiff_t, y_idx...>) {
    return tuple<Ts..., Us...>{get<x_idx>(x)..., get<y_idx>(y)...};
  }
  (std::make_integer_sequence<std::ptrdiff_t, sizeof...(Ts)>{},
   std::make_integer_sequence<std::ptrdiff_t, sizeof...(Us)>{});
}

template <typename... Ts, typename U>
constexpr tuple<Ts..., U> tuple_cat(tuple<Ts...> x, U y) {
  return [&]<std::ptrdiff_t... x_idx>(
      std::integer_sequence<std::ptrdiff_t, x_idx...>) {
    return tuple<Ts..., U>{get<x_idx>(x)..., y};
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

namespace _tuple {

struct none_t {};

template <typename T>
struct tuple_cat_impl {
  T x;

  constexpr explicit tuple_cat_impl(T x) : x(x) {}
};

template <typename T, typename U>
constexpr auto operator+(tuple_cat_impl<T> x, U y) {
  return tuple_cat_impl{tuple_cat(x.x, y)};
}

template <typename U>
constexpr auto operator+(tuple_cat_impl<none_t>, U y) {
  return tuple_cat_impl{y};
}

}  // namespace _tuple

template <typename... Ts>
constexpr auto tuple_cat(Ts... xs) {
  return (_tuple::tuple_cat_impl{_tuple::none_t{}} + ... + xs).x;
}

// --------------------------------------------------
// tuple_flatten - any tuple<elements> are replaced with just elements.
// this is done until none tuple elements left.

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
    return tuple_cat(recurse(get<idxs>(x))...);
  }
  (std::make_integer_sequence<std::ptrdiff_t, sizeof...(Ts)>{});
}

// -------------------------------------------
// tuple_flat_ref - tuple of references to every element

template <typename... Ts>
constexpr auto tuple_flat_ref(tuple<Ts...>& x) {
  auto recurse = []<typename T>(T& elem) -> decltype(auto) {
    if constexpr (_tuple::is_tuple_v<T>) {
      return tuple_flat_ref(elem);
    } else {
      return tuple<T&>(elem);
    }
  };
  return [&]<std::ptrdiff_t... idxs>(
      std::integer_sequence<std::ptrdiff_t, idxs...>) {
    return tuple_cat(recurse(get<idxs>(x))...);
  }
  (std::make_integer_sequence<std::ptrdiff_t, sizeof...(Ts)>{});
}

template <typename... Ts>
constexpr auto tuple_flat_ref(const tuple<Ts...>& x) {
  auto recurse = []<typename T>(const T& elem) -> decltype(auto) {
    if constexpr (_tuple::is_tuple_v<T>) {
      return tuple_flat_ref(elem);
    } else {
      return tuple<const T&>(elem);
    }
  };
  return [&]<std::ptrdiff_t... idxs>(
      std::integer_sequence<std::ptrdiff_t, idxs...>) {
    return tuple_cat(recurse(get<idxs>(x))...);
  }
  (std::make_integer_sequence<std::ptrdiff_t, sizeof...(Ts)>{});
}

// ---------------------------------------------
// tuple_extract - extract a range of elements from a tuple
// as a tuple.

template <std::ptrdiff_t f, std::ptrdiff_t l, typename... Ts>
constexpr auto tuple_extract(tuple<Ts...> x) {
  return [&]<std::ptrdiff_t... idxs>(
      std::integer_sequence<std::ptrdiff_t, idxs...>) {
    return tuple{get<f + idxs>(x)...};
  }
  (std::make_integer_sequence<std::ptrdiff_t, l - f>{});
}

// -----------------------------------
// flat_tuple_size/flat_tuple_size_v - what would be the size of a flatten
// tuple. returns 1 for non tuples

template <typename T>
struct flat_tuple_size
    : std::integral_constant<std::ptrdiff_t,
                             _tuple::flat_tuple_size_impl<T>()> {};

template <typename T>
constexpr std::ptrdiff_t flat_tuple_size_v = flat_tuple_size<T>::value;

// ----------------------------------
// same_flat_tuple - concept that indicates that two tuples have the same
// flatten structure.

template <typename T, typename U>
concept same_flat_tuple = _tuple::is_tuple_v<T> && _tuple::is_tuple_v<U> &&
    std::same_as<decltype(tuple_flatten(T{})), decltype(tuple_flatten(U{}))>;

// ----------------------------------
// tuple_cast - conversion between same_flat_tuple tuples
// tuple_cast_to - same but in like assignment form instead of <type>

template <typename U, typename T>
  requires same_flat_tuple<T, U>
constexpr U tuple_cast(T x) {
  U u{};

  auto in = tuple_flat_ref(x);
  auto out = tuple_flat_ref(u);

  [&]<std::ptrdiff_t... idxs>(
      std::integer_sequence<std::ptrdiff_t, idxs...>) {
    ((get<idxs>(out) = get<idxs>(in)), ...);
  }
  (std::make_integer_sequence<std::ptrdiff_t, flat_tuple_size_v<T>>{});

  return u;
}

template <typename U, typename T>
  requires same_flat_tuple<T, U>
constexpr void tuple_cast_to(U& res, T x) {
  res = tuple_cast<U>(x);
}

// ------------------------------
// main class

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
