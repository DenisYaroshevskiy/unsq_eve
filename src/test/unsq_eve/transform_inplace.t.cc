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

#include "unsq_eve/transform.h"

#include <ostream>

#include <eve/memory/aligned_allocator.hpp>

#include "test/catch.h"

namespace {

template <typename T, std::size_t byte_width, std::size_t _unroll>
struct variation {
  using type = T;

  static constexpr std::size_t bit_witdh = byte_width * 8;
  static constexpr std::size_t unroll = _unroll;

  using traits = unsq_eve::algorithm_traits<type, bit_witdh, unroll>;

  friend std::ostream& operator<<(std::ostream& out, variation) {
    out << "{sizeof(T): " << sizeof(T) << " byte_width: " << byte_width
        << " unroll: " << unroll << "}";
    return out;
  }
};

template <typename Variation, typename Alg>
void specific_tests(Alg alg) {
  using T = typename Variation::type;

  // vector
  {
    std::vector<T> v(13u, T(1));
    std::vector<T> expected(13u, T(2));

    alg(Variation{}, v.begin(), v.end());
    REQUIRE(expected == v);
  }
}

template <typename Variation, typename Alg>
void common_transform_test_impl(Alg alg) {
  INFO("" << Variation{});
  specific_tests<Variation>(alg);
  using T = typename Variation::type;
  std::vector<T, eve::aligned_allocator<T, eve::fixed<4096 / sizeof(T)>>> page(4096 / sizeof(T), T{1});

  // 50 from the beginning
  auto* f = page.data();
  auto* l = f + 50;
  auto* page_end = f + page.size();

  auto run = [&] {
    for (auto* it = f; it < l; ++it) {
      INFO("length: " << (l - f) << " from the beginning: " << it - f);

      std::vector<T> expected(static_cast<std::size_t>(l - it), T(2));
      alg(Variation{}, it, l);

      if (it != f) REQUIRE(*f == T(1));
      if (l != page_end) REQUIRE(*l == T(1));

      REQUIRE(expected == std::vector<T>(it, l));
      std::fill(it, l, 1);
    }
  };

  while (f < l) {
    run();
    --l;
    ++f;
  }

  // 50 from the end
  f = page.data() + page.size() - 50;
  l = page.data() + page.size() - 1;

  while (f < l) {
    run();
    --l;
    ++f;
  }
}

template <typename T, typename Alg>
void common_transform_test_traits_combinations(Alg alg) {
  common_transform_test_impl<variation<T, 16, 1>>(alg);
  common_transform_test_impl<variation<T, 16, 2>>(alg);
  common_transform_test_impl<variation<T, 16, 4>>(alg);
  common_transform_test_impl<variation<T, 32, 1>>(alg);
  common_transform_test_impl<variation<T, 32, 2>>(alg);
  common_transform_test_impl<variation<T, 32, 4>>(alg);
}

template <typename T, typename Alg>
void common_transform_test_min_combinations(Alg alg) {
  common_transform_test_impl<variation<T, 32, 4>>(alg);
}

template <typename Alg>
void common_transform_test(Alg alg) {
  common_transform_test_traits_combinations<std::int8_t>(alg);
  common_transform_test_min_combinations<std::int16_t>(alg);
  common_transform_test_traits_combinations<std::int32_t>(alg);
  common_transform_test_min_combinations<std::int64_t>(alg);
  common_transform_test_min_combinations<float>(alg);
  common_transform_test_min_combinations<double>(alg);
}

TEST_CASE("unsq_eve.transform_inplace_basic", "[unsq_eve]") {
  common_transform_test([](auto variation, auto f, auto l) {
    using traits = typename decltype(variation)::traits;
    using wide = typename traits::wide;
    unsq_eve::transform<traits>(f, l, [](wide x) { return x + x; });
  });
}

}  // namespace
