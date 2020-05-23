#include "eve_extra/eve_extra.h"
#include "unsq_eve/all_any_none.h"

struct traits : unsq_eve::iteration_traits<eve::fixed<32>, 4> {
  static constexpr bool use_extra_any = true;
};

bool any_zeroes(const char* f, const char* l) { return unsq_eve::any_of_is<traits>(f, l, 0); }
