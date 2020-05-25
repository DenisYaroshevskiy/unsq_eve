#include "unsq_eve/find.h"

using traits = unsq_eve::iteration_traits<32, 4>;

const char* find_zeroe(const char* f, const char* l) {
  return unsq_eve::find<traits>(f, l, 0);
}
