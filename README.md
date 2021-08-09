# Benchmarks for [EVE library](https://github.com/jfalcou/eve)

This repo for most part now contains benchmarks for algorithms in [EVE  library](https://github.com/jfalcou/eve).
(Plus some things I did not upstream yet/or that I shouldn't really upstream).

The results can be found [here](https://denisyaroshevskiy.github.io/unsq_eve/).

## What happened to the algoithms

Most of the algorithms are upstreamed and are ported across different architectures. They are now in [eve/algo](https://github.com/jfalcou/eve/tree/develop/include/eve/algo).

## Everything I wrote/said about SIMD algorithms

Talks:
* "My First Simd": [english](https://youtu.be/d6NcnyXjc3I) /
[russian](https://youtu.be/fzUrYTTug8Y).

StackOverflow
* remove using BMI measurements/explanation: https://stackoverflow.com/a/61431303/5021064
* remove using small masks (did not yet write a proper StackOverflow answer): https://github.com/jfalcou/eve/pull/844
* store part of the register (2 answers, transform and incusive_scan explained): https://stackoverflow.com/questions/62183557/how-to-most-efficiently-store-a-part-of-m128i-m256i-while-ignoring-some-num/62492369#62492369
* horisontal boolean reduction on arm (any/find - no numbers): https://stackoverflow.com/a/66215675/5021064
