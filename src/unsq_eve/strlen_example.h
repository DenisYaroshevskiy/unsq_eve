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

#ifndef UNSQ_EVE_STRLEN_EXAMPLE_H_
#define UNSQ_EVE_STRLEN_EXAMPLE_H_

#include <cstdint>

#include <eve/eve.hpp>
#include <eve/conditional.hpp>
#include <eve/function/first_true.hpp>
#include <eve/function/load.hpp>

namespace unsq_eve {

// Simplified implementation of stlren - see find_unguarded for a proper one.
inline std::size_t strlen_example(const char* s_) {
  auto* s = reinterpret_cast<const std::uint8_t*>(s_);
  using wide = eve::wide<unsigned char>;
  using N = typename wide::cardinal_type;

  const wide zeroes{0};

  eve::aligned_ptr aligned_s = eve::previous_aligned_address(s);

  wide cur = eve::unsafe(eve::load)(aligned_s, N{});
  eve::ignore_first ignore(s - aligned_s.get());

  std::optional match = eve::first_true[ignore](cur == zeroes);

  while (!match) {
    aligned_s += wide::size();
    cur = eve::unsafe(eve::load)(aligned_s, N{});
    match = eve::first_true(cur == zeroes);
  }

  return static_cast<std::size_t>(aligned_s.get() + *match - s);
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_STRLEN_EXAMPLE_H_
