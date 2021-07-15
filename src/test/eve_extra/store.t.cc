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

namespace eve_extra {
namespace {

TEMPLATE_TEST_CASE("eve_extra.store", "[eve_extra]", ALL_TEST_PACKS) {
  using wide = TestType;
  using scalar = typename wide::value_type;

  const wide x = eve_extra::iota(eve::as<wide>{}) + wide{5};

  std::array<scalar, wide::size()> actual;
  actual.fill(0);

  auto values_test = [&](std::size_t no_first, std::size_t no_last) {
    std::array<scalar, wide::size()> expected;
    expected.fill(0);

    for (std::size_t i = no_first; i != wide::size() - no_last; ++i) {
      expected[i] = x.get(i);
    }
    REQUIRE(expected == actual);
  };

  SECTION("ignore_none") {
    eve_extra::store(x, actual.data(), eve::ignore_none);
    values_test(0, 0);
  }

  SECTION("ignore_first") {
    for (int i = 0; i != wide::size() + 1; ++i) {
      INFO("i: " << i);
      actual.fill(0);
      eve_extra::store(x, actual.data(), eve::ignore_first{i});
      values_test(i, 0);

      actual.fill(0);
      eve_extra::store(x, actual.data(), eve::ignore_extrema{i, 0});
      values_test(i, 0);
    }
  }

  SECTION("ignore_last") {
    for (int i = 0; i != wide::size() + 1; ++i) {
      INFO("i: " << i);
      actual.fill(0);
      eve_extra::store(x, actual.data(), eve::ignore_last{i});
      values_test(0, i);

      actual.fill(0);
      eve_extra::store(x, actual.data(), eve::ignore_extrema{0, i});
      values_test(0, i);
    }
  }

  SECTION("masks_work") {
    scalar where{1};

    for (int i = 0; i != wide::size(); ++i) {
      eve::ignore_extrema ignore{i,
                                  static_cast<int>(wide::size() - i - 1)};

      store(x, &where - i, ignore);
      REQUIRE(where == x.get(i));
    }
  }
}

}  // namespace
}  // namespace eve_extra
