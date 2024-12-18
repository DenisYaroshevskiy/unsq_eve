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
               eve_extra/concepts.t.cc
               unsq_eve/concepts.t.cc
               unsq_eve/find_common.t.cc
               unsq_eve/other_searches.t.cc
               unsq_eve/unroll.t.cc
               tts_main.cc)

target_compile_options(tests PRIVATE
                       -Werror -Wall -Wextra -Wpedantic -Wno-deprecated-copy -Og -g
                       -DEVE_DISABLE_ASSERTS
                        -fno-omit-frame-pointer
                       --std=c++20
                       -stdlib=libc++)
target_link_options(tests PRIVATE -stdlib=libc++)
