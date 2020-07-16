#include <algorithm>
#include <numeric>

#include "unsq_eve/inclusive_scan.h"
#include "unsq_eve/min_element.h"
#include "unsq_eve/reduce.h"
#include "unsq_eve/transform.h"

using T = int;
using traits = unsq_eve::algorithm_traits<T, 256, 4>;

T* min_element(T* f, T* l) { return unsq_eve::min_element<traits>(f, l); }
