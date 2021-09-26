#include <eve/algo/remove.hpp>
#include <eve/algo/as_range.hpp>

#include <vector>

using T = int;

void remove(std::vector<T>& v) {
  eve::algo::remove(v, 0);
}
