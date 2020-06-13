// #include "unsq_eve/transform.h"
#include "unsq_eve/inclusive_scan.h"

using T = short;
using traits = unsq_eve::algorithm_traits<T, 256, 2>;

void transform(T* f, T* l) {
  unsq_eve::inclusive_scan_inplace_aligned<traits>(f, l);
}
