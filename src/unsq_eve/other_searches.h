/*
 * Copyright 2024 Denis Yaroshevskiy
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

#ifndef UNSQ_EVE_OTHER_SUBSTRINGS_H_
#define UNSQ_EVE_OTHER_SUBSTRINGS_H_

#include <algorithm>

#include <eve/module/core.hpp>

namespace unsq_eve {

/*
 * These are just for baselines
 */

template <std::random_access_iterator I1, std::random_access_iterator I2>
EVE_FORCEINLINE I1 search_find_equal(I1 f1, I1 l1, I2 f2, I2 l2) {
  if (f2 == l2) return f1;
  if (l2 - f2 > l1 - f1) return l1;

  I1 lf1 = l1 - (l2 - f2) + 1;

  while (true) {
    f1 = std::find(f1, lf1, *f2);
    if (f1 == lf1) return l1;
    if (std::equal(f2 + 1, l2, f1 + 1)) return f1;
    ++f1;
  }
}

template <std::random_access_iterator I1, std::random_access_iterator I2>
EVE_FORCEINLINE I1 search_two_loops(I1 f1, I1 l1, I2 f2, I2 l2) {
  if (f2 == l2) return f1;
  if (l2 - f2 > l1 - f1) return l1;

  I1 lf1 = l1 - (l2 - f2) + 1;

  auto verify = [&] {
    I1 cmp1 = f1;
    I2 cmp2 = f2;

    while (true) {
      if (*cmp1 != *cmp2) return false;
      ++cmp1;
      ++cmp2;
      if (cmp2 == l2) return true;
    }
  };

  while (f1 != lf1) {
    if (verify()) return f1;
    ++f1;
  }
  return l1;
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_OTHER_SUBSTRINGS_H_
