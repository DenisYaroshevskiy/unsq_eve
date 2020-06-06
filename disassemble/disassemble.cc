#include "unsq_eve/reduce.h"

using T = char;
using traits = unsq_eve::algorithm_traits<int, 256, 4>;

int reduce(const char* f, const char* l) {
  return unsq_eve::reduce<traits>(f, l);
}
