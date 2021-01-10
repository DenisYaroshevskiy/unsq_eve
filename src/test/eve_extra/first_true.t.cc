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

  REQUIRE(std::nullopt == eve_extra::first_true(x == y, eve::ignore_none));

  SECTION("ignore nothing") {
    for (int i = size; i != 0; --i) {
      x.set(i - 1, 2);
      auto found = eve_extra::first_true(x == y, eve::ignore_none);
      REQUIRE(found);
      REQUIRE(i - 1 == *found);
    }
  }

  SECTION("ignore first") {
    for (int i = 0; i != size; ++i) {
      auto found = eve_extra::first_true(x == y, eve::ignore_first_{i});
      REQUIRE(!found);

      found = eve_extra::first_true(x == y, eve::ignore_extrema_{i, 0});
      REQUIRE(!found);

      x.set(i, 2);

      found = eve_extra::first_true(x == y, eve::ignore_first_{i});
      REQUIRE(found);
      REQUIRE(i == static_cast<int>(*found));

      found = eve_extra::first_true(x == y, eve::ignore_extrema_{i, 0});
      REQUIRE(found);
      REQUIRE(i == static_cast<int>(*found));

      found = eve_extra::first_true(x == y, eve::ignore_first_{i + 1});
      REQUIRE(!found);

      found = eve_extra::first_true(x == y, eve::ignore_extrema_{i + 1, 0});
      REQUIRE(!found);
    }
  }

  SECTION("ignore last") {
    for (int i = size; i != 0; --i) {
      auto found = eve_extra::first_true(x == y, eve::ignore_last_{size - i});
      REQUIRE(!found);

      found = eve_extra::first_true(x == y, eve::ignore_extrema_{0, size - i});
      REQUIRE(!found);

      x.set(i - 1, 2);

      found = eve_extra::first_true(x == y, eve::ignore_last_{size - i});
      REQUIRE(found);
      REQUIRE(i - 1 == static_cast<int>(*found));

      found = eve_extra::first_true(x == y, eve::ignore_extrema_{0, size - i});
      REQUIRE(found);
      REQUIRE(i - 1 == static_cast<int>(*found));

      found = eve_extra::first_true(x == y, eve::ignore_last_{size - i + 1});
      REQUIRE(!found);

      found =
          eve_extra::first_true(x == y, eve::ignore_extrema_{0, size - i + 1});
      REQUIRE(!found);
    }
  }

  SECTION("ignore_extrema_") {
    x.set(0, 2);
    x.set(1, 2);
    x.set(size - 1, 2);

    eve::ignore_first_ first{2};
    eve::ignore_last_ last{1};

    auto found = eve_extra::first_true(x == y, first && last);

    REQUIRE(!found);
  }
}

}  // namespace
