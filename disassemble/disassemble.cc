#include "unsq_eve/find.h"

std::size_t my_strlen(char* s) {
  using traits = unsq_eve::iteration_traits<32, 1>;
  char* found = unsq_eve::find_unguarded<traits>(s, 0);
  return static_cast<std::size_t>(found - s);
}
