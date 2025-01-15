
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

#include "bench/find_0.h"

#include <algorithm>
#include <cstring>

#include "unsq_eve/other_searches.h"

namespace {

struct std_strlen {
  const char* name() const { return "std::strlen"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack, const auto&) const {
    return std::strlen((const char*)haystack.data());
  }
};

struct std_find {
  const char* name() const { return "std::find"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return std::find(haystack.begin(), haystack.end(), needle[0]);
  }
};

struct find_unguarded {
  const char* name() const { return "std_::find_unguarded"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    auto f = haystack.begin();
    while (true) {
      if (*f == needle[0]) return f;
      ++f;
    }
  }
};

}  // namespace

int main(int argc, char** argv) {
  using char_bench =
      bench::find_0_bench<std::int8_t, std_strlen, std_find, find_unguarded>;

  using short_bench = bench::find_0_bench<short, std_find, find_unguarded>;

  using int_bench = bench::find_0_bench<int, std_find, find_unguarded>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
