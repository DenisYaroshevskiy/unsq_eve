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

#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>

namespace {

struct eve_reduce_find_min {
  const char* name() const { return "eve::algo::reduce(min)+find"; }

  template <typename I>
  BENCH_ALWAYS_INLINE I operator()(I f, I l) const {
    if (f == l) return l;
    auto r = eve::algo::as_range(f, l);

    auto value = eve::algo::reduce(r, std::pair{eve::min, *f}, *f);
    return eve::algo::find(r, value);
  }
};

}  // namespace

int main(int argc, char** argv) {
  bench::bench_main<bench::min_bench<std::int8_t, eve_reduce_find_min>,
                    bench::min_bench<short, eve_reduce_find_min>,
                    bench::min_bench<int, eve_reduce_find_min>>(argc, argv);
}
