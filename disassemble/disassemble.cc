#include <eve/function/add.hpp>
#include "eve_extra/eve_extra.h"

#include <utility>

using wide = eve::wide<int, eve::fixed<8>>;

auto test(wide x, wide y) {
  x = eve_extra::inclusive_scan_wide(x, eve::add, wide{0});
  y = eve_extra::inclusive_scan_wide(y, eve::add, wide{0});
  y += wide{x.back()};
  return std::pair{x, y};
}
