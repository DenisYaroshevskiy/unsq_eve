#
# Copyright 2020 Denis Yaroshevskiy
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

find_package(benchmark CONFIG REQUIRED)

function(add_benchmark name source)
    set(compiler_options --std=c++20 --stdlib=libc++ -arch arm64 -DNDEBUG -DEVE_USE_BMI_ON_AVX2 -g -Werror -Wall -Wextra -Wpedantic -Wno-deprecated-copy -O3 -mllvm -align-all-functions=7)
    add_executable(${name})
    target_sources(${name} PRIVATE ${source})
    target_compile_options(${name} PRIVATE ${compiler_options})
    target_link_libraries(${name} PUBLIC benchmark::benchmark_main pthread)
    target_link_options(${name} PRIVATE -stdlib=libc++)
endfunction()

add_benchmark(std_find std_find.cc)
add_benchmark(std_inclusive_scan std_inclusive_scan.cc)
add_benchmark(std_min_element std_min_element.cc)
add_benchmark(std_reduce std_reduce.cc)
add_benchmark(std_remove std_remove.cc)
add_benchmark(std_reverse std_reverse.cc)
add_benchmark(std_transform std_transform.cc)

add_benchmark(eve_any_of eve_any_of.cc)
add_benchmark(eve_find eve_find.cc)
add_benchmark(eve_inclusive_scan eve_inclusive_scan.cc)
add_benchmark(eve_reduce eve_reduce.cc)
add_benchmark(eve_min_element eve_min_element.cc)
add_benchmark(eve_remove eve_remove.cc)
add_benchmark(eve_reverse eve_reverse.cc)
add_benchmark(eve_transform eve_transform.cc)

add_benchmark(unsq_eve_find_unguarded unsq_eve_find_unguarded.cc)

add_benchmark(ignore_me_simple_inner_product ignore_me_simple_inner_product.cc)
