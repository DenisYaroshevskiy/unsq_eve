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

#ifndef TEST_EVE_EXTRA_COMMON_H_
#define TEST_EVE_EXTRA_COMMON_H_

#define ALL_TEST_PACKS                                                      \
  (eve::wide<std::int8_t, eve::fixed<16>>),                                 \
      (eve::wide<std::int8_t, eve::fixed<32>>),                             \
      (eve::wide<std::uint8_t, eve::fixed<16>>),                            \
      (eve::wide<std::uint8_t, eve::fixed<32>>),                            \
      (eve::wide<std::int16_t, eve::fixed<8>>),                             \
      (eve::wide<std::int16_t, eve::fixed<16>>),                            \
      (eve::wide<std::uint16_t, eve::fixed<8>>),                            \
      (eve::wide<std::uint16_t, eve::fixed<16>>),                           \
      (eve::wide<std::int32_t, eve::fixed<4>>),                             \
      (eve::wide<std::int32_t, eve::fixed<8>>),                             \
      (eve::wide<std::uint32_t, eve::fixed<4>>),                            \
      (eve::wide<std::uint32_t, eve::fixed<8>>),                            \
      (eve::wide<std::int64_t, eve::fixed<2>>),                             \
      (eve::wide<std::int64_t, eve::fixed<4>>),                             \
      (eve::wide<std::uint64_t, eve::fixed<2>>),                            \
      (eve::wide<std::uint64_t, eve::fixed<4>>),                            \
      (eve::wide<float, eve::fixed<4>>), (eve::wide<float, eve::fixed<8>>), \
      (eve::wide<double, eve::fixed<2>>), (eve::wide<double, eve::fixed<4>>)

#endif  // TEST_EVE_EXTRA_COMMON_H_
