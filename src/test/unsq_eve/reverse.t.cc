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

#include "unsq_eve/reverse.h"

#include <ostream>

#include <eve/memory/aligned_allocator.hpp>

#include "test/catch.h"

namespace {

TEST_CASE("unsq_eve.reverse", "[unsq_eve]") {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  unsq_eve::reverse<unsq_eve::algorithm_traits<int, 256, 1>>(v.begin(),
                                                             v.end());
  REQUIRE(v == std::vector<int>{11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1});
}

}  // namespace
