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

#include "unsq_eve/reverse.h"

#include <ostream>

#include <eve/memory/aligned_allocator.hpp>

#include "test/catch.h"

namespace {

template <typename T, std::size_t byte_width, std::size_t unroll>
struct variation {
  using type = T;
  using traits = unsq_eve::algorithm_traits<T, byte_width * 8, unroll>;
  using wide = eve::wide<type, unsq_eve::width_t<traits>>;

  friend std::ostream& operator<<(std::ostream& out, variation) {
    out << "{sizeof(T): " << sizeof(T) << " byte_width: " << byte_width
        << " unroll: " << unroll << "}";
    return out;
  }
};

template <typename Variation, typename Alg>
void specific_tests(Alg alg) {
  using T = typename Variation::type;
  using traits = typename Variation::traits;

  // vector
  {
    std::vector<T> v(13u);

    std::iota(v.begin(), v.end(), T{0});

    std::vector<T> expected = v;
    std::reverse(expected.begin(), expected.end());

    alg(traits{}, v.begin(), v.end());
    REQUIRE(expected == v);
  }
}


template <typename Variation, typename Alg>
void common_any_test_impl(Alg alg) {
  INFO("" << Variation{});
  specific_tests<Variation>(alg);

  using T = typename Variation::type;
  std::vector<T, eve::aligned_allocator<T, eve::fixed<4096 / sizeof(T)>>> page(4096 / sizeof(T), T{0});

  // 50 from the beginning
  auto* f = page.data();
  auto* l = f + 50;

  auto run = [&]() {
    typename Variation::traits traits{};

    std::vector<T> copy{f, l};

    for (auto* it = f; it < l; ++it) {
      INFO("length: " << (l - f) << " from the beginning: " << it - f);

      std::vector<T> expected(l - it);
      std::reverse_copy(it, l, expected.begin());

      alg(traits, it, l);
      std::vector<T> actual{it, l};
      REQUIRE(expected == actual);

      std::copy(copy.begin(), copy.end(), f);
    }
  };

  std::iota(f, l, 0);
  while (f < l) {
    run();
    *l = 1;
    --l;
    *f = 1;
    ++f;
  }
}

template <typename T, typename Alg>
void common_any_test_traits_combinations(Alg alg) {
  common_any_test_impl<variation<T, 16, 1>>(alg);
  common_any_test_impl<variation<T, 16, 2>>(alg);
  common_any_test_impl<variation<T, 16, 4>>(alg);
  common_any_test_impl<variation<T, 32, 1>>(alg);
  common_any_test_impl<variation<T, 32, 2>>(alg);
  common_any_test_impl<variation<T, 32, 4>>(alg);
}

template <typename T, typename Alg>
void common_any_test_min_combinations(Alg alg) {
  common_any_test_impl<variation<T, 32, 4>>(alg);
}

template <typename Alg>
void common_any_test(Alg alg) {
  common_any_test_traits_combinations<std::int8_t>(alg);
  common_any_test_min_combinations<std::uint16_t>(alg);
  common_any_test_traits_combinations<std::int32_t>(alg);
  common_any_test_min_combinations<std::int64_t>(alg);
  common_any_test_min_combinations<float>(alg);
  common_any_test_min_combinations<double>(alg);
}

TEST_CASE("unsq_eve.reverse", "[unsq_eve]") {
  common_any_test([](auto traits, auto f, auto l) {
    unsq_eve::reverse<decltype(traits)>(f, l);
  });
}

}  // namespace
