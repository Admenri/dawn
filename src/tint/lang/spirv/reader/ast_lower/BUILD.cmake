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

if(TINT_BUILD_SPV_READER)
################################################################################
# Target:    tint_lang_spirv_reader_ast_lower
# Kind:      lib
# Condition: TINT_BUILD_SPV_READER
################################################################################
tint_add_target(tint_lang_spirv_reader_ast_lower lib
  lang/spirv/reader/ast_lower/atomics.cc
  lang/spirv/reader/ast_lower/atomics.h
  lang/spirv/reader/ast_lower/decompose_strided_array.cc
  lang/spirv/reader/ast_lower/decompose_strided_array.h
  lang/spirv/reader/ast_lower/decompose_strided_matrix.cc
  lang/spirv/reader/ast_lower/decompose_strided_matrix.h
  lang/spirv/reader/ast_lower/fold_trivial_lets.cc
  lang/spirv/reader/ast_lower/fold_trivial_lets.h
  lang/spirv/reader/ast_lower/pass_workgroup_id_as_argument.cc
  lang/spirv/reader/ast_lower/pass_workgroup_id_as_argument.h
  lang/spirv/reader/ast_lower/transpose_row_major.cc
  lang/spirv/reader/ast_lower/transpose_row_major.h
)

tint_target_add_dependencies(tint_lang_spirv_reader_ast_lower lib
  tint_api_common
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_type
  tint_lang_wgsl
  tint_lang_wgsl_ast
  tint_lang_wgsl_ast_transform
  tint_lang_wgsl_common
  tint_lang_wgsl_features
  tint_lang_wgsl_program
  tint_lang_wgsl_resolver
  tint_lang_wgsl_sem
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

tint_target_add_external_dependencies(tint_lang_spirv_reader_ast_lower lib
  "src_utils"
)

endif(TINT_BUILD_SPV_READER)
if(TINT_BUILD_SPV_READER AND TINT_BUILD_WGSL_READER AND TINT_BUILD_WGSL_WRITER)
################################################################################
# Target:    tint_lang_spirv_reader_ast_lower_test
# Kind:      test
# Condition: TINT_BUILD_SPV_READER AND TINT_BUILD_WGSL_READER AND TINT_BUILD_WGSL_WRITER
################################################################################
tint_add_target(tint_lang_spirv_reader_ast_lower_test test
  lang/spirv/reader/ast_lower/atomics_test.cc
  lang/spirv/reader/ast_lower/decompose_strided_array_test.cc
  lang/spirv/reader/ast_lower/decompose_strided_matrix_test.cc
  lang/spirv/reader/ast_lower/fold_trivial_lets_test.cc
  lang/spirv/reader/ast_lower/pass_workgroup_id_as_argument_test.cc
  lang/spirv/reader/ast_lower/transpose_row_major_test.cc
)

tint_target_add_dependencies(tint_lang_spirv_reader_ast_lower_test test
  tint_api_common
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_ir
  tint_lang_core_type
  tint_lang_wgsl
  tint_lang_wgsl_ast
  tint_lang_wgsl_ast_transform
  tint_lang_wgsl_common
  tint_lang_wgsl_features
  tint_lang_wgsl_program
  tint_lang_wgsl_resolver
  tint_lang_wgsl_sem
  tint_lang_wgsl_writer_ir_to_program
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

tint_target_add_external_dependencies(tint_lang_spirv_reader_ast_lower_test test
  "gtest"
  "src_utils"
)

if(TINT_BUILD_SPV_READER)
  tint_target_add_dependencies(tint_lang_spirv_reader_ast_lower_test test
    tint_lang_spirv_reader_ast_lower
  )
endif(TINT_BUILD_SPV_READER)

if(TINT_BUILD_WGSL_READER)
  tint_target_add_dependencies(tint_lang_spirv_reader_ast_lower_test test
    tint_lang_wgsl_reader
    tint_lang_wgsl_reader_parser
  )
endif(TINT_BUILD_WGSL_READER)

if(TINT_BUILD_WGSL_READER AND TINT_BUILD_WGSL_WRITER)
  tint_target_add_dependencies(tint_lang_spirv_reader_ast_lower_test test
    tint_lang_wgsl_ast_transform_test
  )
endif(TINT_BUILD_WGSL_READER AND TINT_BUILD_WGSL_WRITER)

if(TINT_BUILD_WGSL_WRITER)
  tint_target_add_dependencies(tint_lang_spirv_reader_ast_lower_test test
    tint_lang_wgsl_writer
  )
endif(TINT_BUILD_WGSL_WRITER)

endif(TINT_BUILD_SPV_READER AND TINT_BUILD_WGSL_READER AND TINT_BUILD_WGSL_WRITER)