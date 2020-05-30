#include "eve_extra/eve_extra.h"

#include <eve/function/add.hpp>

using wide = eve::wide<int, eve::fixed<32>>;

wide reduce(wide x) {
  return eve_extra::reduce_wide(x, eve::add);
}
