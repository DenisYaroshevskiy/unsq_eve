
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

#include <numeric>

namespace {

struct std_inclusive_scan {
  std::string name() const { return std::string("std::inclusive_scan"); }

  template <typename I>
  BENCH_ALWAYS_INLINE void operator()(I f, I l) const {
    std::inclusive_scan(f, l, f);
  }
};

}  // namespace

int main(int argc, char** argv) {
  bench::bench_main<bench::inplace_transform_bench<std::int8_t, std_inclusive_scan>,
                    bench::inplace_transform_bench<short, std_inclusive_scan>,
                    bench::inplace_transform_bench<int, std_inclusive_scan>>(
      argc, argv);
}
