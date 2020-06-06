
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

#include "bench/sum.h"

#include "unsq_eve/reduce.h"

namespace {

template <typename SumType, std::size_t width, std::size_t unroll>
struct unsq_eve_reduce {
  std::string name() const {
    return "unsq_eve::reduce<" + std::to_string(width) + ", " +
           std::to_string(unroll) +
           ">/sum_type:" + bench::type_name<SumType>{}();
  }

  template <typename I>
  SumType operator()(I f, I l) {
    using traits = unsq_eve::algorithm_traits<SumType, width, unroll>;

    return unsq_eve::reduce<traits>(f, l, SumType{0});
  }
};

}  // namespace

int main(int argc, char** argv) {
  using char_2_char_benchmarks =
      bench::sum_bench<char, unsq_eve_reduce<char, 256, 1>,
                       unsq_eve_reduce<char, 256, 4>>;
  using char_2_short_benchmarks =
      bench::sum_bench<char, unsq_eve_reduce<short, 256, 1>,
                       unsq_eve_reduce<short, 256, 4>>;
  using char_2_int_benchmarks =
      bench::sum_bench<char, unsq_eve_reduce<int, 256, 1>,
                       unsq_eve_reduce<int, 256, 4>>;

  using short_2_short_benchmars =
      bench::sum_bench<short, unsq_eve_reduce<short, 256, 4>,
                       unsq_eve_reduce<int, 256, 4>>;

  using int_2_int_benchmarks =
      bench::sum_bench<int, unsq_eve_reduce<int, 256, 4>>;

  bench::bench_main<char_2_char_benchmarks, char_2_short_benchmarks,
                    char_2_int_benchmarks, short_2_short_benchmars,
                    int_2_int_benchmarks>(argc, argv);
}
