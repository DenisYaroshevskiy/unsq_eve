#include <benchmark/benchmark.h>

#include <eve/module/algo.hpp>

#include <algorithm>
#include <cstdint>
#include <random>
#include <span>

namespace {

#define BENCH_NOINLINE __attribute__((noinline))

using Input = std::pair<std::span<const float>, const float*>;

template <std::size_t Size>
BENCH_NOINLINE
Input testData() {
  static const std::vector<float> res = [] {
    std::vector<float> r(Size * 2U, 0.F);
    std::mt19937 gen;
    std::uniform_real_distribution<float> values(0.F, 100.F);
    std::generate(r.begin(), r.end(), [&]() mutable { return values(gen); });
    return r;
  }();
  return {std::span{res.data(), Size}, &res[Size]};
}

BENCH_NOINLINE
float eve_transform_reduce(const float* a, const float* b, std::size_t size) {
  return eve::algo::transform_reduce[eve::algo::fuse_operations](
    eve::views::zip(std::span{a, size}, b),
    [](auto wide_ab, auto sum) {
      auto [wide_a, wide_b] = wide_ab;
      return eve::fma(wide_a, wide_b, sum);
    },
    0.F);
}

BENCH_NOINLINE
float fvec_inner_product(const float* x, const float* y, size_t d) {
    float32x4_t accux4 = vdupq_n_f32(0);
    const size_t d_simd = d - (d & 3);
    size_t i;
    for (i = 0; i < d_simd; i += 4) {
        float32x4_t xi = vld1q_f32(x + i);
        float32x4_t yi = vld1q_f32(y + i);
        accux4 = vfmaq_f32(accux4, xi, yi);
    }
    float32_t accux1 = vaddvq_f32(accux4);
    for (; i < d; ++i) {
        float32_t xi = x[i];
        float32_t yi = y[i];
        accux1 += xi * yi;
    }
    return accux1;
}

BENCH_NOINLINE
float autovectorized(const float* x, const float* y, std::size_t d) {
  float res = 0.F;
  for (size_t i = 0; i != d; ++i) {
_Pragma ("clang fp contract (fast) reassociate(on)")
      res += x[i] * y[i];
  }
  return res;
}

using TwoArraysFunc = float(*)(const float*, const float*, std::size_t);

template <TwoArraysFunc func>
void ipBenchmark(benchmark::State& state) {
  auto input = testData<10'000>();
  for (auto _ : state) {
    benchmark::DoNotOptimize(func(input.first.data(), input.second, input.first.size()));
  }
}

/*
Run on M2

----------------------------------------------------------------------------
Benchmark                                  Time             CPU   Iterations
----------------------------------------------------------------------------
ipBenchmark<eve_transform_reduce>        714 ns          714 ns       788892
ipBenchmark<fvec_inner_product>         2854 ns         2853 ns       251323
ipBenchmark<autovectorized>              715 ns          715 ns       979638
*/
BENCHMARK(ipBenchmark<eve_transform_reduce>);
BENCHMARK(ipBenchmark<fvec_inner_product>);
BENCHMARK(ipBenchmark<autovectorized>);

}  // namespace
