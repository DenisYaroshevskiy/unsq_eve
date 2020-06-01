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

#include "eve_extra/mmask_operations.h"

#include <eve/function/if_else.hpp>

namespace eve_extra {

template <eve_wide Wide>
Wide replace_ignored(Wide x, ignore_nothing, Wide) {
  return x;
}

template <eve_wide Wide, typename Ignore>
Wide replace_ignored(Wide x, Ignore ignore, Wide with) {
  return eve::if_else(ignore_broadcast<eve::logical<Wide>>(ignore), x, with);
}

}  // namespace eve_extra

#endif  // EVE_EXTRA_REPLACE_IGNORED_H_
