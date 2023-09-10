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

#include <eve/module/algo.hpp>

namespace {

struct eve_mismatch {
  std::string name() const { return "eve::algo::mismatch"; }

  BENCH_ALWAYS_INLINE auto operator()(const auto& r1, const auto& r2) const {
    return eve::algo::mismatch(r1, r2);
  }
};

}  // namespace

int main(int argc, char** argv) {
  bench::bench_main<bench::mismatch_bench<std::int8_t, eve_mismatch>,
                    bench::mismatch_bench<short, eve_mismatch>,
                    bench::mismatch_bench<int, eve_mismatch>>(argc, argv);
}
}
