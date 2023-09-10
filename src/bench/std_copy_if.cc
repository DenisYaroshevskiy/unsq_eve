
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

#include "bench/copy_if.h"

namespace {

struct std_copy_if {
  const char* name() const { return "std::copy_if"; }


  BENCH_ALWAYS_INLINE auto operator()(auto&& in, auto&& out, auto p) const {
    return std::copy_if(in.begin(), in.end(), out.begin(), p);
  }
};

} // namespace

int main(int argc, char** argv) {
  using char_bench = bench::copy_if_bench<std::int8_t, std_copy_if>;

  using short_bench = bench::copy_if_bench<short, std_copy_if>;

  using int_bench = bench::copy_if_bench<int, std_copy_if>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
