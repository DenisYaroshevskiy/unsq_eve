clang++ -std=c++17 -O3 -DEVE_DISABLE_ASSERTS  -march=native -I ../../eve/include -I ../src -S -mllvm --x86-asm-syntax=intel disassemble.cc
