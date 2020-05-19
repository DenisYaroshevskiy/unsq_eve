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
/*
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
*/

TEMPLATE_TEST_CASE("eve_extra.first_true", "[eve_extra]", ALL_TEST_PACKS) {
  using wide = TestType;
  using scalar = typename wide::value_type;
  constexpr std::ptrdiff_t size = wide::static_size;

  wide x{scalar(1)}, y{scalar(2)};

  REQUIRE(std::nullopt == eve_extra::first_true(x == y, eve_extra::ignore_nothing{}));

  for (std::size_t i = 0; i != size; ++i) {
    x[i] = scalar(2);
    auto found = eve_extra::first_true(x == y, eve_extra::ignore_nothing{});
    REQUIRE(found);
    REQUIRE(i == found);
    x[i] = scalar(1);
  }

  for (std::size_t i = 0; i != size; ++i) {
    auto found = eve_extra::first_true(x == y, eve_extra::ignore_first_n{i});
    REQUIRE(!found);

    x[i] = scalar(2);

    found = eve_extra::first_true(x == y, eve_extra::ignore_first_n{i});
    REQUIRE(found);
    REQUIRE(i == *found);

    found = eve_extra::first_true(x == y, eve_extra::ignore_first_n{i + 1});
    REQUIRE(!found);
  }
}

TEST_CASE("eve_extra.load_const_aligned_ptr", "[eve_extra]") {
  using wide = eve::wide<char, eve::fixed<16>>;
  alignas(wide) std::array<char, 16> data;
  data.fill(1);

  eve::aligned_ptr<char, 16> ptr{data.begin()};
  wide loaded = eve::load(ptr, eve::as_<wide>{});

  REQUIRE(eve::all(loaded == wide{1}));
}

}  // namespace