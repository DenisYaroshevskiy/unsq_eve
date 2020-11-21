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

#include "eve_extra/sort_wide.h"

#include <algorithm>

#include "eve_extra/eve_extra.h"

#include "test/catch.h"
#include "test/eve_extra/common.h"

namespace eve_extra {
namespace {

TEST_CASE("eve_extra.sort_wide", "[eve_extra]") {
  using wide = eve::wide<std::int64_t, eve::fixed<4>>;

  const wide expected = eve_extra::iota(eve::as_<wide>{}) + wide{5};
  wide input = expected;

  do {
    wide actual = eve_extra::sort_4(input);
    INFO("input:    " << input);
    INFO("expected: " << expected);
    INFO("actual:   " << actual);
    REQUIRE(eve::all(expected == actual));

  } while (std::next_permutation(input.begin(), input.end()));
}

}  // namespace
}  // namespace eve_extra
