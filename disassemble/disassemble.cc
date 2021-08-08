#include <eve/algo/remove.hpp>
#include <eve/algo/as_range.hpp>

using T = double;

T* remove(T* f, T* l, T v) {
  return eve::algo::remove(eve::algo::as_range(f, l), v);
}
