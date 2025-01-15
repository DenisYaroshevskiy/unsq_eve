
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

#include "bench/search.h"

#include <algorithm>
#include <cstring>
#include <string_view>

#include "unsq_eve/other_searches.h"

namespace {

struct search_find_equal_22 {
  std::string name() const { return "search_find_equal(22)"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return unsq_eve::search_find_equal(haystack.begin(), haystack.end(),
                                       needle.begin(), needle.end());
  }
};

struct search_find_equal_12 {
  std::string name() const { return "search_find_equal(12)"; }

  void mutate_input(auto& input) const { input.needle = {1, 2}; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return unsq_eve::search_find_equal(haystack.begin(), haystack.end(),
                                       needle.begin(), needle.end());
  }
};

struct search_two_loops_22 {
  std::string name() const { return "search_two_loops(22)"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return unsq_eve::search_two_loops(haystack.begin(), haystack.end(),
                                      needle.begin(), needle.end());
  }
};

struct search_two_loops_12 {
  std::string name() const { return "search_two_loops(12)"; }

  void mutate_input(auto& input) const { input.needle = {1, 2}; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return unsq_eve::search_two_loops(haystack.begin(), haystack.end(),
                                      needle.begin(), needle.end());
  }
};

struct std_search_22 {
  std::string name() const { return "std::search(22)"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return std::search(haystack.begin(), haystack.end(), needle.begin(),
                       needle.end());
  }
};

struct std_search_12 {
  std::string name() const { return "std::search(12)"; }

  void mutate_input(auto& input) const { input.needle = {1, 2}; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return std::search(haystack.begin(), haystack.end(), needle.begin(),
                       needle.end());
  }
};

struct std_strstr_22 {
  std::string name() const { return "std::strstr(22)"; }

  void mutate_input(auto& input) const {
    input.haystack.push_back(0);
    input.needle.push_back(0);
  }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return std::strstr((const char*)haystack.data(),
                       (const char*)needle.data());
  }
};

struct std_strstr_112 {
  std::string name() const { return "std::strstr(112)"; }

  void mutate_input(auto& input) const {
    input.haystack.push_back(0);
    input.needle = {1, 1, 2, 0};
  }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return std::strstr((const char*)haystack.data(),
                       (const char*)needle.data());
  }
};

struct std_strstr_2 {
  std::string name() const { return "std::strstr(112)"; }

  void mutate_input(auto& input) const {
    std::fill(input.haystack.begin(), input.haystack.end(), 1);
    input.haystack.push_back(0);
    input.needle = {2, 0};
  }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return std::strstr((const char*)haystack.data(),
                       (const char*)needle.data());
  }
};

struct string_view_find_string_view_22 {
  std::string name() const { return "string_view::find(22)"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    std::string_view haystack_sv(reinterpret_cast<const char*>(haystack.data()),
                                 haystack.size());
    std::string_view needle_sv(reinterpret_cast<const char*>(needle.data()),
                               needle.size());

    return haystack_sv.find(needle_sv);
  }
};

struct string_view_find_string_view_12 {
  std::string name() const { return "string_view::find(12)"; }

  void mutate_input(auto& input) const { input.needle = {1, 2}; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    std::string_view haystack_sv(reinterpret_cast<const char*>(haystack.data()),
                                 haystack.size());
    std::string_view needle_sv(reinterpret_cast<const char*>(needle.data()),
                               needle.size());

    return haystack_sv.find(needle_sv);
  }
};

template <typename T>
using all_types_searches =
    bench::search<T, search_find_equal_22, search_find_equal_12,
                  search_two_loops_22, search_two_loops_12, std_search_22,
                  std_search_12>;

}  // namespace

int main(int argc, char** argv) {
  using char_special_bench =
      bench::search<std::int8_t, std_strstr_22, std_strstr_112, std_strstr_2,
                    string_view_find_string_view_22,
                    string_view_find_string_view_12>;

  bench::bench_main<char_special_bench, all_types_searches<std::int8_t>,
                    all_types_searches<short>, all_types_searches<int>>(argc,
                                                                        argv);
}
