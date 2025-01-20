/*
 * Copyright 2025 Denis Yaroshevskiy
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

#ifndef UNSQ_EVE_OTHER_MISMATCHES_H_
#define UNSQ_EVE_OTHER_MISMATCHES_H_

#include <algorithm>

#include <eve/module/core.hpp>

namespace unsq_eve {

/*
 * from cpprefernce but cleaned up.
 * https://en.cppreference.com/w/cpp/algorithm/mismatch
 */

template <typename I1, typename I2>
EVE_FORCEINLINE std::pair<I1, I2> mismatch_scalar(I1 f1, I1 l1, I2 f2) {
  while (f1 != l1 && *f1 == *f2) {
    ++f1;
    ++f2;
  }

  return std::make_pair(f1, f2);
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_OTHER_MISMATCHES_H_
