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
  using traits =
      unsq_eve::iteration_traits<eve::fixed<byte_width / sizeof(T)>, unroll>;

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

  // 16 from the beginning
  auto* f = page.data();
  auto* before_l = f + 16;

  auto run = [&]() {
    typename Variation::traits traits{};
    auto actual = alg(traits, f, before_l + 1, 1);
    REQUIRE(actual - f == before_l - f);
  };

  while (f != before_l + 1) {
    *before_l = 1;
    run();
    --before_l;
  }

  // 16 from the end
  f = page.data() + page.size() - 16;
  before_l = page.data() + page.size() - 1;
  *before_l = 1;
  auto* l = before_l + 1;

  while (f != l) {
    run();
    *f = 1;
    ++f;
  }
}

template <typename T, typename Alg>
void common_find_test_traits_combinations(Alg alg) {
  common_find_test_impl<variation<T, 16, 1>>(alg);
  common_find_test_impl<variation<T, 16, 2>>(alg);
  common_find_test_impl<variation<T, 16, 3>>(alg);
  common_find_test_impl<variation<T, 16, 4>>(alg);
  common_find_test_impl<variation<T, 32, 1>>(alg);
  common_find_test_impl<variation<T, 32, 2>>(alg);
  common_find_test_impl<variation<T, 32, 3>>(alg);
  common_find_test_impl<variation<T, 32, 4>>(alg);
}

template <typename Alg>
void common_find_test(Alg alg) {
  common_find_test_traits_combinations<std::int8_t>(alg);
  common_find_test_traits_combinations<std::uint8_t>(alg);
  common_find_test_traits_combinations<std::int16_t>(alg);
  common_find_test_traits_combinations<std::uint16_t>(alg);
  common_find_test_traits_combinations<std::int32_t>(alg);
  common_find_test_traits_combinations<std::uint32_t>(alg);
  common_find_test_traits_combinations<std::int64_t>(alg);
  common_find_test_traits_combinations<std::uint64_t>(alg);
  common_find_test_traits_combinations<float>(alg);
  common_find_test_traits_combinations<double>(alg);
}

TEST_CASE("unsq_eve.find_unguarded", "[unsq_eve]") {
  common_find_test([](auto traits, auto f, auto /*l*/, auto v) {
    return unsq_eve::find_unguarded<decltype(traits)>(f, v);
  });
}

}  // namespace
