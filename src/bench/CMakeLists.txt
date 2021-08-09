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

find_package(benchmark)

function(add_benchmark name source)
    set(compiler_options --std=c++20 --stdlib=libc++ -DNDEBUG -g -Werror -Wall -Wextra -Wpedantic -Wno-deprecated-copy -O3 -march=native -mllvm -align-all-functions=7)
    add_executable(${name})
    target_sources(${name} PRIVATE ${source})
    target_compile_options(${name} PRIVATE ${compiler_options})
    target_link_libraries(${name} PUBLIC benchmark pthread)
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
add_benchmark(eve_reduce eve_reduce.cc)
add_benchmark(eve_remove eve_remove.cc)

add_benchmark(unsq_eve_any_of unsq_eve_any_of.cc)
add_benchmark(unsq_eve_find_guarded unsq_eve_find_guarded.cc)
add_benchmark(unsq_eve_find_unguarded unsq_eve_find_unguarded.cc)
add_benchmark(unsq_eve_inclusive_scan unsq_eve_inclusive_scan.cc)
add_benchmark(unsq_eve_min_element unsq_eve_min_element.cc)
add_benchmark(unsq_eve_reduce unsq_eve_reduce.cc)
add_benchmark(unsq_eve_reduce_min unsq_eve_reduce_min.cc)
add_benchmark(unsq_eve_remove unsq_eve_remove.cc)
add_benchmark(unsq_eve_reverse unsq_eve_reverse.cc)
add_benchmark(unsq_eve_transform unsq_eve_transform.cc)
