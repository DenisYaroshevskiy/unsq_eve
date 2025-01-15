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

#include <eve/module/algo.hpp>

namespace {

struct eve_find_if {
  std::string name() const { return "eve::algo::find_if"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return eve::algo::find_if(haystack,
                              [&](auto x) { return x == needle[0]; });
  }
};

struct eve_find_if_no_unrolling {
  std::string name() const { return "eve::algo::find_if[no_unrolling]"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& haystack,
                                      const auto& needle) const {
    return eve::algo::find_if[eve::algo::no_unrolling](
        haystack, [&](auto x) { return x == needle[0]; });
  }
};

}  // namespace

int main(int argc, char** argv) {
  using char_bench = bench::find_0_bench<std::int8_t, eve_find_if, eve_find_if_no_unrolling>;
  using short_bench = bench::find_0_bench<short, eve_find_if, eve_find_if_no_unrolling>;
  using int_bench = bench::find_0_bench<int, eve_find_if, eve_find_if_no_unrolling>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
