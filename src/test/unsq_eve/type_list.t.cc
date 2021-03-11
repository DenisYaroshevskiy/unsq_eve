/*
 * Copyright 2021 Denis Yaroshevskiy
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

#include "unsq_eve/type_list.h"

#include "test/catch.h"

template <typename T>
void is_same_test(T, T) {}

namespace unsq_eve {

TEST_CASE("type_list, concat", "[meta]")
{
  is_same_test(concatenate(), type_list<>{});
  is_same_test(concatenate(type_list<int>{}, type_list<char, double>{}), type_list<int, char, double>{});
  is_same_test(concatenate(type_list<int>{}, type_list<char, double>{}, type_list<float, short>{}),
                           type_list<int, char, double, float, short>{});
}

TEST_CASE("type_list, flatten", "[meta]")
{
  is_same_test(flatten(type_list<>{}), type_list<>{});
  is_same_test(flatten(type_list<int, char>{}), type_list<int, char>{});
  is_same_test(flatten(type_list<type_list<int, char>>{}), type_list<int, char>{});
  is_same_test(flatten(type_list<float, type_list<int>, type_list<char, float, double>>{}),
                       type_list<float, int, char, float, double>{});
}

}  // namespace unsq_eve
