
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

#include "bench/bench.h"

#include <random>

namespace bench {

template <typename T>
struct copy_if_params {
  std::vector<T> in;
  std::vector<T> out;  // in.size() == out.size()
};

struct copy_if_driver {
  template <typename Slide, typename Alg, typename T>
  void operator()(Slide, benchmark::State&, Alg, copy_if_params<T>&) const;
};

template <typename Slide, typename Alg, typename T>
BENCH_NOINLINE void copy_if_driver::operator()(Slide slide,
                                               benchmark::State& state, Alg alg,
                                               copy_if_params<T>& params) const {
  bench::noop_slide(slide);

  auto& [in, out] = params;

  for (auto _ : state) {
    alg(in, out, [](auto x) { return x != 0; });
    benchmark::DoNotOptimize(out);
  }
}

template <typename TestType, typename... Algorithms>
struct copy_if_bench {
  const char* name() const { return "copy not 0s"; }
  copy_if_driver driver() const { return {}; }

  std::vector<std::size_t> sizes() const { return {40, 1000, 10'000}; }

  std::vector<std::size_t> percentage_points() const {
    return {0, 5, 20, 50, 80, 95, 100};
  }

  bench::type_list<Algorithms...> algorithms() const { return {}; }

  bench::type_list<TestType> types() const { return {}; }

  template <typename T>
  copy_if_params<T> input(bench::type_t<T>, std::size_t size,
             std::size_t percentage) const {
    std::size_t size_in_elements = size / sizeof(T);
    std::size_t zeroes = size_in_elements * (100 - percentage) / 100;
    std::vector<T> in(size_in_elements, 1);

    std::fill(in.begin(), in.begin() + zeroes, 0);
    std::shuffle(in.begin(), in.end(), std::mt19937{});

    return copy_if_params<T>{in, std::vector<T>(size_in_elements)};
  }
};

}  // namespace bench
