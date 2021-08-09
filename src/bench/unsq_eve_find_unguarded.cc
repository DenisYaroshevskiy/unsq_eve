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

#include "unsq_eve/find.h"

namespace {

template <std::size_t width, std::size_t unroll>
struct unsq_eve_find_unguarded {
  std::string name() const {
    return "unsq_eve::find_unguarded<" + std::to_string(width) + ", " +
           std::to_string(unroll) + '>';
  }

  template <typename I, typename T>
  BENCH_ALWAYS_INLINE I operator()(I f, I, const T& x) const {
    using traits =
        unsq_eve::algorithm_traits<unsq_eve::value_type<I>, width, unroll>;

    return unsq_eve::find_unguarded<traits>(f, x);
  }
};

}  // namespace

int main(int argc, char** argv) {
  using char_bench = bench::find_0_bench<char, unsq_eve_find_unguarded<256, 4>>;

  using short_bench =
      bench::find_0_bench<short, unsq_eve_find_unguarded<256, 4>>;
  using int_bench = bench::find_0_bench<int, unsq_eve_find_unguarded<256, 4>>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
