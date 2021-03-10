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

#include <numeric>

#include <eve/function/all.hpp>

#include "test/catch.h"
#include "test/eve_extra/common.h"

namespace {

TEMPLATE_TEST_CASE("eve_extra.inclusive_scan", "[eve_extra]", ALL_TEST_PACKS) {
  using wide = TestType;

  const wide in = eve_extra::iota(eve::as_<wide>()) + wide{1};
  const wide zero{0};

  wide expected;
  std::inclusive_scan(in.begin(), in.end(), expected.begin());

  const wide actual = eve_extra::inclusive_scan_wide(
      in, [](wide x, wide y) { return x + y; }, zero);

  INFO("expected: " << expected << " actual: " << actual);
  REQUIRE(eve::all(expected == actual));
}

}  // namespace
