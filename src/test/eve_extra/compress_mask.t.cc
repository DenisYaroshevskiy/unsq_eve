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

TEMPLATE_TEST_CASE("simd.pack.compress_mask", "[simd]",
                   (eve::wide<std::int8_t, eve::fixed<16>>),
                   (eve::wide<std::uint8_t, eve::fixed<16>>),
                   (eve::wide<std::int16_t, eve::fixed<8>>),
                   (eve::wide<std::uint16_t, eve::fixed<8>>),
                   (eve::wide<std::int32_t, eve::fixed<8>>),
                   (eve::wide<std::uint32_t, eve::fixed<8>>)) {
  using wide = TestType;
  using logical = eve::logical<wide>;
  using scalar = typename wide::value_type;

  auto element_idxs = eve_extra::iota(eve::as_<wide>{});

  if constexpr (sizeof(scalar) == 2) {
    element_idxs = {0x0100, 0x0302, 0x0504, 0x0706,
                    0x0908, 0x0b0a, 0x0d0c, 0x0f0e};
  }

  logical mask{false};

  auto run_compress = [&] {
    std::uint32_t mmask = extended_movemask(mask);
    if constexpr (sizeof(wide) == 16) {
      return compress_mask_for_shuffle_epi8<scalar>(mmask);
    } else {
      return compress_mask_for_permutevar8x32<scalar>(mmask);
    }
  };

  auto run = [&] {
    wide expected{0};

    std::uint8_t o = 0;
    for (std::uint8_t i = 0; i != wide::static_size; ++i) {
      if (!mask[i]) continue;
      expected.set(o++, element_idxs[i]);
    }

    auto res = run_compress();
    REQUIRE(eve::all(expected == wide{res.first}));
    REQUIRE(o == res.second);
  };

  auto test = [&](auto& self, std::size_t i) mutable {
    if (i == wide::static_size) {
      run();
      return;
    };
    self(self, i + 1);
    mask[i] = true;
    self(self, i + 1);
  };
  test(test, 0);
}

}  // namespace
}  // namespace eve_extra
