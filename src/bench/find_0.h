
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

#include "bench/search.h"

namespace bench {

// Benchmarks ------------------------------------------------------

template <typename TestType, typename... Algorithms>
struct find_0_bench : search<TestType, Algorithms...> {
  template <typename T>
  auto input(bench::type_t<T> tgt, std::size_t size,
             std::size_t percentage) const {
    auto res = search<TestType, Algorithms...>::input(tgt, size, percentage);
    std::fill(res.haystack.begin(), res.haystack.end(), 1);
    res.needle = {0};
    res.haystack.back() = 0;
    return res;
  }
};

}  // namespace bench
