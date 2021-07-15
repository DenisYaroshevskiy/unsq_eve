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

#include "unsq_eve/strlen_example.h"

#include <eve/memory/aligned_allocator.hpp>

#include "test/catch.h"

namespace unsq_eve {
namespace {

TEST_CASE("unsq_eve.strlen_example", "[unsq_eve]") {
  std::vector<char, eve::aligned_allocator<char, eve::fixed<4096>>> page(4096, 'a');

  // 50 from the beginning
  auto* f = page.data();
  auto* l = f + 50;

  auto run = [&]() {
    *l = 0;
    for (auto* it = f; it < l; ++it) {
      std::size_t expected = static_cast<std::size_t>(l - it);
      REQUIRE(expected == unsq_eve::strlen_example(it));
    }
    *l = 'a';
  };

  while (f < l) {
    run();
    --l;
    *f = 1;
    ++f;
  }

  // 50 from the end
  f = page.data() + page.size() - 50;
  l = page.data() + page.size() - 1;

  while (f < l) {
    run();
    --l;
    ++f;
  }
}

}  // namespace
}  // namespace unsq_eve
