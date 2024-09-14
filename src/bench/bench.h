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

#include <tuple>
#include <type_traits>
#include <vector>

#include <benchmark/benchmark.h>

#define BENCH_NOINLINE __attribute__((noinline))
#define BENCH_ALWAYS_INLINE __attribute__((always_inline))

namespace bench {

template <std::size_t n>
using index_c = std::integral_constant<std::size_t, n>;

template <typename... Ts>
struct type_list {};

template <typename T>
struct type_t {
  using type = T;
};

template <typename T>
struct type_name;

template <>
struct type_name<std::int8_t> {
  const char* operator()() const { return "char"; }
};

template <>
struct type_name<short> {
  const char* operator()() const { return "short"; }
};

template <>
struct type_name<int> {
  const char* operator()() const { return "int"; }
};

template <>
struct type_name<float> {
  const char* operator()() const { return "float"; }
};

namespace _bench {

template <typename Op, std::size_t... idx>
constexpr void unroll_impl(Op op, std::index_sequence<idx...>) {
  ((void)op(index_c<idx>{}), ...);
}

template <std::size_t n, typename Op>
constexpr void unroll(Op op) {
  unroll_impl(op, std::make_index_sequence<n>{});
}

template <typename Op, typename... Bs>
void cortesian_product(type_list<>, type_list<Bs...>, Op) {}

template <typename Op, typename A, typename... As, typename... Bs>
void cortesian_product(type_list<A, As...>, type_list<Bs...>, Op op) {
  ((void)op(type_t<A>{}, type_t<Bs>{}), ...);
  cortesian_product(type_list<As...>{}, type_list<Bs...>{}, op);
}

template <typename Op, typename... As, typename... Bs, typename... Cs>
void cortesian_product(type_list<As...> as, type_list<Bs...> bs,
                       type_list<Cs...>, Op op) {
  cortesian_product(
      as, bs, [&](auto a, auto b) { ((void)op(a, b, type_t<Cs>{}), ...); });
}

template <std::size_t... idxs>
constexpr auto do_all_paddings(std::index_sequence<idxs...>) {
  return type_list<index_c<idxs * 8>...>{};
}

constexpr auto all_paddings() {
  return do_all_paddings(std::make_index_sequence<8>{});
}

template <typename BenchmarkDescription, typename Type, typename Algorithm>
std::string benchmark_name(BenchmarkDescription description, std::size_t size,
                           Type, Algorithm algorithm, std::size_t percentage,
                           std::size_t padding) {
  std::string res = std::string("/name:") + description.name();
  res += "/size:" + std::to_string(size);
  res += std::string("/type:") + type_name<typename Type::type>{}();
  res += std::string("/algorithm:") + algorithm.name();
  res += "/percentage:" + std::to_string(percentage);
  res += "/padding:" + std::to_string(padding);
  return res;
}

}  // namespace _bench

template <std::size_t n>
BENCH_ALWAYS_INLINE void noop_slide(index_c<n>) {
  _bench::unroll<n>([](auto) { asm volatile("nop"); });
}

template <typename BenchDescription>
void register_benchmark(BenchDescription description) {
  for (auto size : description.sizes()) {
    _bench::cortesian_product(
        description.types(), description.algorithms(), _bench::all_paddings(),
        [&](auto type, auto algorithm_wrapped, auto padding_wrapped) {
          for (auto percentage : description.percentage_points()) {
            constexpr auto algorithm =
                typename decltype(algorithm_wrapped)::type{};
            constexpr auto padding = typename decltype(padding_wrapped)::type{};

            auto name = _bench::benchmark_name(description, size, type,
                                               algorithm, percentage, padding);

            auto driver = description.driver();
            auto input = description.input(type, size, percentage);

            if constexpr ( requires { algorithm.mutate_input(input); } ) {
              algorithm.mutate_input(input);
            }

            benchmark::RegisterBenchmark(
                name.c_str(), [=](benchmark::State& state) mutable {
                  driver(padding, state, algorithm, input);
                });
          }
        });
  }
}

template <typename... Benchmarks>
int bench_main(int argc, char** argv) {
  benchmark::Initialize(&argc, argv);
  if (benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;

  (bench::register_benchmark(Benchmarks{}), ...);

  benchmark::RunSpecifiedBenchmarks();
  return 0;
}

}  // namespace bench
