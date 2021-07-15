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

#include <eve/detail/top_bits.hpp>
#include <eve/function/all.hpp>

#include "test/catch.h"
#include "test/eve_extra/common.h"

#include <ios>

namespace eve_extra {
namespace {

template <typename TestType>
void test_impl(TestType element_idxs) {
  using wide = TestType;
  using logical = eve::logical<wide>;
  using scalar = typename wide::value_type;

  logical mask{false};

  auto run_compress = [&] {
    auto mmask = eve::detail::top_bits(mask);

    if constexpr (sizeof(wide) == 16) {
      return compress_mask_for_shuffle_epi8<scalar>(mmask.storage);
    } else {
      return compress_mask_for_permutevar8x32<scalar>(mmask.storage);
    }
  };

  auto run = [&] {
    wide expected{0};

    std::uint8_t o = 0;
    for (std::uint8_t i = 0; i != wide::size(); ++i) {
      if (!mask.get(i)) continue;
      expected.set(o++, element_idxs.get(i));
    }

    auto res = run_compress();

    INFO("expected: " << std::hex << expected);
    INFO("actual: " << std::hex << wide{res.first});

    REQUIRE(eve::all(expected == wide{res.first}));
    REQUIRE(o == res.second);
  };

  auto test = [&](auto& self, std::size_t i) mutable {
    if (i == wide::size()) {
      run();
      return;
    };
    self(self, i + 1);
    mask.set(i, true);
    self(self, i + 1);
  };
  test(test, 0);
}

TEMPLATE_TEST_CASE("simd.pack.compress_mask2", "[simd]",
                   (eve::wide<std::uint8_t, eve::fixed<16>>),
                   (eve::wide<std::uint16_t, eve::fixed<8>>),
                   (eve::wide<std::uint32_t, eve::fixed<4>>),
                   (eve::wide<std::uint64_t, eve::fixed<2>>)) {
  using wide = TestType;
  using scalar = typename wide::value_type;

  auto element_idxs = eve_extra::iota(eve::as<wide>{});

  if constexpr (sizeof(scalar) == 2) {
    element_idxs = {0x0100, 0x0302, 0x0504, 0x0706,
                    0x0908, 0x0b0a, 0x0d0c, 0x0f0e};
  }

  if constexpr (sizeof(scalar) == 4) {
    element_idxs = {0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c};
  }

  if constexpr (sizeof(scalar) == 8) {
    element_idxs = {0x0706050403020100, 0x0f0e0d0c0b0a0908};
  }

  test_impl(element_idxs);
}

TEMPLATE_TEST_CASE("simd.pack.compress_mask2", "[simd]",
                   (eve::wide<std::uint32_t, eve::fixed<8>>),
                   (eve::wide<std::uint64_t, eve::fixed<4>>)) {
  using wide = TestType;
  using scalar = typename wide::value_type;

  auto element_idxs = eve_extra::iota(eve::as<wide>{});

  if constexpr (sizeof(scalar) == 8) {
    element_idxs = {0x0000'0000'10000'0000, 0x0000'0003'0000'0002,
                    0x0000'0005'0000'0004,  0x0000'0007'0000'0006 };
  }

  test_impl(element_idxs);
}

}  // namespace
}  // namespace eve_extra
