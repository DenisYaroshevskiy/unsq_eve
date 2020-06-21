
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

#include <algorithm>

namespace {

struct std_transform {
  std::string name() const { return "std::transform"; }

  template <typename I>
  BENCH_ALWAYS_INLINE void operator()(I f, I l) {
    std::transform(f, l, f, [](auto x) { return x + x; });
  }
};

}  // namespace

int main(int argc, char** argv) {
  bench::bench_main<bench::inplace_transform_bench<char, std_transform>,
                    bench::inplace_transform_bench<short, std_transform>,
                    bench::inplace_transform_bench<int, std_transform>>(argc,
                                                                        argv);
}
