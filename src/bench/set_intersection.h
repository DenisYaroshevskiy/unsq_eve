
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

#include <iostream>
#include <random>
#include <tts/tts.hpp>
#include <unordered_set>

namespace bench {

template <typename T>
struct set_intersection_parameters {
  std::vector<T> in1;
  std::vector<T> in2;
  std::vector<T> out;  // out.size() == in1.size()
};

struct set_intersection_driver {
  template <typename Slide, typename Alg, typename T>
  void operator()(Slide, benchmark::State&, Alg,
                  set_intersection_parameters<T>&) const;
};

template <typename Slide, typename Alg, typename T>
BENCH_NOINLINE void set_intersection_driver::operator()(
    Slide slide, benchmark::State& state, Alg alg,
    set_intersection_parameters<T>& params) const {
  bench::noop_slide(slide);

  auto& [in1, in2, out] = params;

  for (auto _ : state) {
    alg(in1, in2, out);
    benchmark::DoNotOptimize(out);
  }
}

// Benchmarks ------------------------------------------------------
//
// elements in in1 are: [0, 10, 20, 30]
// elements in in2 are random from min(in1) to max(in2) and 20% of them
// are repeats from in1
// in1.size() + in2.size() == bytes / sizeof(T)
// persentage - how close we are to even mix.
//              0 - all elements are in in2,
//           100 - half the elements are in in1.

template <typename TestType, typename... Algorithms>
struct set_intersection_bench {
  const char* name() const { return "set_intersection"; }

  set_intersection_driver driver() const { return {}; }

  std::vector<std::size_t> sizes() const { return {480, 2000, 20'000}; }

  std::vector<std::size_t> percentage_points() const {
    return {5, 20, 50, 80, 100};
  }

  bench::type_list<Algorithms...> algorithms() const { return {}; }

  bench::type_list<TestType> types() const { return {}; }

  template <typename T>
  std::vector<T> populate_in_1(std::size_t size) const {
    std::vector<T> res(size);
    T step = (T)(10000 / size * 3);

    for (T x{0}; auto& e : res) {
      e = x;
      x += step;

      if (x > 32000) {
        std::cout << "size: " << size << " x: " << x << std::endl;
        std::terminate();
      }
    }
    return res;
  }

  template <typename T>
  std::vector<T> unique_elements_for_2(std::size_t size, T min, T max) const {
    std::unordered_set<T> seen;

    std::mt19937 gen{0};
    std::uniform_int_distribution<T> dis(min, max);

    while (seen.size() != size) {
      T x = dis(gen);
      if (x % 3 == 0) continue;
      seen.insert(x);
    }

    return std::vector<T>(seen.begin(), seen.end());
  }

  template <typename T>
  std::vector<T> populate_in_2(std::size_t size,
                               const std::vector<T>& in1) const {
    if (in1.size() < 2) {
      std::terminate();
    }
    std::vector<T> res(in1.size() / 5);

    std::sample(in1.begin(), in1.end(), res.begin(), std::ssize(in1) / 5,
                std::mt19937{});

    auto unique_elems =
        unique_elements_for_2(size - res.size(), in1.front(), in1.back());

    res.insert(res.end(), unique_elems.begin(), unique_elems.end());
    std::sort(res.begin(), res.end());

    return res;
  }

  template <typename T>
  void validate(const std::vector<T>& in, std::size_t i) const {
    auto copy = in;
    std::sort(copy.begin(), copy.end());
    copy.erase(std::unique(copy.begin(), copy.end()), copy.end());
    if (copy != in) {
      std::cout << "validate failed, i: " << i << std::endl;
      std::cout << tts::as_string(in) << std::endl;
      std::terminate();
    }
  }

  template <typename T>
  set_intersection_parameters<T> input(bench::type_t<T>, std::size_t size,
                                       std::size_t percentage) const {
    std::size_t size_total = size / sizeof(T);

    std::size_t size_1 = size_total * percentage / 200;
    std::size_t size_2 = size_total - size_1;

    auto in1 = populate_in_1<T>(size_1);
    auto in2 = populate_in_2(size_2, in1);
    auto out = in1;

    validate(in1, 1);
    validate(in2, 2);

    return set_intersection_parameters<T>{std::move(in1), std::move(in2),
                                          std::move(out)};
  }
};

}  // namespace bench
