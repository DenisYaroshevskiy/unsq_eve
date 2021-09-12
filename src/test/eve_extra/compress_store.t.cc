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

#include <algorithm>

#include <eve/function/all.hpp>

#include "test/catch.h"
#include "test/eve_extra/common.h"

namespace eve_extra {
namespace {

TEMPLATE_TEST_CASE("eve_extra.compress_store_main_logic", "[eve_extra]",
                   ALL_TEST_PACKS) {
  using wide = TestType;
  using logical = eve::logical<wide>;
  using scalar = typename wide::value_type;
  using arr_t = std::array<scalar, wide::size()>;

  const wide x = eve_extra::iota(eve::as<wide>{}) + wide{5};

  logical mask{false};

  auto run = [&] {
    arr_t expected;
    expected.fill(0);

    std::uint8_t o = 0;
    for (std::uint8_t i = 0; i != wide::size(); ++i) {
      if (!mask.get(i)) continue;
      expected[o++] = x.get(i);
    }

    arr_t actual;
    scalar* out =
        compress_store_unsafe(x, actual.begin(), mask, eve::ignore_none);

    REQUIRE(out - actual.begin() == static_cast<std::ptrdiff_t>(o));

    // No guarnaties past actual
    std::copy(out, actual.end(), expected.begin() + o);
    //INFO("expected: " << expected << " actual: " << actual);
    bool test = expected == actual;
    REQUIRE(test);

    // For precise we guarantee an exact match
    std::vector<scalar> precise_expected(expected.begin(),
                                         expected.begin() + o);
    std::vector<scalar> precise_actual(o, scalar(0));
    out = compress_store_precise(x, precise_actual.data(), mask,
                                 eve::ignore_none);

    REQUIRE(precise_actual.data() + o == out);
    REQUIRE(precise_expected == precise_actual);
  };

  SECTION("Up to first 4 even elements") {
    std::ptrdiff_t even_end = std::min(wide::size(), 8l);

    for (std::ptrdiff_t i = 0; i != even_end; i += 2) {
      mask.set(i, true);
    }

    run();
  }
}

TEMPLATE_TEST_CASE("eve_extra.compress_store_ignore", "[eve_extra]",
                   ALL_TEST_PACKS) {
  using wide = TestType;
  using logical = eve::logical<wide>;
  using scalar = typename wide::value_type;

  const wide x = eve_extra::iota(eve::as<wide>{}) + wide{5};

  auto run = [&](auto ignore) {
    logical mask{true};

    int f = 0;
    int l = wide::size();

    if constexpr (std::same_as<decltype(ignore), eve::ignore_first>) {
      f += static_cast<std::ptrdiff_t>(ignore.count_);
    } else if constexpr (std::same_as<decltype(ignore), eve::ignore_last>) {
      l -= static_cast<std::ptrdiff_t>(ignore.count_);
    } else if constexpr (std::same_as<decltype(ignore), eve::ignore_extrema>) {
      f += static_cast<std::ptrdiff_t>(ignore.first_count_);
      l -= static_cast<std::ptrdiff_t>(ignore.last_count_);
    }

    std::ptrdiff_t ignored_from_the_beginning = f;

    std::vector<scalar> expected(l - f, 0);
    for (int i = 0; i != (l - f); ++i) {
      expected[i] = x.get(i + f);
    }

    std::vector<scalar> actual(l, 0);

    INFO("ignore: " << ignore);

    // Compress store precize
    compress_store_precise(x, actual.data(), mask, ignore);
    actual.erase(actual.begin(), actual.begin() + ignored_from_the_beginning);

    REQUIRE(expected == actual);

    // Compress store unsafe
    actual = std::vector<scalar>(l, 0);
    compress_store_unsafe(x, actual.data(), mask, ignore);
    actual.erase(actual.begin(), actual.begin() + ignored_from_the_beginning);

    REQUIRE(expected == actual);
  };

  for (int i = 0; i != wide::size() + 1; ++i) {
    run(eve::ignore_first{i});
    run(eve::ignore_last{i});
    for (int j = 0; j != wide::size() - i; ++j) {
      run(eve::ignore_extrema{i, j});
    }
  }

  SECTION("eve_extra.compress_store_unsafe_ignore_is_precise") {
    logical mask{[](int i, int) { return i == 1; }};
    scalar out{0};

    const wide x = eve_extra::iota(eve::as<wide>{});

    compress_store_precise(x, &out, mask, eve::ignore_none);
    REQUIRE(out == 1);

    out = scalar{5};

    compress_store_unsafe(x, &out, mask, eve::ignore_last{0});
    REQUIRE(out == 1);
  }
}

}  // namespace
}  // namespace eve_extra
