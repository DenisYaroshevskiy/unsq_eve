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

#include <eve/function/all.hpp>

#include "test/catch.h"
#include "test/eve_extra/common.h"

namespace {

template <std::size_t x>
using indx_c = std::integral_constant<std::size_t, x>;

TEMPLATE_TEST_CASE("eve_extra.swap_adjacent_groups", "[eve_extra]",
                   (eve::wide<std::uint64_t, eve::fixed<4>>)) {
  using wide = TestType;

  using T = typename wide::value_type;
  constexpr std::ptrdiff_t size = wide::static_size;

  using extra_wide = eve::wide<T, eve::fixed<size * 4>>;

  const extra_wide x = eve_extra::iota(eve::as_<extra_wide>{});

  auto run = [&]<std::size_t group_size>(indx_c<group_size>) {
    if constexpr (group_size < extra_wide::static_size) {
      const extra_wide actual = eve_extra::swap_adjacent_groups<group_size>(x);
      extra_wide expected = x;

      for (auto f = expected.begin(); f != expected.end();
           f += 2 * group_size) {
        std::swap_ranges(f, f + group_size, f + group_size);
      }
      INFO("group size: " << group_size << "\nexpected: " << expected
                          << "\nactual: " << actual);
      REQUIRE(eve::all(expected == actual));
    }
  };

  run(indx_c<1>{});
  run(indx_c<2>{});
  run(indx_c<4>{});
  run(indx_c<8>{});
  run(indx_c<16>{});
  run(indx_c<32>{});
  run(indx_c<64>{});
}

}  // namespace
