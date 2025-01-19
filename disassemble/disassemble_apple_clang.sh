clang++ --std=c++20 --stdlib=libc++ -mcpu=apple-m2 -DNDEBUG -Werror -O3 -DEVE_DISABLE_ASSERTS -I  ../../eve/include -I ../src -S disassemble.cc -o disassemble_arm.s
