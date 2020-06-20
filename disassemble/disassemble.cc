#include "unsq_eve/inclusive_scan.h"
#include "unsq_eve/reduce.h"
#include "unsq_eve/transform.h"

using T = int;
using traits = unsq_eve::algorithm_traits<T, 256, 4>;

void transform(T* f, T* l) {
  unsq_eve::transform<traits>(f, l, [](auto x) { return x + x; });
}
