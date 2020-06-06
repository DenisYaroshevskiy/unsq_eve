#include "unsq_eve/inclusive_scan.h"

using T = int;
using traits = unsq_eve::algorithm_traits<T, 256, 1>;

void inclusive_scan_inplace(T* f, T* l) {
  unsq_eve::inclusive_scan_inplace_aligned<traits>(f, l);
}
