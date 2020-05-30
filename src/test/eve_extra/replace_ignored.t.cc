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

#include "eve_extra/eve_extra.h"

#include "test/catch.h"
#include "test/eve_extra/common.h"

namespace {

TEMPLATE_TEST_CASE("eve_extra.replace_ignored", "[eve_extra]", ALL_TEST_PACKS) {
  using wide = TestType;

  const wide x{0}, y{1};

  SECTION("ignore_nothing") {
    wide actual = eve_extra::replace_ignored(x, eve_extra::ignore_nothing{}, y);
    REQUIRE(eve::all(x == actual));
  }

  SECTION("ingore_first_n") {
    for (std::size_t i = 0; i <= wide::static_size; ++i) {
      wide actual =
          eve_extra::replace_ignored(x, eve_extra::ignore_first_n{i}, y);
      wide actual2 =
          eve_extra::replace_ignored(x, eve_extra::ignore_first_last{i, 0}, y);
      REQUIRE(eve::all(actual == actual2));

      for (std::size_t j = 0; j != i; ++j) {
        REQUIRE(actual[j] == 1);
      }
      for (std::size_t j = i; j != wide::static_size; ++j) {
        REQUIRE(actual[j] == 0);
      }
    }
  }

  SECTION("ingore_last_n") {
    for (std::size_t i = 0; i <= wide::static_size; ++i) {
      wide actual =
          eve_extra::replace_ignored(x, eve_extra::ignore_last_n{i}, y);
      wide actual2 =
          eve_extra::replace_ignored(x, eve_extra::ignore_first_last{0, i}, y);

      REQUIRE(eve::all(actual == actual2));

      std::size_t border = wide::static_size - i;

      for (std::size_t j = 0; j != border; ++j) {
        REQUIRE(actual[j] == 0);
      }
      for (std::size_t j = border; j != wide::static_size; ++j) {
        INFO("i: " << i << " j: " << j);
        REQUIRE(actual[j] == 1);
      }
    }
  }

  SECTION("ignore_first_last") {
    eve_extra::ignore_first_n first{2};
    eve_extra::ignore_last_n last{1};

    wide actual =
        eve_extra::replace_ignored(x, eve_extra::combine(first, last), y);
    REQUIRE(actual[0] == 1);
    REQUIRE(actual[1] == 1);
    REQUIRE(actual.back() == 1);

    actual[0] = 0;
    actual[1] = 0;
    actual.back() = 0;

    REQUIRE(eve::all(x == actual));
  }
}

}  // namespace
