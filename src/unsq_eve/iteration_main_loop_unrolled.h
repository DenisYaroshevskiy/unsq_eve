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

#ifndef UNSQ_EVE_ITERATION_MAIN_LOOP_UNROLLED_H_
#define UNSQ_EVE_ITERATION_MAIN_LOOP_UNROLLED_H_

#include <cstddef>
#include <cstdint>
#include <utility>

namespace unsq_eve {

template <std::size_t i>
using indx_c = std::integral_constant<std::size_t, i>;

namespace _iteration_main_loop_unrolled {

template <std::size_t, std::ptrdiff_t width>
struct duffs_device;

template <std::ptrdiff_t width>
struct duffs_device<1u, width> {
  template <typename T, typename Op>
  void operator()(T* f, T* l, Op op) const {
    while (f != l) {
      if (op(f, indx_c<0>{})) return;
      f += width;
    }
  }
};

template <std::ptrdiff_t width>
struct duffs_device<2u, width> {
  template <typename T, typename Op>
  void operator()(T* f, T* l, Op op) const {
    while (true) {
      switch (l - f) {
        case 0: return;
        default:
          if (op(f, indx_c<0>{})) return;
          f += width;
          [[fallthrough]];
        case width:
          if (op(f, indx_c<1>{})) return;
          f += width;
          [[fallthrough]];
      }
    }
  }
};

template <std::ptrdiff_t width>
struct duffs_device<3u, width> {
  template <typename T, typename Op>
  void operator()(T* f, T* l, Op op) const {
    while (true) {
      switch (l - f) {
        case 0: return;
        default:
          if (op(f, indx_c<0>{})) return;
          f += width;
          [[fallthrough]];
        case 2 * width:
          if (op(f, indx_c<1>{})) return;
          f += width;
          [[fallthrough]];
        case width:
          if (op(f, indx_c<2>{})) return;
          f += width;
          [[fallthrough]];
      }
    }
  }
};

template <std::ptrdiff_t width>
struct duffs_device<4u, width> {
  template <typename T, typename Op>
  void operator()(T* f, T* l, Op op) const {
    while (true) {
      switch (l - f) {
        case 0: return;
        default:
          if (op(f, indx_c<0>{})) return;
          f += width;
          [[fallthrough]];
        case 3 * width:
          if (op(f, indx_c<1>{})) return;
          f += width;
          [[fallthrough]];
        case 2 * width:
          if (op(f, indx_c<2>{})) return;
          f += width;
          [[fallthrough]];
        case width:
          if (op(f, indx_c<3>{})) return;
          f += width;
          [[fallthrough]];
      }
    }
  }
};

template <std::ptrdiff_t width, typename T, typename Op,
          std::size_t... unroll_idxs>
void unroll_unguarded(T* f, Op op, std::index_sequence<unroll_idxs...>) {
  while (true) {
    const bool test = ([&] {
      if (op(f, indx_c<unroll_idxs>{})) return true;
      f += width;
      return false;
    }() || ...);
    if (test) return;
  }
}

}  // namespace _iteration_main_loop_unrolled

template <std::size_t unroll_size, std::ptrdiff_t width, typename T,
          typename Op>
void iteration_main_loop_unrolled(T* f, T* l, Op op) {
  // assert(l - f) % width == 0
  _iteration_main_loop_unrolled::duffs_device<unroll_size, width> device;
  device(f, l, op);
}

template <std::size_t unroll_size, std::ptrdiff_t width, typename T,
          typename Op>
void iteration_main_loop_unrolled_unguarded(T* f, Op op) {
  _iteration_main_loop_unrolled::unroll_unguarded<width>(
      f, op, std::make_index_sequence<unroll_size>{});
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ITERATION_MAIN_LOOP_UNROLLED_H_
