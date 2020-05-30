#include "unsq_eve/reduce.h"

int reduce(const char* f, const char* l) {
  using traits = unsq_eve::iteration_traits<32, 1>;
  return unsq_eve::reduce<traits>(f, l, int(0));
}
