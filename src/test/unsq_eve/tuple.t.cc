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
      return
    };

    constexpr basic = tuple_cat(unsq_eve::tuple{1}, unsq_eve::tuple{'a'})));
    static_assert(get<0>(res) == 1);
    static_assert(get<1>(res) == 'a');
  }
  // cat multiple
  {
    unsq_eve::tuple<int, char, short, double> res = tuple_cat(
        unsq_eve::tuple{1, 'a'}, unsq_eve::tuple{short(3)}, unsq_eve::tuple{1.0});
    res = tuple_cat(unsq_eve::tuple{1}, unsq_eve::tuple('a', short(3)), unsq_eve::tuple{1.0});
    (void)res;
  }
}

TEST_CASE("tuple: tuple_flatten", "[meta]") {
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

TEST_CASE("tuple: tuple_flat_ref", "[meta]") {
  {
    constexpr auto impl_mutable = [] {
      unsq_eve::tuple x{1, 'a'};
      unsq_eve::tuple<int&, char&> res = tuple_flat_ref(x);
      bool first_test = (get<0>(res) == 1 && get<1>(res) == 'a');

      get<1>(res) = 'b';
      bool second_test = (get<1>(x) == 'b');

      return first_test && second_test;
    };
    static_assert(impl_mutable());

    constexpr auto impl_const = [] {
      const unsq_eve::tuple x{1, 'a'};
      unsq_eve::tuple<const int&, const char&> res = tuple_flat_ref(x);
      return (get<0>(res) == 1 && get<1>(res) == 'a');
    };
    static_assert(impl_const());
  }
  // flattening
  {
    constexpr auto impl = [] {
      unsq_eve::tuple x{ unsq_eve::tuple{1, 'a'}, unsq_eve::tuple{'a', 1}};
      unsq_eve::tuple<int&, char&, char&, int&> ref = tuple_flat_ref(x);
      get<0>(ref) = 2;
      get<2>(ref) = 'b';

      return get<0>(x) == unsq_eve::tuple{2, 'a'} &&
             get<1>(x) == unsq_eve::tuple{'b', 1};
    };
    static_assert(impl());
  }
}

TEST_CASE("tuple: tuple_cast", "[meta]") {
  using t1 = unsq_eve::tuple<int, char, double>;
  using t2 = unsq_eve::tuple<unsq_eve::tuple<int, char>, double>;
  using t3 = unsq_eve::tuple<t1>;
  using t4 = unsq_eve::tuple<unsq_eve::tuple<t3>>;

  auto impl = [](auto in) {
    constexpr auto values_test = [](auto converted) {
      auto flat = unsq_eve::tuple_flatten(converted);
      return (flat == unsq_eve::tuple{1, 'a' , 0.5});
    };

    return values_test(tuple_cast<t1>(in)) &&
           values_test(tuple_cast<t2>(in)) &&
           values_test(tuple_cast<t3>(in)) &&
           values_test(tuple_cast<t4>(in));
  };

  constexpr t1 x1{1, 'a', 0.5};
  static_assert(impl(x1));

  constexpr t2 x2{unsq_eve::tuple{1, 'a'}, 0.5};
  static_assert(impl(x2));

  constexpr t3 x3{x1};
  static_assert(impl(x3));

  constexpr t4 x4{unsq_eve::tuple<unsq_eve::tuple<t3>>{unsq_eve::tuple<t3>{x3}}};
  static_assert(impl(x4));
}

TEST_CASE("tuple: tuple_cast_to", "[meta]") {
   constexpr auto impl = [] {
     unsq_eve::tuple x{ unsq_eve::tuple{1, 'a'}, 0.5, 1};
     unsq_eve::tuple<unsq_eve::tuple<int, char, double>, int> y;
     unsq_eve::tuple_cast_to(y, x);
     return get<0>(y) == unsq_eve::tuple{1, 'a', 0.5} && get<1>(y) == 1;
   };
   static_assert(impl());
}

}  // namespace
