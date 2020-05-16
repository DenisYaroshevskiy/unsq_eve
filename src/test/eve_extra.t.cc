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
#include <eve/function/load.hpp>
#include <eve/function/store.hpp>

#include "test/catch.h"

namespace {

#define ALL_TEST_PACKS                                                      \
  (eve::wide<std::int8_t, eve::fixed<16>>),                                 \
      (eve::wide<std::int8_t, eve::fixed<32>>),                             \
      (eve::wide<std::uint8_t, eve::fixed<16>>),                            \
      (eve::wide<std::uint8_t, eve::fixed<32>>),                            \
      (eve::wide<std::int16_t, eve::fixed<8>>),                             \
      (eve::wide<std::int16_t, eve::fixed<16>>),                            \
      (eve::wide<std::uint16_t, eve::fixed<8>>),                            \
      (eve::wide<std::uint16_t, eve::fixed<16>>),                           \
      (eve::wide<std::int32_t, eve::fixed<4>>),                             \
      (eve::wide<std::int32_t, eve::fixed<8>>),                             \
      (eve::wide<std::uint32_t, eve::fixed<4>>),                            \
      (eve::wide<std::uint32_t, eve::fixed<8>>),                            \
      (eve::wide<std::int64_t, eve::fixed<2>>),                             \
      (eve::wide<std::int64_t, eve::fixed<4>>),                             \
      (eve::wide<std::uint64_t, eve::fixed<2>>),                            \
      (eve::wide<std::uint64_t, eve::fixed<4>>),                            \
      (eve::wide<float, eve::fixed<4>>), (eve::wide<float, eve::fixed<8>>), \
      (eve::wide<double, eve::fixed<2>>), (eve::wide<double, eve::fixed<4>>)

TEMPLATE_TEST_CASE("eve_extra.load_unsafe", "[eve_extra]", ALL_TEST_PACKS) {
  using wide = TestType;
  using scalar = typename wide::value_type;
  constexpr std::ptrdiff_t size = wide::static_size;

  scalar s{123};

  wide actual{};

  auto* page_end = eve_extra::end_of_page(&s);

  if (page_end - &s < size) {
    actual = eve_extra::load_unsafe(page_end - size, eve::as_<wide>{});
  } else {
    actual = eve_extra::load_unsafe(&s, eve::as_<wide>{});
  }

  wide expected{s};
  REQUIRE(eve::any(expected == actual));

  actual = eve_extra::load_unsafe(
      eve_extra::previous_aligned_address(eve::as_<wide>{}, &s),
      eve::as_<wide>{});
  REQUIRE(eve::any(expected == actual));
}

}  // namespace
