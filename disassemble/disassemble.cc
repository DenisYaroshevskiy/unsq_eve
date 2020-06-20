#include <algorithm>
#include <numeric>

#include "unsq_eve/inclusive_scan.h"
#include "unsq_eve/reduce.h"
#include "unsq_eve/transform.h"

auto std_reduce(int* f, int* l) { return std::reduce(f, l); }
