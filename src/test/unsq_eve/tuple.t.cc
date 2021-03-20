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

#include "unsq_eve/tuple.h"

#include <sstream>

#include "test/catch.h"

namespace {

// basic ==================

TEST_CASE("tuple", "[meta]") {
  constexpr unsq_eve::tuple<int, char, double> x{3, 'a', 0.0};
  static_assert(get<0>(x) == 3);
  static_assert(get<1>(x) == 'a');
  static_assert(get<2>(x) == 0.0);

  unsq_eve::tuple y = x;
  REQUIRE(x == y);
  get<0>(y) = 4;
  REQUIRE(get<0>(y) == 4);
  REQUIRE(x != y);
}

TEST_CASE("tuple: ostream<<", "[meta]") {
  std::stringstream s;
  s << unsq_eve::tuple{3, 'a', 0.0};
  REQUIRE(s.str() == "[3, a, 0]");
}

TEST_CASE("tuple: is lexicographical", "[meta]") {
  unsq_eve::tuple x(1, 2, 3);
  unsq_eve::tuple y(2, 1, 3);
  REQUIRE(x < y);
}

TEST_CASE("tuple: tuple cat", "[meta]") {
  // basic pairs
  {
    constexpr auto test = [](unsq_eve::tuple<int, char> res) {
      return (get<0>(res) == 1) && (get<1>(res) == 'a');
    };

    static_assert(test(tuple_cat(unsq_eve::tuple{1}, unsq_eve::tuple{'a'})));
    static_assert(test(tuple_cat(unsq_eve::tuple{1}, 'a')));
    static_assert(test(tuple_cat(1, unsq_eve::tuple{'a'})));
    static_assert(test(unsq_eve::tuple_cat(1, 'a')));
  }
  // cat multiple
  {
    unsq_eve::tuple<int, char, short, double> res = tuple_cat(
        unsq_eve::tuple<int, char>(1, 'a'), short(3), unsq_eve::tuple{1.0});
    res = tuple_cat(1, unsq_eve::tuple('a', short(3)), unsq_eve::tuple{1.0});
    (void)res;
  }
}

TEST_CASE("tuple: tuple flatten", "[meta]") {
  {
    constexpr unsq_eve::tuple<int, char> x =
        tuple_flatten(unsq_eve::tuple{1, 'a'});
    (void)x;
  }
  {
    constexpr unsq_eve::tuple<int, char, double> x =
        tuple_flatten(unsq_eve::tuple{unsq_eve::tuple{1, 'a'}, 0.3});
    static_assert(get<0>(x) == 1);
    static_assert(get<1>(x) == 'a');
    static_assert(get<2>(x) == 0.3);
  }
  {
    constexpr unsq_eve::tuple<int, char, double> x =
        tuple_flatten(unsq_eve::tuple{1, unsq_eve::tuple{'a', 0.3}});
    static_assert(get<0>(x) == 1);
    static_assert(get<1>(x) == 'a');
    static_assert(get<2>(x) == 0.3);
  }
}

}  // namespace
