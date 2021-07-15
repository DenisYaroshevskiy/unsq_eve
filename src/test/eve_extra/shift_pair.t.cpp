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

namespace {

template <std::size_t idx>
using indx_c = std::integral_constant<std::size_t, idx>;

template <std::size_t n, typename Op>
void unroll(Op op) {
  [&]<std::size_t... idxs>(std::index_sequence<idxs...>) mutable {
    (op(indx_c<idxs>{}), ...);
  }
  (std::make_index_sequence<n>{});
}

template <typename TestType, typename Op>
void shift_pair_right_test(Op op) {
  using wide = TestType;

  const wide lhs = eve_extra::iota(eve::as<wide>{});
  const wide rhs = eve_extra::iota(eve::as<wide>{}) + wide{20};

  auto run = [&]<std::size_t shift>(indx_c<shift> wrapped_shift) {
    const wide actual = op(wrapped_shift, lhs, rhs);

    wide expected;
    std::copy(lhs.end() - shift, lhs.end(), expected.begin());
    std::copy(rhs.begin(), rhs.end() - shift, expected.begin() + shift);

    INFO("lhs: " << lhs << " rhs: " << rhs);
    INFO("shift " << shift);
    INFO("expected: " << expected << " actual: " << actual);
    REQUIRE(eve::all(expected == actual));
  };

  unroll<wide::size()>(run);
}

TEMPLATE_TEST_CASE("eve_extra.shift_pair_right", "[eve_extra]",
                   ALL_TEST_PACKS) {
  shift_pair_right_test<TestType>(
      []<std::size_t shift>(indx_c<shift>, auto lhs, auto rhs) {
        return eve_extra::shift_pair_right<shift>(lhs, rhs);
      });
}

TEST_CASE("trying shifts (left for reference)", "[eve_extra]") {
  using wide = eve::wide<std::int64_t, eve::fixed<4>>;

  wide x_wide = eve_extra::iota(eve::as<wide>{}) + wide{10};
  wide filler_wide = eve_extra::iota(eve::as<wide>{});

  INFO("x: " << x_wide << " filler: " << filler_wide);

  __m256i x = x_wide.storage();
  __m256i filler = filler_wide.storage();

  // 1
  {
    wide expected{filler[3], x[0], x[1], x[2]};

    __m256i filler1_x0 = _mm256_permute2x128_si256(x, filler, 0x03);
    INFO("filler1_x0: " << wide(filler1_x0));

    wide actual = _mm256_alignr_epi8(x, filler1_x0, 8);
    INFO("expected: " << expected << " actual: " << actual);
    REQUIRE(eve::all(expected == actual));
  }

  // 2
  {
    wide expected{filler[2], filler[3], x[0], x[1]};

    wide actual = _mm256_permute2x128_si256(x, filler, 0x03);

    INFO("expected: " << expected << " actual: " << actual);
    REQUIRE(eve::all(expected == actual));
  }

  // 3
  {
    wide expected{filler[1], filler[2], filler[3], x[0]};

    __m256i filler1_x0 = _mm256_permute2x128_si256(x, filler, 0x03);
    INFO("filler1_x0: " << wide(filler1_x0));

    wide actual = _mm256_alignr_epi8(filler1_x0, filler, 8);
    INFO("expected: " << expected << " actual: " << actual);
    REQUIRE(eve::all(expected == actual));
  }
}

TEST_CASE("eve_extra.shift_pair_right_in_groups", "[eve_extra]") {
  using wide = eve::wide<std::int64_t, eve::fixed<4>>;
  using TestType = wide;

  if constexpr (eve_extra::wide_16_bytes<wide>) {
    shift_pair_right_test<TestType>(
        []<std::size_t shift>(indx_c<shift>, auto lhs, auto rhs) {
          return eve_extra::shift_pair_right_in_groups<shift>(lhs, rhs);
        });
    return;
  }

  const wide lhs = eve_extra::iota(eve::as<wide>{});
  const wide rhs = eve_extra::iota(eve::as<wide>{}) + wide{20};
  static constexpr std::ptrdiff_t half_size = wide::size() / 2;

  auto run = [&]<std::size_t shift>(indx_c<shift>) {
    const wide actual = eve_extra::shift_pair_right_in_groups<shift>(lhs, rhs);

    wide expected;

    auto lhs_m = lhs.begin() + half_size;
    auto rhs_m = rhs.begin() + half_size;
    auto expected_m = expected.begin() + half_size;

    std::copy(lhs_m - shift, lhs_m, expected.begin());
    std::copy(rhs.begin(), rhs_m - shift, expected.begin() + shift);
    std::copy(lhs.end() - shift, lhs.end(), expected_m);
    std::copy(rhs_m, rhs.end() - shift, expected_m + shift);

    INFO("lhs: " << lhs << " rhs: " << rhs);
    INFO("shift " << shift);
    INFO("expected: " << expected << " actual: " << actual);
    REQUIRE(eve::all(expected == actual));
  };

  unroll<half_size>(run);
}

}  // namespace
