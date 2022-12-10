
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

#include "bench/remove.h"

#include <eve/algo/remove.hpp>

#include <eve/algo/as_range.hpp>

namespace {

struct eve_remove {
  std::string name() const {
    return "eve::algo::remove";
  }

  template <typename I, typename T>
  BENCH_ALWAYS_INLINE I operator()(I f, I l, const T& v) const {
    return eve::algo::remove(eve::algo::as_range(f, l), v);
  }
};

}  // namespace

int main(int argc, char** argv) {
  using char_bench = bench::remove_bench<std::int8_t, eve_remove>;
  using short_bench = bench::remove_bench<short, eve_remove>;
  using int_bench = bench::remove_bench<int, eve_remove>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
