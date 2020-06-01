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

#ifndef EVE_EXTRA_SCAN_H_
#define EVE_EXTRA_SCAN_H_

#include "eve_extra/concepts.h"

namespace eve_extra {

// [a b c d]
// + [0 a b c]
// [a (a + b) (b + c) (c + d)]
// >> 2 [0 0 a (a + b)]
// [a (a + b) (a + b + c) (a + b + c + d)]

template <native_wide Wide, typename Op>
Wide scan_wide(Wide x, Op op) {
  return x;
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_SCAN_H_
