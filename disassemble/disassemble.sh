clang++ -std=c++20 -mavx2 -mbmi2 -DEVE_USE_BMI_ON_AVX2 --stdlib=libc++ -O3 -DEVE_DISABLE_ASSERTS -I  ../../eve/include -I ../src -S -mllvm --x86-asm-syntax=intel disassemble.cc
