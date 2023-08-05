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

#include "bench/min.h"

#include <eve/module/algo.hpp>

namespace {

struct eve_min_element {
  std::string name() const { return "eve::algo::min_element"; }

  template <typename I>
  BENCH_ALWAYS_INLINE I operator()(I f, I l) const {
    return eve::algo::min_element(eve::algo::as_range(f, l));
  }
};

struct eve_min_element_single_pass {
  std::string name() const {
    return "eve::algo::min_element[eve::algo::single_pass]";
  }

  template <typename I>
  BENCH_ALWAYS_INLINE I operator()(I f, I l) const {
    return eve::algo::min_element[eve::algo::single_pass](
        eve::algo::as_range(f, l));
  }
};

}  // namespace

int main(int argc, char** argv) {
  using char_bench = bench::min_bench<std::int8_t, eve_min_element, eve_min_element_single_pass>;

  using short_bench = bench::min_bench<short, eve_min_element, eve_min_element_single_pass>;

  using int_bench = bench::min_bench<int, eve_min_element, eve_min_element_single_pass>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
