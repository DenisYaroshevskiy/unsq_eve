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

#ifndef UNSQ_EVE_CONCEPTS_H_
#define UNSQ_EVE_CONCEPTS_H_

#include <iterator>

#include "eve_extra/eve_extra.h"

namespace unsq_eve {

template <std::size_t i>
using indx_c = std::integral_constant<std::size_t, i>;

template <typename Traits>
using width_t = typename Traits::width_type;

template <typename I>
using value_type = typename std::iterator_traits<I>::value_type;

template <typename Op, typename Wide>
concept wide_predicate =
    eve_extra::eve_wide<Wide>&& requires(Op&& op, const Wide& wide) {
  { op(wide) }
  ->eve_extra::eve_logical;
};

template <typename Op, typename Traits, typename I>
concept wide_predicate_for =
    wide_predicate<Op, eve::wide<value_type<I>, width_t<Traits>>>;

}  // namespace unsq_eve

#endif  // UNSQ_EVE_CONCEPTS_H_
