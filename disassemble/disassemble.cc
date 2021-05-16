
#include "unsq_eve/all_any_none.h"

using traits = unsq_eve::algorithm_traits<int, 32, 4>;

bool any_zeroes(const int* f, const int* l) {
  return unsq_eve::any_of<traits>(f, l, [](auto x) { return x == 0; });
}
