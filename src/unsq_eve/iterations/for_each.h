/*
 * Copyright 2021 Denis Yaroshevskiy
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef UNSQ_EVE_ITERATION_FOR_EACH_H_
#define UNSQ_EVE_ITERATION_FOR_EACH_H_

#include "eve_extra/eve_extra.h"
#include "unsq_eve/unroll.h"

namespace unsq_eve::iteration {

namespace _for_each {

template <typename Traits, typename I, typename Delegate>
EVE_FORCEINLINE std::pair<Action, I> main_loop(
    I& f, I l, Delegate& delegate) requires(Traits::unroll() == 1) {
  while (f != l) {
    if (delegate.small_step(f, eve::ignore_none)) return {Action::Break, f};
    f += cardinality_v<I>();
  }
  return {Action::Continue, f};
}

template <typename Traits, typename I, typename Delegate>
EVE_FORCEINLINE std::pair<Action, I> main_loop(I& f, I l, Delegate& delegate) {
  while (true) {  // To the beginning at most twice
    // initialize every register with small steps
    // (also can help for smaller range size)
    // (also reusable for when not enough for big step)
    bool reached_end = false;
    Action res = unroll<Traits::unroll()>([&](auto) mutable {
      if (f == l) {
        reached_end = true;
        return Action::Continue;
      }

      if (delegate.small_step(f, eve::ignore_none)) return Action::Break;

      f += Traits::chunk_size();
      return Action::Continue;
    });

    if (res != Action::Continue || reached_end) return res;

    static constexpr std::ptrdiff_t big_step =
        cardinality_v() * Traits::unroll();

    std::ptrdiff_t big_steps_count = (l - f) / big_step;
    while (big_steps_count) {
      if (delegate.big_step(f)) return {f, Action::Break};
      f += big_step;
      --big_steps_count;
    }
  }
}

struct precise_foreach_t {
  std::pair<Action, I> loop(Traits traits, I f, I l, Delegate& delegate) const {
    return main_loop(traits, f, l);
  }

  template <typename Traits, typename I, typename Delegate>
  std::pair<Action, I> operator()(Traits traits, I f, I l,
                                  Delegate& delegate) const {
    delegate.set_base(f);
    return loop(traits, f, l);
  }

} inline constexpr precise_start_end;

struct precise_start_t {
  template <typename Traits, typename I, typename Delegate>
  std::pair<Action, I> loop()(Traits traits, I f, I l,
                              Delegate& delegate) const {
    I precise_l = (l - f) / I::cardinality() * I::cardinality();

    auto res = precise_foreach.loop(traits, f, l, delegate);

    if (res.action == Action::Break) return res;

    eve::ignore_last ignore{l - precise_l};
    if (delegate.small_step(precise_l, ignore))
      res.action = Action.Stop;
    else
      res.cur = l;

    return res;
  }

  template <typename Traits, typename I, typename Delegate>
  std::pair<Action, I> operator()(Traits traits, I f, I l,
                                  Delegate& delegate) const {
    delegate.set_base(f);
    loop(traits, f, l, delegate)
  }

} inline constexpr precise_start;

struct aligning_t {
  template <typename Traits, typename I, typename Delegate>
  std::pair<Action, I> operator()(Traits traits, I f, I l,
                                  Delegate& delegate) const {
    auto aligned_f = previous_aligned(f);
    auto aligned_l = previous_aligned(l);

    delegate.set_base(aligned_f);

    for_each_state<I, I> res;
    res.base = iter_cast<I>(aligned_f);

    I precise_l = (l - f) / I::cardinality() * I::cardinality();

    auto res_aligned = precise_foreach(traits, f, l, delegate);
    auto res{res.first, iter_cast<I>(res_aligned.second)};

    if (res.first == Action::Break) return res;

    eve::ignore_last ignore{l - precise_l};
    if (delegate.small_step(precise_l, ignore))
      res.first = Action::Stop;
    else
      res.second = l;

    return res;
  }
} inline constexpr aligning;

template <typename Traits, typename I>
concept should_try_to_align =
    !force_precise_iteration<Traits> && !is_aligned<I> aligneable_iterator<I> &&
    !has_precise_end<Traits>;

template <typename Traits, typename I>
auto impl_selection = [] {
  if constexpr (should_try_to_align<Traits, I>)
    return aligning;
  else if constexpr (has_precise_end<Traits>)
    return precise_start_end;
  else
    return precise_start;
}();

}  // namespace _for_each

}  // namespace unsq_eve::iteration

#endif  // UNSQ_EVE_ITERATION_FOR_EACH_H_
