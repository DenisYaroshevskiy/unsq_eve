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

#ifndef EVE_EXTRA_CONCEPTS_H_
#define EVE_EXTRA_CONCEPTS_H_

#include <type_traits>

#include <eve/eve.hpp>

namespace eve_extra {

template <typename, template <typename ...> typename>
struct specialization_impl : std::false_type {};

template <template <typename ...> typename Template, typename ... Args>
struct specialization_impl<Template<Args...>, Template> : std::true_type {};

template <typename T, template <typename ...> typename Template>
concept specialization = specialization_impl<T, Template>::value;


template <typename T>
concept eve_wide = specialization<T, eve::wide>;

template <typename T>
concept eve_logical = specialization<T, eve::logical>;

template <typename Wide>
concept composite_wide = eve_wide<Wide>&& requires(const Wide& x) {
  {x.storage().segments};
};

template <eve_wide Wide>
constexpr std::size_t element_size_v = sizeof(typename Wide::value_type);

template <eve_wide Wide>
constexpr std::size_t static_byte_size_v =
    Wide::static_size* element_size_v<Wide>;

template <typename Wide>
concept native_wide = eve_wide<Wide> && ((static_byte_size_v<Wide> == 16) ||
                                         (static_byte_size_v<Wide> == 32));

template <typename Wide>
concept wide_16_bytes = eve_wide<Wide>&& static_byte_size_v<Wide> == 16;

template <typename Wide>
concept wide_32_bytes = eve_wide<Wide>&& static_byte_size_v<Wide> == 32;

template <typename Logical>
concept native_logical =
    eve_logical<Logical>&& native_wide<typename Logical::bits_type>;

template <composite_wide Wide>
constexpr std::ptrdiff_t small_size =
    Wide::storage_type::subvalue_type::static_size;

}  // namespace eve_extra

#endif  // EVE_EXTRA_CONCEPTS_H_
