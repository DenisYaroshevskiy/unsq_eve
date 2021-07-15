
#include "unsq_eve/find.h"

using traits = unsq_eve::algorithm_traits<int, 32, 4>;

const int* find_0(const int* f, const int* l) {
  return unsq_eve::find_if<traits>(f, l, [](auto x) { return x == 0; });
}
