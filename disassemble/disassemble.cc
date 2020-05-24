#include "eve_extra/eve_extra.h"
#include "unsq_eve/all_any_none.h"

using traits = unsq_eve::iteration_traits<32, 1>;

bool any_zeroes(const char* f, const char* l) { return unsq_eve::any_of_is<traits>(f, l, 0); }
