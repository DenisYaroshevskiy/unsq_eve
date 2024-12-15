
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

#include "bench/search_121_1111s_bench.h"

#include <algorithm>
#include <cstring>
#include <string_view>

#include "unsq_eve/other_searches.h"

namespace {

struct search_find_equal {
  std::string name() const { return "search find equal"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return unsq_eve::search_find_equal(haystack.begin(), haystack.end(),
                                       needle.begin(), needle.end());
  }
};

struct search_two_loops {
  std::string name() const { return "search two loops"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return unsq_eve::search_two_loops(haystack.begin(), haystack.end(),
                                       needle.begin(), needle.end());
  }
};

struct std_search {
  std::string name() const { return "std::search"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return std::search(haystack.begin(), haystack.end(), needle.begin(),
                       needle.end());
  }
};

struct std_strstr {
  std::string name() const { return "std::strstr"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return std::strstr((const char*)haystack.data(),
                       (const char*)needle.data());
  }
};

struct std_strstr_112 {
  std::string name() const { return "std::strstr112"; }

  void mutate_input(auto& input) const {
    input.needle = {1, 1, 2};
  }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return std::strstr((const char*)haystack.data(),
                       (const char*)needle.data());
  }
};

struct string_view_find_string_view {
  std::string name() const { return "string_view::find"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    std::string_view haystack_sv(reinterpret_cast<const char*>(haystack.data()), haystack.size());
    std::string_view needle_sv(reinterpret_cast<const char*>(needle.data()), needle.size());

    return haystack_sv.find(needle_sv);
  }
};

}  // namespace

int main(int argc, char** argv) {
  using char_bench = bench::search_121_in_1111s_bench<
      std::int8_t, std_strstr, std_strstr_112, string_view_find_string_view, std_search,
      search_find_equal, search_two_loops>;

  using short_bench =
      bench::search_121_in_1111s_bench<short, std_search, search_find_equal,
                                       search_two_loops>;

  using int_bench =
      bench::search_121_in_1111s_bench<int, std_search, search_find_equal,
                                       search_two_loops>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
