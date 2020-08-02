#include <algorithm>
#include <numeric>

#include "unsq_eve/all_any_none.h"
#include "unsq_eve/inclusive_scan.h"
#include "unsq_eve/min_element.h"
#include "unsq_eve/reduce.h"
#include "unsq_eve/remove.h"
#include "unsq_eve/transform.h"

using T = int;
using traits = unsq_eve::algorithm_traits<T, 256, 4>;

bool any(const T* f, const T* l, T v) {
  return unsq_eve::any_of_is<traits>(f, l, v);
}
