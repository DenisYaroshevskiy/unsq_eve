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

TEST_CASE("previous_aligned_address", "[eve_extra]") {
  using wide = eve::wide<char, eve::fixed<16>>;
  const char str[] = "abc";
  eve::aligned_ptr test =
      eve_extra::previous_aligned_address(eve::as_<wide>{}, str);
  REQUIRE(test.get());
};

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

TEMPLATE_TEST_CASE("eve_extra.first_true", "[eve_extra]", ALL_TEST_PACKS) {
  using wide = TestType;
  using scalar = typename wide::value_type;
  constexpr std::ptrdiff_t size = wide::static_size;

  wide x{scalar(1)}, y{scalar(2)};

  REQUIRE(std::nullopt ==
          eve_extra::first_true(x == y, eve_extra::ignore_nothing{}));

  SECTION("ignore nothing") {
    for (std::size_t i = size; i != 0; --i) {
      x[i - 1] = scalar(2);
      auto found = eve_extra::first_true(x == y, eve_extra::ignore_nothing{});
      REQUIRE(found);
      REQUIRE(i - 1 == *found);
    }
  }

  SECTION("ignore first n") {
    for (std::size_t i = 0; i != size; ++i) {
      auto found = eve_extra::first_true(x == y, eve_extra::ignore_first_n{i});
      REQUIRE(!found);

      found = eve_extra::first_true(x == y, eve_extra::ignore_first_last{i, 0});
      REQUIRE(!found);

      x[i] = scalar(2);

      found = eve_extra::first_true(x == y, eve_extra::ignore_first_n{i});
      REQUIRE(found);
      REQUIRE(i == *found);

      found = eve_extra::first_true(x == y, eve_extra::ignore_first_last{i, 0});
      REQUIRE(found);
      REQUIRE(i == *found);

      found = eve_extra::first_true(x == y, eve_extra::ignore_first_n{i + 1});
      REQUIRE(!found);

      found =
          eve_extra::first_true(x == y, eve_extra::ignore_first_last{i + 1, 0});
      REQUIRE(!found);
    }
  }

  SECTION("ignore last n") {
    for (std::size_t i = size; i != 0; --i) {
      auto found =
          eve_extra::first_true(x == y, eve_extra::ignore_last_n{size - i});
      REQUIRE(!found);

      found = eve_extra::first_true(x == y,
                                    eve_extra::ignore_first_last{0, size - i});
      REQUIRE(!found);

      x[i - 1] = scalar(2);

      found = eve_extra::first_true(x == y, eve_extra::ignore_last_n{size - i});
      REQUIRE(found);
      REQUIRE(i - 1 == *found);

      found = eve_extra::first_true(x == y,
                                    eve_extra::ignore_first_last{0, size - i});
      REQUIRE(found);
      REQUIRE(i - 1 == *found);

      found =
          eve_extra::first_true(x == y, eve_extra::ignore_last_n{size - i + 1});
      REQUIRE(!found);

      found = eve_extra::first_true(
          x == y, eve_extra::ignore_first_last{0, size - i + 1});
      REQUIRE(!found);
    }
  }

  SECTION("ignore_first_last") {
    x[0] = scalar(2);
    x[1] = scalar(2);
    x[size - 1] = scalar(2);

    eve_extra::ignore_first_n first{2};
    eve_extra::ignore_last_n last{1};

    auto found = eve_extra::first_true(x == y, eve_extra::combine(first, last));

    REQUIRE(!found);
    found = eve_extra::first_true(x == y, eve_extra::combine(last, first));
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

TEMPLATE_TEST_CASE("eve_extra.any", "[eve_extra]", ALL_TEST_PACKS) {
  using wide = TestType;

  wide x{0}, y{1};

  REQUIRE(!eve_extra::any(x == y, eve_extra::ignore_nothing{}));
  x[0] = 1;
  REQUIRE(eve_extra::any(x == y, eve_extra::ignore_nothing{}));
  REQUIRE(!eve_extra::any(x == y, eve_extra::ignore_first_n{1}));

  SECTION("extra_wide") {
    using T = typename wide::value_type;
    constexpr std::ptrdiff_t size = wide::static_size;

    auto run = [](auto reg) {
      using extra_wide = decltype(reg);

      extra_wide x{0};
      extra_wide y{1};

      REQUIRE(!eve_extra::any(x == y, eve_extra::ignore_nothing{}));

      for (auto& elem : x) {
        elem = 1;
        REQUIRE(eve_extra::any(x == y, eve_extra::ignore_nothing{}));
        elem = 0;
      }
    };

    run(eve::wide<T, eve::fixed<size>>{});
  }
}

TEMPLATE_TEST_CASE("eve_extra.first_true_array", "[eve_extra]",
                   ALL_TEST_PACKS) {
  using wide = TestType;
  using logical = eve::logical<wide>;

  auto run = [&](auto test) {
    wide x{0}, y{1};

    test.fill(x == y);

    using namespace eve_extra;
    REQUIRE(!first_true_array(test));

    x[1] = 1;

    for (std::size_t i = 0; i != test.size(); ++i) {
      test[i] = (x == y);
      std::uint32_t expected = (wide::static_size * i) + 1;
      REQUIRE(first_true_array(test));
      REQUIRE(*first_true_array(test) == expected);
      test[i] = (x != x);
    }
  };

  run(std::array<logical, 1>{});
  run(std::array<logical, 2>{});
  run(std::array<logical, 4>{});
}

}  // namespace
