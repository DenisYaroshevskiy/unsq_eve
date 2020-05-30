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

TEMPLATE_TEST_CASE("eve_extra.first_true", "[eve_extra]", ALL_TEST_PACKS) {
  using wide = TestType;
  using scalar = typename wide::value_type;
  constexpr std::ptrdiff_t size = wide::static_size;

  wide x{scalar(1)}, y{scalar(2)};

  REQUIRE(std::nullopt ==
          eve_extra::first_true(x == y, eve_extra::ignore_nothing{}));

  SECTION("ignore nothing") {
    for (std::size_t i = size; i != 0; --i) {
      x[i - 1] = scalar(2);
      auto found = eve_extra::first_true(x == y, eve_extra::ignore_nothing{});
      REQUIRE(found);
      REQUIRE(i - 1 == *found);
    }
  }

  SECTION("ignore first n") {
    for (std::size_t i = 0; i != size; ++i) {
      auto found = eve_extra::first_true(x == y, eve_extra::ignore_first_n{i});
      REQUIRE(!found);

      found = eve_extra::first_true(x == y, eve_extra::ignore_first_last{i, 0});
      REQUIRE(!found);

      x[i] = scalar(2);

      found = eve_extra::first_true(x == y, eve_extra::ignore_first_n{i});
      REQUIRE(found);
      REQUIRE(i == *found);

      found = eve_extra::first_true(x == y, eve_extra::ignore_first_last{i, 0});
      REQUIRE(found);
      REQUIRE(i == *found);

      found = eve_extra::first_true(x == y, eve_extra::ignore_first_n{i + 1});
      REQUIRE(!found);

      found =
          eve_extra::first_true(x == y, eve_extra::ignore_first_last{i + 1, 0});
      REQUIRE(!found);
    }
  }

  SECTION("ignore last n") {
    for (std::size_t i = size; i != 0; --i) {
      auto found =
          eve_extra::first_true(x == y, eve_extra::ignore_last_n{size - i});
      REQUIRE(!found);

      found = eve_extra::first_true(x == y,
                                    eve_extra::ignore_first_last{0, size - i});
      REQUIRE(!found);

      x[i - 1] = scalar(2);

      found = eve_extra::first_true(x == y, eve_extra::ignore_last_n{size - i});
      REQUIRE(found);
      REQUIRE(i - 1 == *found);

      found = eve_extra::first_true(x == y,
                                    eve_extra::ignore_first_last{0, size - i});
      REQUIRE(found);
      REQUIRE(i - 1 == *found);

      found =
          eve_extra::first_true(x == y, eve_extra::ignore_last_n{size - i + 1});
      REQUIRE(!found);

      found = eve_extra::first_true(
          x == y, eve_extra::ignore_first_last{0, size - i + 1});
      REQUIRE(!found);
    }
  }

  SECTION("ignore_first_last") {
    x[0] = scalar(2);
    x[1] = scalar(2);
    x[size - 1] = scalar(2);

    eve_extra::ignore_first_n first{2};
    eve_extra::ignore_last_n last{1};

    auto found = eve_extra::first_true(x == y, eve_extra::combine(first, last));

    REQUIRE(!found);
    found = eve_extra::first_true(x == y, eve_extra::combine(last, first));
    REQUIRE(!found);
  }
}

}  // namespace
