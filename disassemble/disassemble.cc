#include <eve/algo/remove.hpp>
#include <eve/algo/as_range.hpp>

#include <eve/algo/inclusive_scan.hpp>

using T = int;

void inclusive_scan(T* f, T* l) {
  eve::algo::inclusive_scan_inplace(eve::algo::as_range(f, l), eve::zero);
}
