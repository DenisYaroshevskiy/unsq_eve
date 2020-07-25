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

TEMPLATE_TEST_CASE("eve_extra.mmask_operations", "[eve_extra]",
                   ALL_TEST_PACKS) {
  using wide = TestType;
  using scalar = typename wide::value_type;
  constexpr std::ptrdiff_t size = wide::static_size;

  wide x{scalar(1)}, y{scalar(2)};

  REQUIRE(0 == extended_movemask(x == y));
  REQUIRE(set_lower_n_bits(size * sizeof(scalar)) == extended_movemask(x != y));

  REQUIRE(0 == extended_movemask(eve::if_not_(x != y)));
  REQUIRE(set_lower_n_bits(size * sizeof(scalar)) ==
          extended_movemask(eve::if_not_(x == y)));
}

}  // namespace
}  // namespace eve_extra
