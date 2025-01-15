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

#include <eve/module/algo.hpp>

namespace {

struct eve_search_22 {
  std::string name() const { return "eve::algo::search(22)"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return eve::algo::search(haystack, needle);
  }
};

struct eve_search_good_unroll_22 {
  std::string name() const { return "eve::algo::search[unroll<2>](22)"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return eve::algo::search[eve::algo::unroll<2>](haystack, needle);
  }
};

struct eve_search_121 {
  std::string name() const { return "eve::algo::search(121)"; }

  void mutate_input(auto& input) const { input.needle = {1, 2, 1}; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return eve::algo::search(haystack, needle);
  }
};

struct eve_search_2 {
  std::string name() const { return "eve::algo::search(2)"; }

  void mutate_input(auto& input) const {
    std::fill(input.haystack.begin(), input.haystack.end(), 1);
    input.needle = {2};
  }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return eve::algo::search(haystack, needle);
  }
};

template <typename T>
using eve_searches_for_type =
    bench::search<T, eve_search_22, eve_search_good_unroll_22,
                  eve_search_121, eve_search_2>;

}  // namespace

int main(int argc, char** argv) {
  using char_bench = eve_searches_for_type<std::int8_t>;
  using short_bench = eve_searches_for_type<short>;
  using int_bench = eve_searches_for_type<int>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
