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

#include "unsq_eve/iteration_traits.h"

namespace unsq_eve {

namespace _unroll {

template <std::size_t, std::ptrdiff_t width>
struct duffs_device;

template <std::ptrdiff_t width>
struct duffs_device<1u, width> {
  template <typename Ptr, typename Op>
  void operator()(Ptr f, Ptr l, Op op) const {
    while (f != l) {
      if (op(f, indx_c<0>{})) return;
      f += width;
    }
  }
};

template <std::ptrdiff_t width>
struct duffs_device<2u, width> {
  template <typename Ptr, typename Op>
  void operator()(Ptr f, Ptr l, Op op) const {
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
  template <typename Ptr, typename Op>
  void operator()(Ptr f, Ptr l, Op op) const {
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
  template <typename Ptr, typename Op>
  void operator()(Ptr f, Ptr l, Op op) const {
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

template <std::ptrdiff_t width, typename Ptr, typename Op,
          std::size_t... unroll_idxs>
std::pair<Ptr, bool> do_unroll(Ptr f, Op op,
                               std::index_sequence<unroll_idxs...>) {
  const bool test = ([&] () mutable {
    if (op(f, indx_c<unroll_idxs>{})) return true;
    f += width;
    return false;
  }() || ...);
  return {f, test};
}

}  // namespace _unroll

template <typename Traits, typename Ptr, typename Op>
void duffs_device_iteration(Ptr f, Ptr l, Op op) {
  // assert(l - f) % width == 0
  _unroll::duffs_device<Traits::unroll(), Traits::width()> device;
  device(f, l, op);
}

template <typename Traits, typename Ptr, typename Op>
std::pair<Ptr, bool> unroll(Ptr f, Op op) {
  return _unroll::do_unroll<Traits::width()>(
      f, op, std::make_index_sequence<Traits::unroll()>{});
}

template <typename Traits, typename Ptr, typename Op>
void unroll_iteration(Ptr f, Op op) {
  while (true) {
    auto [f_, test] = unroll<Traits>(f, op);
    f = f_;
    if (test) return;
  }
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_ITERATION_MAIN_LOOP_UNROLLED_H_