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

#include <utility>

#include "unsq_eve/iteration_traits.h"
#include "unsq_eve/transform_reduce.h"

#include <eve/function/convert.hpp>

#include "test/catch.h"

namespace {

TEMPLATE_TEST_CASE("unsq_eve.transform_reduce.type_increase", "[unsq_eve]",
                   (std::pair<char, char>), (std::pair<char, short>),
                   (std::pair<char, int>)/*, (std::pair<int, char>),
                   (std::pair<int, short>), (std::pair<int, int>)*/) {
  using ArrayType = typename TestType::first_type;
  using IterateAs = typename TestType::second_type;
  using traits = unsq_eve::algorithm_traits<IterateAs, 256, 4>;
  using wide = eve::wide<IterateAs, eve::fixed<32 / sizeof(IterateAs)>>;

  auto map = [](wide x) -> wide { return x + x; };
  auto reduce = [](wide x, wide y) -> wide { return x + y; };

  std::vector<ArrayType> data{1, 2, 3};
  auto res = unsq_eve::transform_reduce<traits>(data.begin(), data.end(),
                                                IterateAs(0), reduce, map);
  STATIC_REQUIRE(std::is_same_v<decltype(res), IterateAs>);
  REQUIRE(1 * 2 + 2 * 2 + 3 * 2 == res);
}

}  // namespace
