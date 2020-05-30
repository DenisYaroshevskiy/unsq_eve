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

#include "unsq_eve/iteration_traits.h"
#include "unsq_eve/transform_reduce.h"

#include <eve/function/convert.hpp>

#include "test/catch.h"

namespace {

TEST_CASE("unsq_eve.transform_reduce.type_increase", "[unsq_eve]") {
  using traits = unsq_eve::iteration_traits<32, 4>;
  using wide = eve::wide<char, eve::fixed<32>>;
  using wider = eve::wide<short, eve::fixed<32>>;
  using widest = eve::wide<int, eve::fixed<32>>;

  auto map = [](wide x) -> wider {
    auto wider_x = eve::convert(x, eve::as_<short>{});
    wider_x += wider_x;
    return wider_x;
  };
  auto reduce = [](widest x, widest y) -> widest { return x + y; };
  std::vector<char> data{1, 2, 3};
  unsq_eve::transform_reduce<traits>(data.begin(), data.end(), int(0), map,
                                     reduce);
}

}  // namespace
