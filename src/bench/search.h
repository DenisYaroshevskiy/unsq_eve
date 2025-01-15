
/*
 * Copyright 2024 Denis Yaroshevskiy
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

namespace bench {

template <typename T>
struct search_parameters {
  std::vector<T> haystack;
  std::vector<T> needle;
};

struct search_driver {
  template <typename Slide, typename Alg, typename T>
  void operator()(Slide, benchmark::State&, Alg, search_parameters<T>&) const;
};

template <typename Slide, typename Alg, typename T>
BENCH_NOINLINE void search_driver::operator()(
    Slide slide, benchmark::State& state, Alg alg,
    search_parameters<T>& params) const {
  bench::noop_slide(slide);

  auto& haystack = params.haystack;
  auto& needle = params.needle;

  for (auto _ : state) {
    auto r = alg(haystack, needle);
    benchmark::DoNotOptimize(haystack);
    benchmark::DoNotOptimize(needle);
    benchmark::DoNotOptimize(r);
  }
}

// Benchmarks ------------------------------------------------------
template <typename TestType, typename... Algorithms>
struct search {
  const char* name() const { return "search"; }

  search_driver driver() const { return {}; }

  std::vector<std::size_t> sizes() const { return {40, 1000, 10'000}; }

  std::vector<std::size_t> percentage_points() const { return {100}; }

  bench::type_list<Algorithms...> algorithms() const { return {}; }

  bench::type_list<TestType> types() const { return {}; }

  template <typename T>
  auto input(struct bench::type_t<T>, std::size_t size,
             std::size_t /*percentage*/) const {
    std::size_t size_in_elements = size / sizeof(T);
    search_parameters<T> res;
    res.needle = {2, 2};

    res.haystack.resize(size_in_elements, T(1));
    std::copy_backward(res.needle.begin(), res.needle.end(), res.haystack.end());

    return res;
  }
};

}  // namespace bench
