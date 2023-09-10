
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

#include "bench/set_intersection.h"

#include <eve/module/algo.hpp>

namespace {

struct eve_set_intersection {
  std::string name() const {
    return "eve::algo::set_intersection";
  }

  BENCH_ALWAYS_INLINE auto operator()(const auto& in1, const auto& in2, auto& out) const {
    auto res =  eve::algo::set_intersection(in1, in2, out);
    return res;
  }
};

}  // namespace

int main(int argc, char** argv) {
  using short_bench = bench::set_intersection_bench<short, eve_set_intersection>;
  using int_bench = bench::set_intersection_bench<int, eve_set_intersection>;

  bench::bench_main<short_bench, int_bench>(argc, argv);
}
