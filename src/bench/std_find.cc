
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
    return f + std::strlen((const char*)&*f);
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
  const char* name() const { return "std_::find_unguarded"; }

  template <typename I, typename T>
  BENCH_ALWAYS_INLINE I operator()(I f, I, const T& x) const {
    while (true) {
      if (*f == x) return f;
      ++f;
    }
  }
};

struct search_one {
  const char* name() const { return "std::search"; }

  template <typename I, typename T>
  BENCH_ALWAYS_INLINE I operator()(I f, I l, const T& x) const {
    return std::search(f, l, &x, &x + 1);
  }
};

struct strstr_one {
  std::string name() const { return "strstr"; }

  void mutate_input(auto& input) const {
    auto l = input.data.end();
    *(l - 2) = 1;
  }

  template <typename I, typename T>
  BENCH_ALWAYS_INLINE auto operator()(I f, I, const T&) const {
    char needle[]{1, 0};
    return std::strstr((const char*)&*f, needle);
  }
};

struct string_view_find_string_view_one {
  std::string name() const { return "string_view::find(string_view)"; }

  template <typename I, typename T>
  BENCH_ALWAYS_INLINE auto operator()(I f, I l, const T& v) const {
    std::string_view haystack(reinterpret_cast<const char*>(&*f), l - f);

    std::array<char, 1> needle{static_cast<char>(v)};
    return haystack.find(std::string_view(needle.data(), 1U));
  }
};

}  // namespace

int main(int argc, char** argv) {
  using char_bench =
      bench::find_0_bench<std::int8_t, std_strlen, std_find, find_unguarded,
                          strstr_one, string_view_find_string_view_one,
                          search_one>;

  using short_bench =
      bench::find_0_bench<short, std_find, find_unguarded, search_one>;

  using int_bench =
      bench::find_0_bench<int, std_find, find_unguarded, search_one>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
