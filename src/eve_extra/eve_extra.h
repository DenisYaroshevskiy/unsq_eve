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

#ifndef EVE_EXTRA_EVE_EXTA_H_
#define EVE_EXTRA_EVE_EXTA_H_

#include <type_traits>

#include <eve/eve.hpp>
#include <eve/function/load.hpp>
#include <eve/memory/align.hpp>

#include "eve_extra/concepts.h"

namespace eve_extra {

/*
Compiler does not generate this properly, instead of doing things one
after another if you ask it.
*/

template <typename T, typename Op>
T segment_reduction(const std::array<T, 1>& arr, Op) {
  return arr[0];
}

template <typename T, typename Op>
T segment_reduction(const std::array<T, 2>& arr, Op op) {
  return op(arr[0], arr[1]);
}

template <typename T, typename Op>
T segment_reduction(const std::array<T, 4>& arr, Op op) {
  T x = op(arr[0], arr[2]);
  T y = op(arr[1], arr[3]);
  return op(x, y);
}

template <typename T, typename Op>
T segment_reduction(const std::array<T, 8>& arr, Op op) {
  T x1 = op(arr[0], arr[4]);
  T x2 = op(arr[1], arr[5]);
  T x3 = op(arr[2], arr[6]);
  T x4 = op(arr[3], arr[7]);
  x1 = op(x1, x2);
  x3 = op(x3, x4);
  return op(x1, x3);
}

namespace _eve_extra {

template <std::size_t, typename>
struct n_wide;

template <std::size_t n, typename T, typename N>
struct n_wide<n, eve::wide<T, N>> {
  using type = eve::wide<T, eve::fixed<N() * n>>;
};

template <std::size_t n, eve_wide Wide>
struct n_wide<n, eve::logical<Wide>> {
  using type = eve::logical<typename n_wide<n, Wide>::type>;
};

template <std::size_t n, typename T>
using n_wide_t = typename n_wide<n, T>::type;

template <std::size_t f, std::size_t n, typename Wide, std::size_t N>
auto aggregate_impl(const std::array<Wide, N>& xs) {
  if constexpr (n == 1)
    return xs[f];
  else {
    return n_wide_t<n, Wide>{aggregate_impl<f, n / 2>(xs),
                           aggregate_impl<f + n / 2, n / 2>(xs)};
  }
}

}  // namespace _eve_extra

template <typename Wide, std::size_t N>
auto aggregate(const std::array<Wide, N>& xs) {
  return _eve_extra::aggregate_impl<0, N>(xs);
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_EVE_EXTA_H_
