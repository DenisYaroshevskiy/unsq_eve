#include "unsq_eve/inclusive_scan.h"
#include "unsq_eve/transform.h"

using T = short;
using traits = unsq_eve::algorithm_traits<T, 256, 4>;

void transform_unaligned(T* f, T* l) {
  unsq_eve::transform_unaligned<traits>(f, l, [](auto x) { return x + x; });
}

/*
void inclusive_scan(T* f, T* l) {
  unsq_eve::inclusive_scan_inplace_overlap_stores<traits>(f, l);
}
*/
