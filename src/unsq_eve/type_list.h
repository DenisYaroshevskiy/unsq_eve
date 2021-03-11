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

#ifndef UNSQ_EVE_TYPE_LIST_H_
#define UNSQ_EVE_TYPE_LIST_H_

#include <cstddef>
#include <type_traits>
#include <utility>

namespace unsq_eve {

template <typename ...Ts>
struct type_list
{
  template <typename ... Us>
  constexpr friend type_list<Ts..., Us...> operator+(type_list<Ts...>, type_list<Us...>) { return {}; }
};

template <typename T>
struct is_type_list : std::false_type {};

template <typename ... Ts>
struct is_type_list<type_list<Ts...>> : std::true_type {};

template <typename T>
concept any_type_list = is_type_list<T>::value;

template <any_type_list ...Ts>
constexpr auto concatenate(Ts... type_lists)
{
  return (type_list<>{} + ... + type_lists);
}

template <typename ...Ts>
constexpr auto flatten(type_list<Ts...>)
{
  auto impl = []<typename T> (std::type_identity<T>) {
    if constexpr (any_type_list<T>) return flatten(T{});
    else                            return type_list<T>{};
  };
  return concatenate(impl(std::type_identity<Ts>{}) ... );
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_TYPE_LIST_H_
