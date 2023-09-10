
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

#include <eve/module/algo.hpp>

namespace {

struct eve_copy_if_dense {
  const char* name() const { return "eve::algo::copy_if"; }


  BENCH_ALWAYS_INLINE auto operator()(auto&& in, auto&& out, auto p) const {
    return eve::algo::copy_if(in, out, p);
  }
};

} // namespace

int main(int argc, char** argv) {
  using char_bench = bench::copy_if_bench<std::int8_t, eve_copy_if_dense>;

  using short_bench = bench::copy_if_bench<short, eve_copy_if_dense>;

  using int_bench = bench::copy_if_bench<int, eve_copy_if_dense>;

  bench::bench_main<char_bench, short_bench, int_bench>(argc, argv);
}
