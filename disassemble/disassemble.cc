#include "unsq_eve/inclusive_scan.h"

using T = int;
using traits = unsq_eve::algorithm_traits<T, 128, 4>;

void inclusive_scan_inplace(int* f, int* l) {
  unsq_eve::inclusive_scan_inplace_aligned<traits>(f, l);
}
