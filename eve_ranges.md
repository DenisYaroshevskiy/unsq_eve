# EVE Ranges, design doc

This is a design doc on how implementing extensible stl like algorithms in EVE can be done.
It is mostly looking into what should be doable and issues that we found so far - everything is up for discussion.
Most code was not compiled so can contain some naive issues.

## GOALS

__Potential for all STL algorithms__<br/>
Even though some algorithms like sort, remove or merge require quite complicated simd operations that I don’t see in our immediate future, we have to have a clear understanding on how we would like them to look.

__ZIP support__<br/>
There are two ways of structuring data: AoS (array of structs) and SoA (structs of arrays). For SIMD however using AoS is much worse since one would need to do complicated shuffles in order to extract fields. Which means we need to support SoA as a first class citizen - hense ZIP.

__Close to STL / ranges interface by default__<br/>
C++ developers are familiar with STL and we want to capitalize on that experience. However in some cases the STL interfaces will be extremely inefficient (for example - copy_if requires to know the output size in SIMD implementation), in which case we want to be very explicit about it and guarantee compilation breakage.

_Alternative_: we can sacrifice the consistency with STL in order to be internally consistent, for example since we need to know the output size for copy_if we can demand it for transform as well.

__Customizability__<br/>
Even though we want simplicity by default, SIMD is mostly about efficiency, so we want to provide nobs to tweak things like unrolling, guarantee that the range length is divisible by the cardinality of the register etc. The specific tweaks are algorithm specific.

__One argument type for callbacks__<br/>
There are maybe some incentives to use different register width within the same algorithm. However it makes writing custom predicates much more complicated. Consider a trick with implementing is_space with a shuffle on sse4. We want to just be able to pass that to find without needing to deal with different wide cardinalities.

## NON-GOALS

__Non contiguous ranges__<br/>
Theoretically using gather and scatter we could implement support for non contiguous ranges. However, we believe it to be a very niche use case and do not take it into account at the moment.

__Conceptually different iterator/sentinel types__<br/>
Though std::ranges found a great use out of smth like counted ranges, we do not yet see how to incorporate them efficiently

## Usage examples

First let’s have a look at the interface level with some examples

__helpers__

A typedef for a vector to use aligned allocator.
```
template <typename T>
using aliged_vector =
    std::vector<T, eve::aligned_allocator<T, sizeof(eve::wide<T>)>;
```

A complex predicate that the user might want to avoid unrolling
```
auto complex_check = [threshold = eve::wide<float>(0.3f)]
	(eve::wide<float> x) { return sin(x) < threshold; };
```

__find a number__

```
find(int const*, int const*, int) -> int const*
find(std::vector<int> const&, int) -> std::vector<int>::const_iterator
```

This usecase illustrates that we need to do one of two things: either propogate iterators all the way through the system or have some sort of interface unification on the top level.

__find a number matching some condition__

```
find_if(int const*, int const*,
       [](eve::wide<int> x) { return x > 5; }) -> int const*
find_if(float const*, float const*, complex_check) -> float const*
```

We are illustrating here that the predicate always accepts
wide\<int\> and the user does not have to deal with different
widths. This is especially useful if the user needs to drop down to the intrinsic level from eve.

__find with aligned start__

```
find(aligned_ptr<int const>, int const*, int) -> int const*
find(aligned_vector<int> const&, int) ->
     aligned_vector<int>::const_iterator
```

We should be able to pass an `aligned_ptr` instead of the first argument.
However we can't return `aligned_ptr` since the position might be not aligned.

__Disable unrolling__

```
find(eve::ranges::no_unrolling,
     eve::aligned_ptr<float const>, float const*,
     complex_check) -> float const*
find(eve::ranges::no_unrolling,
     const aligned_vector<float>&,
     complex_check)-> aligned_vector<float>::const_iterator
```

