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

#include "unsq_eve/unroll.h"

#include <vector>

#include <eve/eve.hpp>

#include "test/catch.h"

namespace {

#define ALL_UNROLLS \
  (unsq_eve::indx_c<1>), (unsq_eve::indx_c<2>), (unsq_eve::indx_c<4>)

TEMPLATE_TEST_CASE("iteration_main_loop_unrolled", "[unsq_eve]", ALL_UNROLLS) {
  using traits = unsq_eve::iteration_traits<8, TestType{}()>;

  std::vector<int> v(1024, 15);
  constexpr std::ptrdiff_t stop_at = 248;

  int* last_ptr = nullptr;

  auto op = [&](int* ptr, auto register_idx) mutable {
    if (ptr - v.data() == stop_at) return true;

    *ptr = static_cast<int>(register_idx());
    REQUIRE(ptr > last_ptr);
    last_ptr = ptr;
    return false;
  };

  SECTION("guarded") {
    unsq_eve::duffs_device_iteration<traits>(v.data(), v.data() + v.size(), op);
    for (int i = 0, j = 0; i < 1024; i += 8) {
      if (i >= stop_at) {
        REQUIRE(v[i] == 15);
        continue;
      }

      // guarded doesn't guarantee register order
      REQUIRE(v[i] != 15);
      REQUIRE(v[i + 1] == 15);
      if (++j == traits::unroll) j = 0;
    }
  }

  SECTION("unguarded") {
    unsq_eve::unroll_iteration<traits>(v.data(), op);
    for (int i = 0, j = 0; i < 1024; i += 8) {
      if (i >= stop_at) {
        REQUIRE(v[i] == 15);
        continue;
      }

      // unguarded does guarantee register order
      REQUIRE(v[i] == j);
      REQUIRE(v[i + 1] == 15);
      if (++j == traits::unroll) j = 0;
    }
  }
}

}  // namespace
