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

#ifndef UNSQ_EVE_SIMD_RANGE_H_
#define UNSQ_EVE_SIMD_RANGE_H_

#include "unsq_eve/simd_base.h"

namespace unsq_eve {

template <typename .... Ts>
struct simd_range {
  using iterator = simd_iterator<Ts...>;

  simd_range() = default;
  simd_range(iterator f, iterator l) : begin_(f), end_(l) {}

  iterator begin() const { return begin_; }
  iterator end() const { return end_; }

 private:
  iterator begin_;
  iterator end_;
};


}  // namespace unsq_eve

#endif  // UNSQ_EVE_SIMD_RANGE_H_