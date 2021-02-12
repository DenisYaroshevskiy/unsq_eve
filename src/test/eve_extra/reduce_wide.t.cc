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

#include <eve/function/min.hpp>

#include "test/catch.h"
#include "test/eve_extra/common.h"

namespace {

TEMPLATE_TEST_CASE("eve_extra.reduce_wide", "[eve_extra]", ALL_TEST_PACKS) {
  using wide = TestType;

  using T = typename wide::value_type;
  constexpr std::ptrdiff_t size = wide::static_size;
  using extra_wide = eve::wide<T, eve::fixed<size * 4>>;

  auto run = []<typename Wide>(Wide) {
    const auto input = eve_extra::iota(eve::as_<Wide>{});

    // I'm hardcoding types in the predicates to make sure that we are
    // calling with the correct types.

    // sum
    {
      const T expected = std::accumulate(input.begin(), input.end(), T{0});

      Wide actual = eve_extra::reduce_wide(
          input, [](const Wide& x, const Wide& y) { return x + y; });
      REQUIRE(eve::all(Wide{expected} == actual));
    }

    // min
    {
      const T expected = T{0};

      Wide actual = eve_extra::reduce_wide(
          input, [](const Wide& x, const Wide& y) { return eve::min(x, y); });

      REQUIRE(eve::all(Wide{expected} == actual.get(0)));
    }
  };

  run(wide{});
  run(extra_wide{});
}

}  // namespace
