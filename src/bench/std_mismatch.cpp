
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

#include "bench/mismatch.h"

#include <algorithm>

namespace {

struct std_mismatch {
  std::string name() const { return "std::mismatch"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& r1, const auto& r2) const {
    return std::mismatch(r1.begin(), r1.end(), r2.begin());
  }
};

struct use_int64s {
  std::string name() const { return "use_int64s"; }

  template <typename T>
  BENCH_ALWAYS_INLINE auto operator()(const std::vector<T>& r1,
                                      const std::vector<T>& r2) const {
    constexpr std::size_t step = 8 / sizeof(T);

    std::size_t n = r1.size() / step;

    const auto* p1 = r1.data();
    const auto* p2 = r2.data();

    while (n--) {
      std::uint64_t x, y;
      std::memcpy(&x, p1, 8);
      std::memcpy(&y, p2, 8);

      if (x != y) break;
      p1 += step;
      p2 += step;
    }
    return std::pair{p1, p2};
  }
};

struct std_memcmp {
  std::string name() const { return "std::memcmp"; }

  template <typename T>
  BENCH_ALWAYS_INLINE auto operator()(const std::vector<T>& r1,
                                      const std::vector<T>& r2) const {
    const auto* p1 = r1.data();
    const auto* p2 = r2.data();

    return std::memcmp(p1, p2, r1.size() * sizeof(T))
  }
};

}  // namespace

int main(int argc, char** argv) {
  bench::bench_main<
      bench::mismatch_bench<std::int8_t, std_mismatch, use_int64s, std_memcmp>,
      bench::mismatch_bench<short, std_mismatch, use_int64s, std_memcmp>,
      bench::mismatch_bench<int, std_mismatch, use_int64s, std_memcmp>>(argc,
                                                                        argv);
}
