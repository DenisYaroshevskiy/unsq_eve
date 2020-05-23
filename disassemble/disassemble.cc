#include "eve_extra/eve_extra.h"

using logical = eve::logical<eve::wide<char, eve::fixed<32 * 4>>>;
/*using small_wide = eve::wide<char, eve::fixed<32>>;

bool eve_greater(const small_wide& x, const small_wide& y) {
  return eve::any(x > y);
}*/

bool eve_extra_any(const logical& vbool) {
  return eve_extra::any(vbool, eve_extra::ignore_nothing{});
}

/*
bool eve_any(const logical& vbool) {
  return eve::any(vbool);
}
*/
