#ifndef UNSQ_EVE_REVERSE_H_
#define UNSQ_EVE_REVERSE_H_

#include "eve_extra/eve_extra.h"
#include "unsq_eve/iteration_two_sides_parallel.h"

#include <iostream>

namespace unsq_eve {
namespace _reverse {

template <typename Traits, typename I>
struct body {
  using T = typename Traits::type;
  using wide_read = eve::wide<value_type<I>, width_t<Traits>>;
  using wide = typename Traits::wide;

  static_assert(std::same_as<wide, wide_read>, "Does not make sense otherwise");

  template <typename Ptr>
  EVE_FORCEINLINE void small_array_step(Ptr from,
                                        eve::ignore_first_ ignore) const {
    wide xs = eve_extra::load_unsafe(from, width_t<Traits>{});
    xs = eve_extra::reverse(xs);

    eve_extra::store(xs, from + ignore.count_,
                     eve::ignore_last_(ignore.count_));
  }

  template <typename Ptr>
  EVE_FORCEINLINE void small_array_step(Ptr from,
                                        eve::ignore_last_ ignore) const {
    wide xs = eve_extra::load_unsafe(from, width_t<Traits>{});
    xs = eve_extra::reverse(xs);

    eve_extra::store(xs, from - ignore.count_,
                     eve::ignore_first_(ignore.count_));
  }

  template <typename Ptr>
  EVE_FORCEINLINE void small_step(Ptr lhs, Ptr rhs) const {
    wide xs{lhs}, ys{rhs};
    xs = eve_extra::reverse(xs);
    ys = eve_extra::reverse(ys);
    eve::store(xs, rhs);
    eve::store(ys, lhs);
  }
};

}  // namespace _reverse

template <typename Traits, contigious_iterator I>
void reverse(I _f, I _l) {
  if (_f == _l) return;

  auto [f, l] = drill_down_range(_f, _l);
  _reverse::body<Traits, Pointer<I>> body;
  iteration_two_sides_parallel<iteration_traits_t<Traits>>(f, l, body);
}

}  // namespace unsq_eve

#endif  // UNSQ_EVE_REVERSE_H_
