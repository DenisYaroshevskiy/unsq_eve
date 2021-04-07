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

#include <compare>
#include <concepts>
#include <cstddef>
#include <ostream>
#include <utility>
#include <type_traits>

namespace unsq_eve {

template <typename... Ts>
struct tuple;

namespace _tuple {

template <std::size_t I, typename T>
struct indexed_element_t {
  T body;

  auto operator<=>(const indexed_element_t&) const = default;
};

template <std::size_t I, typename T>
constexpr T& get(_tuple::indexed_element_t<I, T>& x) {
  return x.body;
}

template <std::size_t I, typename T>
constexpr T get(_tuple::indexed_element_t<I, T>&& x) {
  return x.body;
}

template <std::size_t I, typename T>
constexpr const T& get(const _tuple::indexed_element_t<I, T>& x) {
  return x.body;
}

template <std::size_t I, typename T>
constexpr T get(const _tuple::indexed_element_t<I, T>&& x) {
  return x.body;
}

template <typename...>
struct impl;

template <std::size_t... from0_n, typename... Ts>
struct impl<std::integer_sequence<std::size_t, from0_n...>, Ts...>
    : indexed_element_t<from0_n, Ts>... {
  constexpr impl() = default;

  constexpr explicit impl(Ts... xs) requires(sizeof...(Ts) > 0)
      : indexed_element_t<from0_n, Ts>{xs}... {}

  auto operator<=>(const impl&) const = default;
};

template <typename... Ts>
using impl_t = impl<std::index_sequence_for<Ts...>, Ts...>;

template <typename T>
struct is_tuple : std::false_type {};

template <typename... Ts>
struct is_tuple<tuple<Ts...>> : std::true_type {};

template <typename T>
concept unsq_eve_tuple = is_tuple<T>::value;

struct none_t {};

template <typename T>
struct tuple_cat_impl {
  T x;

  constexpr explicit tuple_cat_impl(T x) : x(x) {}

  template <unsq_eve_tuple U>
  constexpr auto operator+(U y) {
    if constexpr (std::same_as<T, none_t>)
      return tuple_cat_impl<U>(y);
    else {
      auto res = tuple_cat(x, y);
      return tuple_cat_impl<decltype(res)>(res);
    }
  }
};

}  // namespace _tuple

}  // namespace unsq_eve

namespace std {

template <typename... Ts>
struct tuple_size<unsq_eve::tuple<Ts...>>
    : std::integral_constant<std::size_t, sizeof...(Ts)> {};

template <std::size_t idx, typename... Ts>
struct tuple_element<idx, unsq_eve::tuple<Ts...>> {
  using type = std::remove_cvref_t<decltype(get<idx>(tuple<Ts...>{}))>;
};

template <std::size_t idx, typename... Ts>
struct tuple_element<idx, const unsq_eve::tuple<Ts...>> {
  using type =
      std::add_const_t<std::remove_cvref_t<decltype(get<idx>(tuple<Ts...>{}))>>;
};

}  // namespace std

