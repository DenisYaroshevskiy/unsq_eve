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

#include "unsq_eve/reduce.h"

#include <ostream>

#include <eve/memory/aligned_allocator.hpp>

#include "test/catch.h"

namespace {

template <typename T, std::size_t byte_width, std::size_t _unroll>
struct variation {
  using type = T;

  static constexpr std::size_t bit_witdh = byte_width * 8;
  static constexpr std::size_t unroll = _unroll;

  friend std::ostream& operator<<(std::ostream& out, variation) {
    out << "{sizeof(T): " << sizeof(T) << " byte_width: " << byte_width
        << " unroll: " << unroll << "}";
    return out;
  }
};

template <typename T, typename Variation>
using traits_for =
    unsq_eve::algorithm_traits<T, Variation::bit_witdh, Variation::unroll>;

template <typename Variation, typename Alg>
void specific_tests(Alg alg) {
  using T = typename Variation::type;

  // const T*
  {
    std::vector<T> v(13u, T(1));

    const T* f = v.data();
    const T* l = f + v.size();

    REQUIRE(alg(Variation{}, f, l) == 13);
  }

  // const iterator
  {
    std::vector<T> v(27u, T(1));
    REQUIRE(alg(Variation{}, v.cbegin(), v.cend()) == 27);
  }
}

template <typename Variation, typename Alg>
void common_any_test_impl(Alg alg) {
  INFO("" << Variation{});
  specific_tests<Variation>(alg);

  using T = typename Variation::type;
  std::vector<T, eve::aligned_allocator<T, 4096>> page(4096 / sizeof(T), T{0});

  // 50 from the beginning
  auto* f = page.data();
  auto* l = f + 50;

  auto run = [&]() {
    for (auto* it = f; it < l; ++it) {
      INFO("length: " << (l - f) << " from the beginning: " << it - f);
      int n = l - it;
      int expected = *it * n + n * (n - 1) / 2;
      REQUIRE(expected == alg(Variation{}, it, l));
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

  // 50 from the end
  f = page.data() + page.size() - 50;
  l = page.data() + page.size() - 1;
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
  common_any_test_min_combinations<std::int16_t>(alg);
  common_any_test_traits_combinations<std::int32_t>(alg);
  common_any_test_min_combinations<std::int64_t>(alg);
  common_any_test_min_combinations<float>(alg);
  common_any_test_min_combinations<double>(alg);
}

TEST_CASE("unsq_eve.reduce_basic", "[unsq_eve]") {
  common_any_test([](auto variation, auto f, auto l) {
    if constexpr (sizeof(unsq_eve::value_type<decltype(f)>) == 1) {
      using traits = traits_for<short, decltype(variation)>;
      return unsq_eve::reduce<traits>(f, l, short(0));
    } else {
      using traits =
          traits_for<unsq_eve::value_type<decltype(f)>, decltype(variation)>;
      return unsq_eve::reduce<traits>(f, l);
    }
  });
}

}  // namespace
