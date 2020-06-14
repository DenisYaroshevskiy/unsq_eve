#include "unsq_eve/transform.h"

using T = short;
using traits = unsq_eve::algorithm_traits<T, 256, 4>;

void transform(T* f, T* l) {
  unsq_eve::transform<traits>(f, l, [](auto x) { return x + x; });
}
