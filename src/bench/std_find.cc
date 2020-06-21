
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

namespace {

struct std_strlen {
  const char* name() const { return "std::strlen"; }

  template <typename I, typename T>
  BENCH_ALWAYS_INLINE I operator()(I f, I, const T&) const {
    return f + std::strlen(&*f);
  }
};

struct std_find {
  const char* name() const { return "std::find"; }

  template <typename I, typename T>
  BENCH_ALWAYS_INLINE I operator()(I f, I l, const T& x) const {
    return std::find(f, l, x);
  }
};

struct find_unguarded {
  const char* name() const { return "find_unguarded"; }

  template <typename I, typename T>
  BENCH_ALWAYS_INLINE I operator()(I f, I, const T& x) const {
    while (true) {
      if (*f == x) return f;
      ++f;
    }
  }
};

}  // namespace

int main(int argc, char** argv) {
  using char_bench =
      bench::find_0_bench<char, std_strlen, std_find, find_unguarded>;

  using short_bench = bench::find_0_bench<short, std_find, find_unguarded>;

  using int_bench = bench::find_0_bench<int, std_find, find_unguarded>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
