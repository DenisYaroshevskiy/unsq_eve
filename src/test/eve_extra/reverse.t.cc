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

#include <algorithm>

#include <eve/function/all.hpp>

#include "test/catch.h"
#include "test/eve_extra/common.h"

namespace eve_extra {
namespace {

TEMPLATE_TEST_CASE("eve_extra.reverse", "[eve_extra]", ALL_TEST_PACKS) {
  using wide = TestType;

  wide input = eve_extra::iota(eve::as_<wide>{});

  wide expected;
  std::reverse_copy(input.begin(), input.end(), expected.begin());

  wide actual = eve_extra::reverse(input);

  INFO("expected: " << expected << " actual: " << actual);
  REQUIRE(eve::all(expected == actual));
}
}  // namespace
}  // namespace eve_extra
