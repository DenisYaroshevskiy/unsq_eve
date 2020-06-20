#include "unsq_eve/inclusive_scan.h"
#include "unsq_eve/reduce.h"
#include "unsq_eve/transform.h"

using T = int;
using traits = unsq_eve::algorithm_traits<T, 256, 1>;

void inclusive_scan(T* f, T* l) {
  unsq_eve::inclusive_scan_inplace<traits>(f, l);
}
