#include <algorithm>

#include "unsq_eve/inclusive_scan.h"
#include "unsq_eve/reduce.h"
#include "unsq_eve/transform.h"

void std_transform(int* f, int* l) {
  std::transform(f, l, f, [](auto x) { return x + x; });
}
