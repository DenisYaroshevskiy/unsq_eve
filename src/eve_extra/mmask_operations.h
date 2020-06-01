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

#ifndef EVE_EXTRA_MMASK_OPERATIONS_H_
#define EVE_EXTRA_MMASK_OPERATIONS_H_

#include <eve/eve.hpp>
#include <eve/function/logical_and.hpp>

#include "eve_extra/concepts.h"
#include "eve_extra/constants.h"

#include <iostream>

namespace eve_extra {

struct ignore_nothing {
  friend std::ostream& operator<<(std::ostream& out, const ignore_nothing&) {
    out << "ignore_noting";
    return out;
  }
};

struct ignore_first_n {
  std::size_t n;

  friend std::ostream& operator<<(std::ostream& out,
                                  const ignore_first_n& ignore) {
    out << "ignore_first{" << ignore.n << "}";
    return out;
  }
};

struct ignore_last_n {
  std::size_t n;

  friend std::ostream& operator<<(std::ostream& out,
                                  const ignore_last_n& ignore) {
    out << "ignore_last{" << ignore.n << "}";
    return out;
  }
};

struct ignore_first_last {
  std::size_t first_n;
  std::size_t last_n;

  friend std::ostream& operator<<(std::ostream& out,
                                  const ignore_first_last& ignore) {
    out << "ignore_first_last{" << ignore.first_n << ',' << ignore.last_n
        << "}";
    return out;
  }
};

constexpr ignore_first_last combine(ignore_first_n x, ignore_last_n y) {
  return ignore_first_last{x.n, y.n};
}

constexpr ignore_first_last combine(ignore_last_n x, ignore_first_n y) {
  return combine(y, x);
}

template <native_logical Logical>
std::uint32_t clear_ingored(std::uint32_t mmask, ignore_nothing) {
  return mmask;
}

constexpr std::uint32_t set_lower_n_bits(std::uint32_t n) {
  std::uint64_t res{1};
  res <<= n;
  res -= 1;
  return static_cast<std::uint32_t>(res);
}

template <native_logical Logical>
std::uint32_t clear_ingored(std::uint32_t mmask, ignore_first_n ignore) {
  using scalar = typename Logical::value_type;

  std::uint32_t ignore_mask = ~set_lower_n_bits(ignore.n * sizeof(scalar));
  return ignore_mask & mmask;
}

template <native_logical Logical>
std::uint32_t clear_ingored(std::uint32_t mmask, ignore_last_n ignore) {
  using scalar = typename Logical::value_type;

  std::uint32_t ignore_mask = set_lower_n_bits(
      sizeof(typename Logical::storage_type) - ignore.n * sizeof(scalar));
  return ignore_mask & mmask;
}

template <native_logical Logical>
std::uint32_t clear_ingored(std::uint32_t mmask, ignore_first_last ignore) {
  mmask = clear_ingored<Logical>(mmask, ignore_first_n{ignore.first_n});
  return clear_ingored<Logical>(mmask, ignore_last_n{ignore.last_n});
};

template <typename Register>
std::uint32_t movemask(Register reg) {
  if constexpr (sizeof(reg) == 16) {
    return _mm_movemask_epi8(reg);
  } else {
    return _mm256_movemask_epi8(reg);
  }
}

namespace _mmask_operations {

template <typename Wide>
auto do_signed_integer_wide() {
  using T = typename Wide::value_type;
  using N = typename Wide::cardinal_type;
  using ABI = typename Wide::abi_type;

  if constexpr (sizeof(T) == 1) {
    return eve::wide<std::int8_t, N, ABI>{};
  } else if constexpr (sizeof(T) == 2) {
    return eve::wide<std::int16_t, N, ABI>{};
  } else if constexpr (sizeof(T) == 4) {
    return eve::wide<std::int32_t, N, ABI>{};
  } else if constexpr (sizeof(T) == 8) {
    return eve::wide<std::int64_t, N, ABI>{};
  }
}

template <typename Wide>
using signed_integer_wide =
    decltype(_mmask_operations::do_signed_integer_wide<Wide>());

template <typename Wide>
Wide ignore_first_broadcast(ignore_first_n ignore) {
  using T = typename Wide::value_type;
  return Wide{static_cast<T>(ignore.n) - 1};
}

template <typename Wide>
Wide ignore_last_broadcast(ignore_last_n ignore) {
  using T = typename Wide::value_type;

  T last_idx = static_cast<T>(Wide::static_size);
  T offset = static_cast<T>(ignore.n);

  return Wide{last_idx - offset};
}

}  // namespace _mmask_operations

template <eve_logical Logical>
Logical ignore_broadcast(ignore_nothing) {
  return Logical{true};
}

template <eve_logical Logical>
Logical ignore_broadcast(ignore_first_n ignore) {
  using wide = typename Logical::parent;
  using si_wide = _mmask_operations::signed_integer_wide<wide>;

  si_wide idxs = eve_extra::iota(eve::as_<si_wide>{});
  si_wide vignore = _mmask_operations::ignore_first_broadcast<si_wide>(ignore);

  return Logical{vignore < idxs};
}

template <eve_logical Logical>
Logical ignore_broadcast(ignore_last_n ignore) {
  using wide = typename Logical::parent;
  using si_wide = _mmask_operations::signed_integer_wide<wide>;

  si_wide idxs = eve_extra::iota(eve::as_<si_wide>{});
  si_wide vignore = _mmask_operations::ignore_last_broadcast<si_wide>(ignore);

  return Logical{idxs < vignore};
}

template <eve_logical Logical>
Logical ignore_broadcast(ignore_first_last ignore) {
  using namespace _mmask_operations;
  using wide = typename Logical::parent;
  using si_wide = signed_integer_wide<wide>;

  si_wide idxs = eve_extra::iota(eve::as_<si_wide>{});
  si_wide first =
      ignore_first_broadcast<si_wide>(ignore_first_n{ignore.first_n});
  si_wide last = ignore_last_broadcast<si_wide>(ignore_last_n{ignore.last_n});

  eve::logical<si_wide> first_mask = first < idxs;
  eve::logical<si_wide> last_mask = idxs < last;

  return Logical{eve::logical_and(first_mask, last_mask)};
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_MMASK_OPERATIONS_H_
