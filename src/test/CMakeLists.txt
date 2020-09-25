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

add_executable(tests)

target_sources(tests PRIVATE
               eve_extra/any.t.cc
               eve_extra/compress_mask.t.cc
               eve_extra/compress_store.t.cc
               eve_extra/concepts.t.cc
               eve_extra/eve_extra.t.cc
               eve_extra/first_true_array.t.cc
               eve_extra/first_true.t.cc
               eve_extra/mmask_operations.t.cc
               eve_extra/reduce_wide.t.cc
               eve_extra/replace_ignored.t.cc
               eve_extra/reverse.t.cc
               eve_extra/scan_wide.t.cc
               eve_extra/shift_pair.t.cpp
               eve_extra/store.t.cc
               eve_extra/swap_adjacent_groups.t.cc
               unsq_eve/all_any_none.t.cc
               unsq_eve/concepts.t.cc
               unsq_eve/find_common.t.cc
               unsq_eve/inclusive_scan_inplace.t.cc
               unsq_eve/min_element.t.cc
               unsq_eve/reduce.t.cc
               unsq_eve/remove.t.cc
               unsq_eve/strlen_example.t.cc
               unsq_eve/transform_inplace.t.cc
               unsq_eve/transform_reduce.types.t.cc
               unsq_eve/unroll.t.cc
               catch_main.cc)

target_compile_options(tests PRIVATE
                       -Werror -Wall -Wextra -Wpedantic -Og -g
                       -DEVE_DISABLE_ASSERTS
                        -fno-omit-frame-pointer
                       --std=c++20
                       -stdlib=libc++
                       -fsanitize=address
                       -march=native)
target_link_options(tests PRIVATE -fsanitize=address -stdlib=libc++)
