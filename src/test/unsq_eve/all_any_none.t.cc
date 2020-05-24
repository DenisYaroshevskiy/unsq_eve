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

#include "unsq_eve/all_any_none.h"

#include <ostream>
#include <string>

#include <eve/memory/aligned_allocator.hpp>

#include "test/catch.h"

namespace {

template <typename T, std::size_t byte_width, std::size_t unroll>
struct variation {
  using type = T;
  using traits = unsq_eve::iteration_traits<eve::fixed<byte_width / sizeof(T)>, unroll>;
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

  // const T*
  {
    std::vector<T> v(13u, T(1));
    v.back() = T(2);

    const T* f = v.data();
    const T* l = f + v.size();

    REQUIRE(alg(traits{}, f, l, 2));
    REQUIRE(!alg(traits{}, f, l, 5));
  }

  // const iterator
  {
    std::vector<T> v(27u, T(1));
    v.back() = T(2);

    REQUIRE(alg(traits{}, v.cbegin(), v.cend(), v.back()));
  }
}

template <typename Variation, typename Alg>
void common_any_test_impl(Alg alg) {
  INFO("" << Variation{});
  specific_tests<Variation>(alg);

  using T = typename Variation::type;
  std::vector<T, eve::aligned_allocator<T, 4096>> page(4096 / sizeof(T), T{0});

  auto aligned_address = [](T* ptr) {
    using wide = typename Variation::wide;
    return eve_extra::previous_aligned_address(eve::as_<wide>{}, ptr).get();
  };

  // 50 from the beginning
  auto* f = page.data();
  auto* l = f + 50;

  auto run = [&]() {
    typename Variation::traits traits{};

    for (auto* it = f + 16; it < l; ++it) {
      INFO("length: " << (l - f) << " from the beginning: " << it - f);
      INFO("previous aligned f: " << (std::uint64_t)aligned_address(f)
                                  << " previous aligned l: "
                                  << (std::uint64_t)aligned_address(l));
      REQUIRE(!alg(traits, f, l, 1));

      *it = 1;
      REQUIRE(alg(traits, f, l, 1));
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

TEST_CASE("unsq_eve.any", "[unsq_eve]") {
  common_any_test([](auto traits, auto f, auto l, auto v) {
    return unsq_eve::any_of_is<decltype(traits)>(f, l, v);
  });
}

}  // namespace
