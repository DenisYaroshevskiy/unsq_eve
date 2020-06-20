#include "unsq_eve/inclusive_scan.h"
#include "unsq_eve/reduce.h"
#include "unsq_eve/transform.h"

using T = int;
using traits = unsq_eve::algorithm_traits<T, 256, 4>;

auto reduce(T* f, T* l) { return unsq_eve::reduce<traits>(f, l); }
