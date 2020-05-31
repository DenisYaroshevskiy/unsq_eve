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

#include "unsq_eve/find.h"

#include <ostream>
#include <string>

#include <eve/memory/aligned_allocator.hpp>

#include "test/catch.h"

namespace {

template <typename T, std::size_t byte_width, std::size_t unroll>
struct variation {
  using type = T;
  using traits = unsq_eve::algorithm_traits<T, byte_width * 8, unroll>;

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

  // const T*
  {
    std::vector<T> v(13u, T(1));
    v.back() = T(2);

    const T* f = v.data();
    const T* l = f + v.size();

    REQUIRE(alg(traits{}, f, l, v.back()) - f == 12);
  }

  // const iterator
  {
    std::vector<T> v(27u, T(1));
    v.back() = T(2);

    REQUIRE(alg(traits{}, v.cbegin(), v.cend(), v.back()) - v.cbegin() == 26);
  }
}

template <typename Variation, typename Alg>
void common_find_test_impl(Alg alg) {
  INFO("" << Variation{});
  specific_tests<Variation>(alg);

  using T = typename Variation::type;
  std::vector<T, eve::aligned_allocator<T, 4096>> page(4096 / sizeof(T), T{0});

  // 50 from the beginning
  auto* f = page.data();
  auto* l = f + 50;

  auto run = [&]() {
    typename Variation::traits traits{};

    for (auto* it = f; it < l; ++it) {
      INFO("length: " << (l - f) << " from the beginning: " << it - f);
      *it = 1;
      REQUIRE(alg(traits, f, l, 1) == it);
      *it = 0;
    }
  };

  while (f < l) {
    run();
    *l = 1;
    --l;
    *f = 1;
    ++f;
  }

  // 50 from the end
  f = page.data() + page.size() - 50;
  l = page.data() + page.size() - 1;

  while (f < l) {
    run();
    *l = 1;
    --l;
    *f = 1;
    ++f;
  }
}

template <typename T, typename Alg>
void common_find_test_traits_combinations(Alg alg) {
  common_find_test_impl<variation<T, 16, 1>>(alg);
  common_find_test_impl<variation<T, 16, 2>>(alg);
  common_find_test_impl<variation<T, 16, 4>>(alg);
  common_find_test_impl<variation<T, 32, 1>>(alg);
  common_find_test_impl<variation<T, 32, 2>>(alg);
  common_find_test_impl<variation<T, 32, 4>>(alg);
}

template <typename Alg>
void common_find_test(Alg alg) {
  common_find_test_traits_combinations<std::int8_t>(alg);
  common_find_test_traits_combinations<std::int16_t>(alg);
  common_find_test_traits_combinations<std::int32_t>(alg);
  common_find_test_traits_combinations<std::int64_t>(alg);
  common_find_test_traits_combinations<float>(alg);
  common_find_test_traits_combinations<double>(alg);
}

TEST_CASE("unsq_eve.find_unguarded", "[unsq_eve]") {
  common_find_test([](auto traits, auto f, auto /*l*/, auto v) {
    return unsq_eve::find_unguarded<decltype(traits)>(f, v);
  });
}

TEST_CASE("unsq_eve.find_found", "[unsq_eve]") {
  common_find_test([](auto traits, auto f, auto l, auto v) {
    return unsq_eve::find<decltype(traits)>(f, l, v);
  });
}

}  // namespace
