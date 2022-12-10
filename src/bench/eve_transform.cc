
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

#include "bench/inplace_transform.h"

#include <eve/algo/transform.hpp>

namespace {

struct eve_transform_inplace {
  std::string name() const { return "eve::algo::transform_inplace"; }

  template <typename I>
  BENCH_ALWAYS_INLINE void operator()(I f, I l) {
    eve::algo::transform_inplace(eve::algo::as_range(f, l),
                                 [](auto x) { return x + x; });
  }
};

}  // namespace

int main(int argc, char** argv) {
  using char_bench =
      bench::inplace_transform_bench<std::int8_t, eve_transform_inplace>;
  using short_bench =
      bench::inplace_transform_bench<short, eve_transform_inplace>;
  using int_bench = bench::inplace_transform_bench<int, eve_transform_inplace>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
