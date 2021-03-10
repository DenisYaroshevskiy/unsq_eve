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

#include <array>
#include <numeric>

#include <eve/function/any.hpp>
#include <eve/function/all.hpp>
#include <eve/function/load.hpp>
#include <eve/function/store.hpp>

#include "test/catch.h"
#include "test/eve_extra/common.h"

namespace {

TEST_CASE("eve_extra.load_const_aligned_ptr", "[eve_extra]") {
  using wide = eve::wide<char, eve::fixed<16>>;
  alignas(wide) std::array<char, 16> data;
  data.fill(1);

  eve::aligned_ptr<char, 16> ptr{data.begin()};
  wide loaded = eve::load(ptr, eve::fixed<16>{});

  REQUIRE(eve::all(loaded == wide{1}));
}

TEMPLATE_TEST_CASE("eve_extra.constatns", "[eve_extra]", ALL_TEST_PACKS) {
  using wide = TestType;

  SECTION("iota") {
    wide x;
    std::iota(x.begin(), x.end(), 0);
    auto actual = eve_extra::iota(eve::as_<wide>{});
    REQUIRE(eve::all(x == actual));
  }
}

}  // namespace
