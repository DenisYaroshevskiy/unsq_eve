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

TEMPLATE_TEST_CASE("eve_extra.concepts", "[eve_extra]", ALL_TEST_PACKS) {
  using wide = TestType;
  using logical = eve::logical<wide>;

  STATIC_REQUIRE(eve_extra::eve_wide<wide>);
  STATIC_REQUIRE(eve_extra::native_wide<wide>);
  STATIC_REQUIRE(eve_extra::eve_logical<logical>);
  STATIC_REQUIRE(eve_extra::native_logical<logical>);

  using T = typename wide::value_type;
  constexpr std::ptrdiff_t size = wide::size();
  using extra_wide = eve::wide<T, eve::fixed<size * 4>>;
  using extra_logical = eve::logical<logical>;

  STATIC_REQUIRE(eve_extra::composite_wide<extra_wide>);
  STATIC_REQUIRE(eve_extra::eve_logical<extra_logical>);
}
