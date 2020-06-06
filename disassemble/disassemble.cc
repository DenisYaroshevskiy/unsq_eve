#include "unsq_eve/reduce.h"

using T = char;
using traits = unsq_eve::algorithm_traits<short, 256, 4>;

short reduce(const char* f, const char* l) {
  return unsq_eve::reduce<traits>(f, l);
}
