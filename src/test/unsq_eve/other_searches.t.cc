/*
 * Copyright 2024 Denis Yaroshevskiy
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

#include "unsq_eve/other_searches.h"

#include <string_view>

#include <tts/tts.hpp>

namespace {

void string_search_test(auto algo) {
  auto verify = [algo](std::string_view haystack, std::string_view needle) {
    auto expected = haystack.find(needle);
    auto actual = algo(haystack, needle);
    TTS_EQUAL(expected, actual,) << haystack << " " << needle;
  };

  verify("", "");
  verify("", "a");
  verify("a", "a");
  verify("aaaaa", "a");
  verify("bbbbbbbb", "abab");
  verify("bbbababbbb", "abab");
  verify("bbbababbbb", "");
  verify("bbbababbbb", "bbbababbbb");
  verify("bbbbaaa", "aaa");
}

void search_test(auto algo) {
  string_search_test([&](std::string_view haystack, std::string_view needle) {
    auto found = algo(haystack.begin(), haystack.end(), needle.begin(), needle.end());

    if (found == haystack.end()) {
      if (needle.empty()) return std::string_view::size_type{0};
      else return std::string_view::npos;
    }
    return static_cast<std::string_view::size_type>(found - haystack.begin());
  });
}

TTS_CASE("unsq_eve.other_searches.search_find_equal") {
  search_test([](auto f1, auto l1, auto f2, auto l2) {
    return unsq_eve::search_find_equal(f1, l1, f2, l2);
  });
};

TTS_CASE("unsq_eve.other_searches.search_two_loops") {
  search_test([](auto f1, auto l1, auto f2, auto l2) {
    return unsq_eve::search_two_loops(f1, l1, f2, l2);
  });
};

}  // namespace
