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

#include "unsq_eve/min_element.h"

#include <ostream>
#include <string>

#include <eve/memory/aligned_allocator.hpp>

#include <tts/tts.hpp>

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
    std::vector<T> v(13u, T(5));
    v.back() = T(2);

    const T* f = v.data();
    const T* l = f + v.size();

    TTS_EXPECT(alg(traits{}, f, l) - f == 12);
  }

  // const iterator
  {
    std::vector<T> v(27u, T(2));
    v[0] = 1;

    TTS_EXPECT(alg(traits{}, v.cbegin(), v.cend()) - v.cbegin() == 0);
  }
}

template <typename Variation, typename Alg>
void common_min_test_impl(Alg alg) {
  specific_tests<Variation>(alg);

  using T = typename Variation::type;
  std::vector<T, eve::aligned_allocator<T, eve::fixed<4096 / sizeof(T)>>> page(4096 / sizeof(T), T{1});

  // 300 from the beginning for chars

  std::ptrdiff_t n = std::is_same_v<T, char> ? 300 : 50;

  auto* f = page.data();
  auto* l = f + n;

  auto run = [&]() {
    typename Variation::traits traits{};

    for (auto* it = f; it < l; ++it) {
      *it = 1;
      auto expected = it - f;
      auto actual = alg(traits, f, l) - f;
      TTS_EXPECT(expected == actual);
      *it = 2;
    }
    std::fill(f, l, 1);
  };

  while (f < l) {
    run();
    *l = 1;
    --l;
    *f = 1;
    ++f;
  }

  // n from the end
  f = page.data() + page.size() - n;
  l = page.data() + page.size() - 1;

  while (f < l) {
    run();
    --l;
    ++f;
  }
}

template <typename T, typename Alg>
void common_min_test_traits_combinations(Alg alg) {
  common_min_test_impl<variation<T, 16, 1>>(alg);
  common_min_test_impl<variation<T, 16, 2>>(alg);
  common_min_test_impl<variation<T, 16, 4>>(alg);
  common_min_test_impl<variation<T, 32, 1>>(alg);
  common_min_test_impl<variation<T, 32, 2>>(alg);
  common_min_test_impl<variation<T, 32, 4>>(alg);
}

template <typename T, typename Alg>
void common_min_test_min_combinations(Alg alg) {
  common_min_test_impl<variation<T, 32, 4>>(alg);
}

template <typename Alg>
void common_min_test(Alg alg) {
  common_min_test_traits_combinations<std::int8_t>(alg);
  common_min_test_min_combinations<std::int16_t>(alg);
  common_min_test_traits_combinations<std::int32_t>(alg);
  common_min_test_min_combinations<std::int64_t>(alg);
  common_min_test_min_combinations<float>(alg);
  common_min_test_min_combinations<double>(alg);
}

TTS_CASE("unsq_eve.min_element") {
  common_min_test([](auto traits, auto f, auto l) {
    return unsq_eve::min_element<decltype(traits)>(f, l);
  });
};

}  // namespace
