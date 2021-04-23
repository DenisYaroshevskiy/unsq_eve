/*
 * Copyright 2021 Denis Yaroshevskiy
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

#include "unsq_eve/simd_base.h"

#include <eve/conditional.hpp>
#include <eve/function/all.hpp>

#include <vector>

#include "test/catch.h"

namespace {

TEST_CASE("simd_base.common_cordinality", "[unsq_eve]") {
  static_assert(unsq_eve::common_cardinality<char*>() == 32);
  static_assert(unsq_eve::common_cardinality<char*, char*>() == 32);
  static_assert(unsq_eve::common_cardinality<char*, eve::aligned_ptr<short>>() == 16);
  static_assert(unsq_eve::common_cardinality<eve::aligned_ptr<short>, eve::aligned_ptr<char>>() == 16);
}

TEST_CASE("simd_base.basic", "[unsq_eve]") {
  std::vector<int> ints(16u, 0);
  alignas(32u) std::array<char, 32u> aligned_chars;

  std::iota(ints.begin(), ints.end(), 0);
  std::iota(aligned_chars.begin(), aligned_chars.end(), 0);

  auto load_test = [](auto... ptrs) {
    unsq_eve::simd_base it{ptrs...};
    using N = typename decltype(it)::cardinality;

    static_assert(N{}() == 8);

    {
      unsq_eve::tuple loaded = load(it);

      tuple_iter_flat(loaded, []<typename Wide>(Wide e) {
        REQUIRE(eve::all(e == Wide([](int i, int) { return i; })));
      });
    }
    {
      unsq_eve::tuple loaded = load(eve::ignore_none, it);

      tuple_iter_flat(loaded, []<typename Wide>(Wide e) {
        REQUIRE(eve::all(e == Wide([](int i, int) { return i; })));
      });
    }
    {
      unsq_eve::tuple loaded = load(eve::ignore_first(3).else_(-1), it);

      tuple_iter_flat(loaded, []<typename Wide>(Wide e) {
        REQUIRE(eve::all(e == Wide([](int i, int) { return i < 3 ? -1 : i; })));
      });
    }

    {
      unsq_eve::tuple loaded = load(it + 8, eve::lane<8>);

      tuple_iter_flat(loaded, [&]<typename Wide>(Wide e) {
        e -= static_cast<typename Wide::value_type>(N());
        REQUIRE(eve::all(e == Wide([](int i, int) { return i; })));
      });
    }
  };

  load_test(ints.data(), aligned_chars.begin());
  load_test(ints.data(), eve::aligned_ptr<char, 16>{aligned_chars.begin()});
  load_test(ints.data(), eve::aligned_ptr<char, 8>{aligned_chars.begin()});
  load_test(
      unsq_eve::simd_base{ints.data(),
                              eve::aligned_ptr<char, 8>{aligned_chars.begin()}},
      ints.data());
}

}  // namespace
