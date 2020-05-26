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

#ifndef EVE_EXTRA_REPLACE_IGNORED_H_
#define EVE_EXTRA_REPLACE_IGNORED_H_

#include "eve_extra/constants.h"
#include "eve_extra/mmask_operations.h"

#include <eve/function/if_else.hpp>
#include <eve/function/logical_or.hpp>

namespace eve_extra {
namespace _replace_ignored {

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

}  // namespace _replace_ignored

template <typename Wide>
using signed_integer_wide =
    decltype(_replace_ignored::do_signed_integer_wide<Wide>());

namespace _replace_ignored {

template <typename Wide>
Wide ignore_first_broadcast(ignore_first_n ignore) {
  using T = typename Wide::value_type;
  return Wide{static_cast<T>(ignore.n)};
}

template <typename Wide>
Wide ignore_last_broadcast(ignore_last_n ignore) {
  using T = typename Wide::value_type;

  T last_idx = static_cast<T>(Wide::static_size - 1);
  T offset = static_cast<T>(ignore.n);

  return Wide{last_idx - offset};
}

}  // namespace _replace_ignored

template <typename Wide>
Wide replace_ignored(Wide x, ignore_nothing, Wide) {
  return x;
}

template <typename Wide>
Wide replace_ignored(Wide x, ignore_first_n ignore, Wide with) {
  using si_wide = signed_integer_wide<Wide>;

  si_wide idxs = eve_extra::iota(eve::as_<si_wide>{});
  si_wide vignore = _replace_ignored::ignore_first_broadcast<si_wide>(ignore);

  return eve::if_else(idxs < vignore, with, x);
}

template <typename Wide>
Wide replace_ignored(Wide x, ignore_last_n ignore, Wide with) {
  using si_wide = signed_integer_wide<Wide>;

  si_wide idxs = eve_extra::iota(eve::as_<si_wide>{});
  si_wide vignore = _replace_ignored::ignore_last_broadcast<si_wide>(ignore);
  return eve::if_else(vignore < idxs, with, x);
}

template <typename Wide>
Wide replace_ignored(Wide x, ignore_first_last ignore, Wide with) {
  using si_wide = signed_integer_wide<Wide>;

  si_wide idxs = eve_extra::iota(eve::as_<si_wide>{});

  si_wide first =
      _replace_ignored::ignore_first_broadcast<si_wide>({ignore.first_n});
  si_wide last =
      _replace_ignored::ignore_last_broadcast<si_wide>({ignore.last_n});

  eve::logical<si_wide> first_mask = idxs < first;
  eve::logical<si_wide> last_mask = last < idxs;
  eve::logical<si_wide> mask = eve::logical_or(first_mask, last_mask);

  return eve::if_else(mask, with, x);
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_REPLACE_IGNORED_H_
