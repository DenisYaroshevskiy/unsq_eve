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

#include "bench/min.h"

#include <eve/function/min.hpp>

#include "unsq_eve/find.h"
#include "unsq_eve/reduce.h"

#include <algorithm>

namespace {

template <typename I>
using make_traits = unsq_eve::algorithm_traits<unsq_eve::value_type<I>, 256, 4>;

struct reduce_min {
  const char* name() const { return "unsq_eve::reduce<256, 4>(min)"; }

  template <typename I>
  BENCH_ALWAYS_INLINE auto operator()(I f, I l) const {
    if (f == l) return unsq_eve::value_type<I>(0);
    return unsq_eve::reduce<make_traits<I>>(f, l, *f, eve::min);
  }
};

struct reduce_find_min {
  const char* name() const { return "unsq_eve::reduce(min)+find<256, 4>"; }

  template <typename I>
  BENCH_ALWAYS_INLINE I operator()(I f, I l) const {
    if (f == l) return l;
    auto value = unsq_eve::reduce<make_traits<I>>(f, l, *f, eve::min);
    return unsq_eve::find<make_traits<I>>(f, l, value);
  }
};

}  // namespace

int main(int argc, char** argv) {
  bench::bench_main<bench::min_bench<char, reduce_min, reduce_find_min>,
                    bench::min_bench<short, reduce_min, reduce_find_min>,
                    bench::min_bench<int, reduce_min, reduce_find_min>>(argc,
                                                                        argv);
}
