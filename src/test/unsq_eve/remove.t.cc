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

#include "unsq_eve/remove.h"

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
    std::vector<T> expected(10u, T(1));
    v[5u] = T(2);
    v[7u] = T(2);
    v[11u] = T(2);

    v.erase(alg(Variation{}, v.begin(), v.end(), 2), v.end());
    REQUIRE(expected == v);
  }
}

template <typename Variation, typename Alg>
void common_remove_test_impl(Alg alg) {
  INFO("" << Variation{});
  specific_tests<Variation>(alg);

  using T = typename Variation::type;
  std::vector<T, eve::aligned_allocator<T, 4096>> page(4096 / sizeof(T), T{0});

  // 50 from the beginning
  auto* f = page.data();
  auto* l = f + 50;

  auto prepopulate = [&](auto it) {
    std::fill(it, l, 0);

    std::ptrdiff_t count = 0;

    while (it + 1 < l) {
      *it = 1;
      ++count;
      it += 2;
    }

    return count;
  };

  auto run = [&]() {
    for (auto* it = f; it < l; ++it) {
      INFO("length: " << (l - f) << " from the beginning: " << it - f);
      std::ptrdiff_t count = prepopulate(it);
      auto end = alg(Variation{}, it, l, 0);
      REQUIRE(count == end - it);

      std::vector<T> expected_prefix = std::vector<T>(it - f, 0);
      REQUIRE(expected_prefix == std::vector<T>(f, it));

      std::vector<T> expected_suffix = std::vector<T>(count, 1);
      REQUIRE(expected_suffix == std::vector<T>(it, end));

      *it = 0;

      if (l - page.data() != static_cast<std::ptrdiff_t>(page.size())) {
        REQUIRE(*l == T{0});
      }
    }
  };

  while (f < l) {
    run();
    *l = 0;
    --l;
    *f = 0;
    ++f;
  }

  // 50 from the end
  f = page.data() + page.size() - 50;
  l = page.data() + page.size() - 1;

  while (f < l) {
    run();
    *l = 0;
    --l;
    *f = 0;
    ++f;
  }
}

template <typename T, typename Alg>
void common_remove_test_traits_combinations(Alg alg) {
  common_remove_test_impl<variation<T, 16, 1>>(alg);
  common_remove_test_impl<variation<T, 16, 2>>(alg);
  common_remove_test_impl<variation<T, 16, 4>>(alg);
  common_remove_test_impl<variation<T, 32, 1>>(alg);
  common_remove_test_impl<variation<T, 32, 2>>(alg);
  common_remove_test_impl<variation<T, 32, 4>>(alg);
}

template <typename T, typename Alg>
void common_remove_test_min_combinations(Alg alg) {
  common_remove_test_impl<variation<T, 32, 4>>(alg);
}

template <typename Alg>
void common_remove_test(Alg alg) {
  common_remove_test_traits_combinations<std::int8_t>(alg);
  common_remove_test_min_combinations<std::int16_t>(alg);
  common_remove_test_traits_combinations<std::int32_t>(alg);
  common_remove_test_min_combinations<std::int64_t>(alg);
  common_remove_test_min_combinations<float>(alg);
  common_remove_test_min_combinations<double>(alg);
}

TEST_CASE("unsq_eve.remove", "[unsq_eve]") {
  common_remove_test([](auto variation, auto f, auto l, auto x) {
    using traits = typename decltype(variation)::traits;
    return unsq_eve::remove<traits>(f, l, x);
  });
}

}  // namespace
