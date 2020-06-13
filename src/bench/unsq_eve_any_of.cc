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

#include "bench/find_0.h"

#include "unsq_eve/all_any_none.h"

namespace {

template <typename I, std::size_t width, std::size_t unroll>
struct make_traits
    : unsq_eve::algorithm_traits<unsq_eve::value_type<I>, width, unroll> {
  static constexpr bool use_extra_any = true;
};

struct unsq_eve_any_of_128_1 {
  const char* name() const { return "unsq_eve::any_of<128, 1>"; }

  template <typename I, typename T>
  BENCH_ALWAYS_INLINE bool operator()(I f, I l, const T& x) {
    return unsq_eve::any_of_is<make_traits<I, 128, 1>>(f, l, x);
  }
};

struct unsq_eve_any_of_256_1 {
  const char* name() const { return "unsq_eve::any_of<256, 1>"; }

  template <typename I, typename T>
  BENCH_ALWAYS_INLINE bool operator()(I f, I l, const T& x) {
    return unsq_eve::any_of_is<make_traits<I, 256, 1>>(f, l, x);
  }
};

struct unsq_eve_any_of_256_4 {
  const char* name() const { return "unsq_eve::any_of<256, 4>"; }

  template <typename I, typename T>
  BENCH_ALWAYS_INLINE bool operator()(I f, I l, const T& x) {
    return unsq_eve::any_of_is<make_traits<I, 256, 4>>(f, l, x);
  }
};

}  // namespace

int main(int argc, char** argv) {
  bench::bench_main<bench::find_0_bench<
      unsq_eve_any_of_128_1, unsq_eve_any_of_256_1, unsq_eve_any_of_256_4>>(
      argc, argv);
}
