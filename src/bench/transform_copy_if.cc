
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

#include <ranges>

namespace {

struct transform_copy_if_sparse {
  const char* name() const {
    return "eve::algo::transform_copy_if[sparse_output]";
  }

  BENCH_ALWAYS_INLINE auto operator()(auto&& in, auto&& out, auto p) const {
    return eve::algo::transform_copy_if[eve::algo::sparse_output](
        in, out, [p](auto x) { return kumi::tuple{x + x, p(x)}; });
  }
};

struct transform_copy_if_dense {
  const char* name() const {
    return "eve::algo::transform_copy_if[dense_output]";
  }

  BENCH_ALWAYS_INLINE auto operator()(auto&& in, auto&& out, auto p) const {
    return eve::algo::transform_copy_if[eve::algo::dense_output](
        in, out, [p](auto x) { return kumi::tuple{x + x, p(x)}; });
  }
};

struct map_copy_if_sparse {
  const char* name() const {
    return "eve::algo::copy_if[sparse_output](views::map)";
  }

  BENCH_ALWAYS_INLINE auto operator()(auto&& in, auto&& out, auto p) const {
    return eve::algo::copy_if[eve::algo::sparse_output](
        eve::views::map(in, [](auto x) { return x + x; }), out, p);
  }
};

struct map_copy_if_dense {
  const char* name() const {
    return "eve::algo::copy_if[dense_output](views::map)";
  }

  BENCH_ALWAYS_INLINE auto operator()(auto&& in, auto&& out, auto p) const {
    return eve::algo::copy_if[eve::algo::dense_output](
        eve::views::map(in, [](auto x) { return x + x; }), out, p);
  }
};

struct std_transform_copy_if_dense {
  const char* name() const {
    return "std::ranges::copy_if()";
  }

  BENCH_ALWAYS_INLINE auto operator()(auto&& in, auto&& out, auto p) const {
    return std::ranges::copy_if(in, out.begin(), p, [](auto x) { return x + x; });
  }
};

}  // namespace

int main(int argc, char** argv) {
  using int_bench = bench::copy_if_bench<int, transform_copy_if_sparse,
                                         transform_copy_if_dense,
                                         map_copy_if_sparse, map_copy_if_dense,
                                         std_transform_copy_if_dense>;

  bench::bench_main<int_bench>(argc, argv);
}
