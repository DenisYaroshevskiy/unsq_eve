
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

#include "unsq_eve/reverse.h"

namespace {

template <std::size_t width, std::size_t unroll>
struct unsq_eve_reverse {
  std::string name() const {
    return "unsq_eve::reverse<" + std::to_string(width) + ", " +
           std::to_string(unroll) + '>';
  }

  template <typename I>
  BENCH_ALWAYS_INLINE void operator()(I f, I l) {
    using traits =
        unsq_eve::algorithm_traits<unsq_eve::value_type<I>, width, unroll>;

    unsq_eve::reverse<traits>(f, l);
  }
};

}  // namespace

int main(int argc, char** argv) {
  using char_bench =
      bench::inplace_transform_bench<char, unsq_eve_reverse<256, 1>>;
  using short_bench =
      bench::inplace_transform_bench<short, unsq_eve_reverse<256, 1>>;

  using int_bench =
      bench::inplace_transform_bench<int, unsq_eve_reverse<256, 1>>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