The default unrolling in my experiments should probably be 4. However, the user should be able to tweak it. When she has a complicated check - the unroll should be disabled by the user. One possible way to control it is with optional traits parameter.

__Aligned end__

```
find(eve::ranges::aligned_from_both_sides(
      aligned_vector<float>::const_iterator,
      aligned_vector<float>::const_iterator),
     complex_check) -> float const*
```

When executing implementing a both multithreaded and simd optimized search, we can control the division in sub ranges. In this case we might want to align both sides so there are no ends to clean up for most threads. EVE should support this. One way'd be to pass aligned_ptr for both begin/end or here we use example of `aligned_from_both_sides` helper.

__Mismatch using find__

Fundamentally, mismatch and find are the same algorithm, just operating on zipped ranges. We need to take into account the conversions.

```
// We are better off using structs instead of functions since we
// can share some properties between different algorithms.

struct mismatch_t {
  // We want to reuse the default traits from find.
  static constexpr auto default_traits =
      eve::ranges::find_t::default_traits;

  // Basic version
  template <
    eve::ranges::input_iterator I1,  // eve has to have it's own
    eve::ranges::input_iterator I2,  // iterator concept see below
    typename P                       // concept on the predicate is
                                     // a touch tricky.
  >
  auto operator()(
    auto traits,
    I1 f1,                        // Since we can do aligned/non-aligned
    eve::ranges::sentinel<I1> l1, // pointers - we need to have
                                  // different types for begin/end
    I2 f2,
    P p,
  ) const ->
    std::pair<                             // We need to strip
      eve::ranges::unaligned_iterator<I1>, // alignment from result
      eve::ranges::unaligned_iterator<I2>  // type
    >
  {
    // We need to understand the cardinality we operate on.
    // Each iterator has it's cardinality.
    // Traits can supply custom cardinality
    auto N =
      eve::ranges::select_cardinality(traits,
        eve::caridnality<I1>{},
        eve::cardinality<I2>{});

    // Get a zipped range, length == to the [f1, l1)
    // Maybe we need to put some of the cardinality buisness in zip.
    auto zipped = eve::ranges::zip(
      eve::cardinaltiy_cast<N>(eve::ranges::range_pair{f1, l1}),
      eve::cardinality_cast<N>(f2)
    );

    auto [r1, r2] = eve::ranges::find(traits, zipped,
       [&](
         // Element type of the zipped is a tuple of wides
         // for each range. They have to have the same cardinality.
         tuple<
            eve::wide<eve::value_type<I1>, N>,
            eve::wide<eve::value_type<I2>, N>
          > e
       ) {
         // After the bugs we reported to compilers
         // We expect negeation to be properly optimized
         return !p(get<0>(e), get<1>(e)));
       });

    // After zip we need to undo our zipping.
    // The find will already deal with unwrapping alignments.
    return std::pair{
      eve::cardinality_cast<eve::caridnality<I1>>(r1),
      eve::cardinality_cast<eve::caridnality<I2>>(r2),
    };
  }

  // Using default eqaulity
  template <
    eve::ranges::input_iterator I1,
    eve::ranges::input_iterator I2
  >
  auto operator()(auto traits,
                  I1 f1, eve::ranges::sentinel<I1> l1,
                  I2 l2) const {
    // Equality can only be applied to the same type.
    // Assuming we can `load(as_)` we can have a converting_iterator
    using common_t = std::common_type<
      eve::ranges::value_type<I1>, eve::ranges::value_type<I2>>;

    auto [r1, r2] = missmatch(
      eve::ranges::make_converting_iterator<common_t>(f1),
      eve::ranges::make_converting_iterator<common_t>(l1),
      eve::ranges::make_converting_iterator<common_t>(f2),
      eve::equals);

    // Not sure if base is the correct way to do it.
    // The casts between iterators definetly require more thinking
    return std::pair{r1.base(), r2.base()};
  }
} constexpr mismatch;

```
