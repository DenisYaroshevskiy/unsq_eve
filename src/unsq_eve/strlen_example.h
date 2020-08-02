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

#ifndef UNSQ_EVE_STRLEN_EXAMPLE_H_
#define UNSQ_EVE_STRLEN_EXAMPLE_H_

#include <cstdint>

#include "eve_extra/eve_extra.h"

namespace unsq_eve {

// Simplified implementation of stlren - see find_unguarded for a proper one.
std::size_t strlen_example(const char* s) {
  using wide = eve::wide<char>;

  const wide zeroes{0};

  eve::aligned_ptr aligned_s =
      eve_extra::previous_aligned_address<sizeof(wide)>(s);

  wide cur = eve_extra::load_unsafe(aligned_s, eve::as_<wide>{});
  eve::ignore_first ignore(s - aligned_s.get());

  std::optional match = eve_extra::first_true(cur == zeroes, ignore);

  while (!match) {
    aligned_s += wide::static_size;
    cur = eve_extra::load_unsafe(aligned_s, eve::as_<wide>{});
    match = eve_extra::first_true(cur == zeroes, eve::ignore_none);
  }

  return static_cast<std::size_t>(aligned_s.get() + *match - s);
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_STRLEN_EXAMPLE_H_