namespace unsq_eve {

// --------------------------------------------------------
// tuple_cat: similar to std::tuple_cat but allows for not just
// unsq_eve::tuple as elements but also for just single types that are treated
// as tuple of one element.

template <typename... Ts, typename... Us>
constexpr tuple<Ts..., Us...> tuple_cat(tuple<Ts...> x, tuple<Us...> y) {
  return [&]<std::size_t... x_idx, std::size_t... y_idx>(
      std::index_sequence<x_idx...>, std::index_sequence<y_idx...>) {
    return tuple<Ts..., Us...>{get<x_idx>(x)..., get<y_idx>(y)...};
  }
  (std::index_sequence_for<Ts...>{}, std::index_sequence_for<Us...>{});
}

template <_tuple::unsq_eve_tuple... Ts>
constexpr auto tuple_cat(Ts... xs) {
  return (_tuple::tuple_cat_impl{_tuple::none_t{}} + ... + xs).x;
}

// --------------------------------------------------
// tuple_flatten - any tuple<elements> are replaced with just elements.
// this is done until none tuple elements left.

template <typename... Ts>
constexpr auto tuple_flatten(tuple<Ts...> x) {
  auto recurse = []<typename T>(const T& elem) {
    if constexpr (_tuple::unsq_eve_tuple<T>) {
      return tuple_flatten(elem);
    } else {
      return tuple{elem};
    }
  };
  return [&]<std::size_t... idxs>(std::index_sequence<idxs...>) {
    return tuple_cat(recurse(get<idxs>(x))...);
  }
  (std::index_sequence_for<Ts...>{});
}

// -------------------------------------------
// tuple_flat_ref - tuple of references to every element

template <typename Tuple>
requires _tuple::unsq_eve_tuple<std::remove_cvref_t<Tuple>>
constexpr auto tuple_flat_ref(Tuple&& x) {
  auto recurse = []<typename T>(T&& elem) {
    if constexpr (_tuple::unsq_eve_tuple<std::remove_cvref_t<T>>) {
      return tuple_flat_ref(elem);
    } else {
      return tuple<decltype(elem)>(elem);
    }
  };
  return [&]<std::size_t... idxs>(std::index_sequence<idxs...>) {
    return tuple_cat(recurse(get<idxs>(x))...);
  }
  (std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<Tuple>>>{});
}

// ----------------------------------
// same_flat_tuple - concept that indicates that two tuples have the same
// flatten structure.

template <typename T, typename U>
concept same_flat_tuple =
    _tuple::unsq_eve_tuple<T> && _tuple::unsq_eve_tuple<U> &&
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

  [&]<std::size_t... idxs>(std::index_sequence<idxs...>) {
    ((get<idxs>(out) = get<idxs>(in)), ...);
  }
  (std::make_index_sequence<std::tuple_size_v<decltype(in)>>{});

  return u;
}

template <typename U, typename T>
requires same_flat_tuple<T, U>
constexpr void tuple_cast_to(U& res, T x) { res = tuple_cast<U>(x); }

// ------------------------------
// main class

template <typename... Ts>
struct tuple : _tuple::impl_t<Ts...> {
  using base = _tuple::impl_t<Ts...>;

  using base::base;

  friend std::ostream& operator<<(std::ostream& out, const tuple& x) {
    out << "[";

    [&]<std::size_t... for0_n>(std::integer_sequence<std::size_t, for0_n...>) {
      ((out << (for0_n ? ", " : "") << get<for0_n>(x)), ...);
    }
    (std::make_integer_sequence<std::size_t, sizeof...(Ts)>{});

    out << "]";
    return out;
  }

  auto operator<=>(const tuple&) const = default;
};

template <typename... Ts>
tuple(Ts... xs) -> tuple<Ts...>;

template <typename Tuple, typename Op>
requires _tuple::unsq_eve_tuple<std::remove_cvref_t<Tuple>>
constexpr auto tuple_map(Tuple&& in, Op op) {
  return [&]<std::size_t... idxs>(std::index_sequence<idxs...>) {
    return tuple{op(get<idxs>(in))...};
  }
  (std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<Tuple>>>{});
}

template <typename Tuple, typename Op>
requires _tuple::unsq_eve_tuple<std::remove_cvref_t<Tuple>>
constexpr auto tuple_map_flat(Tuple&& in, Op op) {
  return tuple_map(in, [&](auto&& e) {
    if constexpr (_tuple::unsq_eve_tuple<std::remove_cvref_t<decltype(e)>>) {
      return tuple_map_flat(e, op);
    } else {
      return op(e);
    }
  });
}

template <typename Tuple, typename Op>
requires _tuple::unsq_eve_tuple<std::remove_cvref_t<Tuple>>
constexpr void tuple_iter_flat(Tuple&& in, Op op) {
  tuple_map_flat(in, [&](auto&& e) { op(e); return 1; });
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_TUPLE_H_
