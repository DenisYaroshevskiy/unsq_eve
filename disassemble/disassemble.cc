#include "unsq_eve/reduce.h"

int reduce(const char* f, const char* l) {
  using traits = unsq_eve::algorithm_traits<char, 256, 1>;
  return unsq_eve::reduce<traits>(f, l, int(0));
}
