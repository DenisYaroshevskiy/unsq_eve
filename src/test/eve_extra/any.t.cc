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

TEMPLATE_TEST_CASE("eve_extra.any", "[eve_extra]", ALL_TEST_PACKS) {
  using wide = TestType;

  wide x{0}, y{1};

  REQUIRE(!eve_extra::any(x == y, eve::ignore_none));
  x.set(0, 1);
  REQUIRE(eve_extra::any(x == y, eve::ignore_none));
  REQUIRE(!eve_extra::any(x == y, eve::ignore_first{1}));

  SECTION("extra_wide") {
    using T = typename wide::value_type;
    constexpr std::ptrdiff_t size = wide::static_size;

    auto run = [](auto reg) {
      using extra_wide = decltype(reg);

      extra_wide x{0};
      extra_wide y{1};

      REQUIRE(!eve_extra::any(x == y, eve::ignore_none));

      for (auto& elem : x) {
        elem = 1;
        REQUIRE(eve_extra::any(x == y, eve::ignore_none));
        elem = 0;
      }
    };

    run(eve::wide<T, eve::fixed<size>>{});
  }
}

}  // namespace
