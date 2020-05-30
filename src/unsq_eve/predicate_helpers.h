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

 #ifndef UNSQ_EVE_PREDICATE_HELPERS_H_
 #define UNSQ_EVE_PREDICATE_HELPERS_H_

 #include <eve/eve.hpp>
 #include "unsq_eve/iteration_unguarded.h"

 namespace unsq_eve {

template <typename Traits, typename I, typename U>
auto equal_to(const U& y) {
  using T = value_type<I>;
  using wide = eve::wide<T, width_t<Traits>>;
  wide ys{static_cast<T>(y)};
  return [ys](const wide& xs) { return xs == ys; };
}

 }  // namespace unsq_eve

 #endif  // UNSQ_EVE_PREDICATE_HELPERS_H_
