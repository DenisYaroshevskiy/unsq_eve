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

#include <eve/module/algo.hpp>

namespace {

struct eve_search {
  std::string name() const { return "eve::algo::search"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack, const auto& needle) const {
    return eve::algo::search(haystack, needle);
  }
};

}  // namespace

int main(int argc, char** argv) {
  using char_bench = bench::search_121_in_1111s_bench<std::int8_t, eve_search>;
  using short_bench = bench::search_121_in_1111s_bench<short, eve_search>;
  using int_bench = bench::search_121_in_1111s_bench<int, eve_search>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
