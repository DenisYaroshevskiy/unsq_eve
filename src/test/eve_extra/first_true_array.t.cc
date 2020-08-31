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

TEMPLATE_TEST_CASE("eve_extra.first_true_array", "[eve_extra]",
                   (eve::wide<std::int8_t, eve::fixed<16>>)) {
  using wide = TestType;
  using logical = eve::logical<wide>;

  auto run = [&](auto test) {
    wide x{0}, y{1};

    test.fill(x == y);

    using namespace eve_extra;
    REQUIRE(!first_true_array(test));

    x.set(1, 1);

    for (std::size_t i = 0; i != test.size(); ++i) {
      test[i] = (x == y);
      std::uint32_t expected = (wide::static_size * i) + 1;
      REQUIRE(first_true_array(test));
      REQUIRE(*first_true_array(test) == expected);
      test[i] = (x != x);
    }
  };

  run(std::array<logical, 1>{});
  run(std::array<logical, 2>{});
  run(std::array<logical, 4>{});
}

}  // namespace
