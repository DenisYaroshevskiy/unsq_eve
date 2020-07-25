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

#include "test/catch.h"
#include "test/eve_extra/common.h"

namespace eve_extra {
namespace {

TEMPLATE_TEST_CASE("eve_extra.compress_store_main_logic", "[eve_extra]",
                   ALL_TEST_PACKS) {
  using wide = TestType;
  using logical = eve::logical<wide>;
  using scalar = typename wide::value_type;

  const wide x = eve_extra::iota(eve::as_<wide>{}) + wide{5};

  logical mask{false};

  auto run = [&] {
    wide expected{0};

    std::uint8_t o = 0;
    for (std::uint8_t i = 0; i != wide::static_size; ++i) {
      if (!mask[i]) continue;
      expected[o++] = x[i];
    }

    wide actual;
    scalar* out =
        compress_store_unsafe(x, actual.begin(), mask, ignore_nothing{});

    REQUIRE(out - actual.begin() == static_cast<std::ptrdiff_t>(o));

    // No guarnaties past actual
    std::copy(out, actual.end(), &expected[o]);
    INFO("expected: " << expected << " actual: " << actual);
    REQUIRE(eve::all(expected == actual));

    // For precise we guarantee an exact match
    std::vector<scalar> precise_expected(expected.begin(),
                                         expected.begin() + o);
    std::vector<scalar> precise_actual(o, scalar(0));
    out = compress_store_precise(x, precise_actual.data(), mask,
                                 ignore_nothing{});

    REQUIRE(precise_actual.data() + o == out);
    REQUIRE(precise_expected == precise_actual);
  };

  SECTION("Up to first 4 even elements") {
    std::ptrdiff_t even_end = std::min(wide::static_size, 8l);

    for (std::ptrdiff_t i = 0; i != even_end; i += 2) {
      mask[i] = true;
    }

    run();
  }
}

TEMPLATE_TEST_CASE("eve_extra.compress_store_ignore", "[eve_extra]",
                   ALL_TEST_PACKS) {
  using wide = TestType;
  using logical = eve::logical<wide>;
  using scalar = typename wide::value_type;

  const wide x = eve_extra::iota(eve::as_<wide>{}) + wide{5};

  auto run = [&](auto ignore) {
    logical mask{true};

    const auto* f = x.begin();
    const auto* l = x.end();

    if constexpr (std::same_as<decltype(ignore), ignore_first_n>) {
      f += static_cast<std::ptrdiff_t>(ignore.n);
    } else if constexpr (std::same_as<decltype(ignore), ignore_last_n>) {
      l -= static_cast<std::ptrdiff_t>(ignore.n);
    } else if constexpr (std::same_as<decltype(ignore), ignore_first_last>) {
      f += static_cast<std::ptrdiff_t>(ignore.first_n);
      l -= static_cast<std::ptrdiff_t>(ignore.last_n);
    }

    std::ptrdiff_t ignored_from_the_beginning = f - x.begin();

    std::vector<scalar> expected(f, l);
    std::vector<scalar> actual(l - x.begin(), 0);

    INFO("ignore: " << ignore);

    // Compress store precize
    compress_store_precise(x, actual.data(), mask, ignore);
    actual.erase(actual.begin(), actual.begin() + ignored_from_the_beginning);

    REQUIRE(expected == actual);

    // Compress store unsafe
    actual = std::vector<scalar>(l - x.begin(), 0);
    compress_store_unsafe(x, actual.data(), mask, ignore);
    actual.erase(actual.begin(), actual.begin() + ignored_from_the_beginning);

    REQUIRE(expected == actual);
  };

  for (std::size_t i = 0; i != wide::static_size + 1; ++i) {
    run(ignore_first_n{i});
    run(ignore_last_n{i});
    for (std::size_t j = 0; j != wide::static_size - i; ++j) {
      run(ignore_first_last{i, j});
    }
  }

  SECTION("eve_extra.compress_store_unsafe_ignore_is_precise") {
    logical mask{[](int i, int) { return i == 1; }};
    scalar out{0};

    const wide x = eve_extra::iota(eve::as_<wide>{});

    compress_store_precise(x, &out, mask, ignore_nothing{});
    REQUIRE(out == 1);

    out = scalar{5};

    compress_store_unsafe(x, &out, mask, ignore_last_n{0});
    REQUIRE(out == 1);
  }
}

}  // namespace
}  // namespace eve_extra
