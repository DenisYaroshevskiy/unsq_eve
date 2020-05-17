
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
  I operator()(I f, I, const T&) {
    return f + std::strlen(&*f);
  }
};

struct std_find {
  const char* name() const { return "std::find"; }

  template <typename I, typename T>
  I operator()(I f, I l, const T& x) {
    return std::find(f, l, x);
  }
};

struct find_unguarded {
  const char* name() const { return "find_unguarded"; }

  template <typename I, typename T>
  I operator()(I f, I, const T& x) {
    while (true) {
      if (*f == x) return f;
      ++f;
    }
  }
};

struct strlen_bench : bench::find_0_bench<std_strlen> {
  bench::type_list<char> types() const { return {}; }
};

}  // namespace

int main(int argc, char** argv) {
  bench::bench_main<bench::find_0_bench<std_find, find_unguarded>,
                    strlen_bench>(argc, argv);
}
