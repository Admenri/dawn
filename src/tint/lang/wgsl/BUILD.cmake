# Copyright 2023 The Dawn & Tint Authors
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

################################################################################
# File generated by 'tools/src/cmd/gen' using the template:
#   tools/src/cmd/gen/build/BUILD.cmake.tmpl
#
# To regenerate run: './tools/run gen'
#
#                       Do not modify this file directly
################################################################################

include(lang/wgsl/ast/BUILD.cmake)
include(lang/wgsl/common/BUILD.cmake)
include(lang/wgsl/features/BUILD.cmake)
include(lang/wgsl/helpers/BUILD.cmake)
include(lang/wgsl/inspector/BUILD.cmake)
include(lang/wgsl/intrinsic/BUILD.cmake)
include(lang/wgsl/ir/BUILD.cmake)
include(lang/wgsl/ls/BUILD.cmake)
include(lang/wgsl/program/BUILD.cmake)
include(lang/wgsl/reader/BUILD.cmake)
include(lang/wgsl/resolver/BUILD.cmake)
include(lang/wgsl/sem/BUILD.cmake)
include(lang/wgsl/writer/BUILD.cmake)

################################################################################
# Target:    tint_lang_wgsl
# Kind:      lib
################################################################################
tint_add_target(tint_lang_wgsl lib
  lang/wgsl/builtin_fn.cc
  lang/wgsl/builtin_fn.h
  lang/wgsl/diagnostic_rule.cc
  lang/wgsl/diagnostic_rule.h
  lang/wgsl/diagnostic_severity.cc
  lang/wgsl/diagnostic_severity.h
  lang/wgsl/extension.cc
  lang/wgsl/extension.h
)

tint_target_add_dependencies(tint_lang_wgsl lib
  tint_utils
  tint_utils_containers
  tint_utils_diagnostic
  tint_utils_ice
  tint_utils_macros
  tint_utils_math
  tint_utils_memory
  tint_utils_rtti
  tint_utils_text
)

tint_target_add_external_dependencies(tint_lang_wgsl lib
  "src_utils"
)

################################################################################
# Target:    tint_lang_wgsl_test
# Kind:      test
################################################################################
tint_add_target(tint_lang_wgsl_test test
  lang/wgsl/diagnostic_rule_test.cc
  lang/wgsl/diagnostic_severity_test.cc
  lang/wgsl/extension_test.cc
  lang/wgsl/language_feature_status_test.cc
  lang/wgsl/language_feature_test.cc
  lang/wgsl/wgsl_test.cc
)

tint_target_add_dependencies(tint_lang_wgsl_test test
  tint_api_common
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_ir
  tint_lang_core_type
  tint_lang_wgsl
  tint_lang_wgsl_ast
  tint_lang_wgsl_common
  tint_lang_wgsl_features
  tint_lang_wgsl_program
  tint_lang_wgsl_sem
  tint_lang_wgsl_writer_ir_to_program
  tint_lang_wgsl_writer_raise
  tint_utils
  tint_utils_containers
  tint_utils_diagnostic
  tint_utils_ice
  tint_utils_macros
  tint_utils_math
  tint_utils_memory
  tint_utils_rtti
  tint_utils_symbol
  tint_utils_text
)

tint_target_add_external_dependencies(tint_lang_wgsl_test test
  "gtest"
  "src_utils"
)

if(TINT_BUILD_WGSL_READER)
  tint_target_add_dependencies(tint_lang_wgsl_test test
    tint_lang_wgsl_reader
    tint_lang_wgsl_reader_program_to_ir
  )
endif(TINT_BUILD_WGSL_READER)

if(TINT_BUILD_WGSL_READER AND TINT_BUILD_WGSL_WRITER)
  tint_target_add_sources(tint_lang_wgsl_test test
    "lang/wgsl/ir_roundtrip_test.cc"
  )
endif(TINT_BUILD_WGSL_READER AND TINT_BUILD_WGSL_WRITER)

if(TINT_BUILD_WGSL_WRITER)
  tint_target_add_dependencies(tint_lang_wgsl_test test
    tint_lang_wgsl_writer
  )
endif(TINT_BUILD_WGSL_WRITER)

################################################################################
# Target:    tint_lang_wgsl_bench
# Kind:      bench
################################################################################
tint_add_target(tint_lang_wgsl_bench bench
  lang/wgsl/diagnostic_rule_bench.cc
  lang/wgsl/diagnostic_severity_bench.cc
  lang/wgsl/extension_bench.cc
)

tint_target_add_dependencies(tint_lang_wgsl_bench bench
  tint_lang_wgsl
  tint_utils
  tint_utils_containers
  tint_utils_diagnostic
  tint_utils_ice
  tint_utils_macros
  tint_utils_math
  tint_utils_memory
  tint_utils_rtti
  tint_utils_text
)

tint_target_add_external_dependencies(tint_lang_wgsl_bench bench
  "google-benchmark"
  "src_utils"
)
