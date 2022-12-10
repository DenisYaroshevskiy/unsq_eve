
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

#include <eve/algo/reverse.hpp>

namespace {

struct eve_reverse {
  std::string name() const {
    return "eve::algo::reverse";
  }

  template <typename I>
  BENCH_ALWAYS_INLINE void operator()(I f, I l) {
    eve::algo::reverse(eve::algo::as_range(f, l));
  }
};

}

int main(int argc, char** argv) {
  using char_bench =
      bench::inplace_transform_bench<std::int8_t, eve_reverse>;
  using short_bench =
      bench::inplace_transform_bench<short, eve_reverse>;

  using int_bench =
      bench::inplace_transform_bench<int, eve_reverse>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
