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
# Target:    tint_lang_spirv_reader_ast_parser
# Kind:      lib
# Condition: TINT_BUILD_SPV_READER
################################################################################
tint_add_target(tint_lang_spirv_reader_ast_parser lib
  lang/spirv/reader/ast_parser/ast_parser.cc
  lang/spirv/reader/ast_parser/ast_parser.h
  lang/spirv/reader/ast_parser/attributes.h
  lang/spirv/reader/ast_parser/construct.cc
  lang/spirv/reader/ast_parser/construct.h
  lang/spirv/reader/ast_parser/entry_point_info.cc
  lang/spirv/reader/ast_parser/entry_point_info.h
  lang/spirv/reader/ast_parser/enum_converter.cc
  lang/spirv/reader/ast_parser/enum_converter.h
  lang/spirv/reader/ast_parser/fail_stream.h
  lang/spirv/reader/ast_parser/function.cc
  lang/spirv/reader/ast_parser/function.h
  lang/spirv/reader/ast_parser/namer.cc
  lang/spirv/reader/ast_parser/namer.h
  lang/spirv/reader/ast_parser/parse.cc
  lang/spirv/reader/ast_parser/parse.h
  lang/spirv/reader/ast_parser/type.cc
  lang/spirv/reader/ast_parser/type.h
  lang/spirv/reader/ast_parser/usage.cc
  lang/spirv/reader/ast_parser/usage.h
)

tint_target_add_dependencies(tint_lang_spirv_reader_ast_parser lib
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
  tint_utils_result
  tint_utils_rtti
  tint_utils_symbol
  tint_utils_text
)

tint_target_add_external_dependencies(tint_lang_spirv_reader_ast_parser lib
  "src_utils"
)

if(TINT_BUILD_SPV_READER)
  tint_target_add_dependencies(tint_lang_spirv_reader_ast_parser lib
    tint_lang_spirv_reader_ast_lower
    tint_lang_spirv_reader_common
  )
endif(TINT_BUILD_SPV_READER)

if(TINT_BUILD_SPV_READER OR TINT_BUILD_SPV_WRITER)
  tint_target_add_external_dependencies(tint_lang_spirv_reader_ast_parser lib
    "spirv-headers"
    "spirv-opt-internal"
  )
endif(TINT_BUILD_SPV_READER OR TINT_BUILD_SPV_WRITER)

endif(TINT_BUILD_SPV_READER)
if(TINT_BUILD_SPV_READER AND TINT_BUILD_WGSL_WRITER)
################################################################################
# Target:    tint_lang_spirv_reader_ast_parser_test
# Kind:      test
# Condition: TINT_BUILD_SPV_READER AND TINT_BUILD_WGSL_WRITER
################################################################################
tint_add_target(tint_lang_spirv_reader_ast_parser_test test
  lang/spirv/reader/ast_parser/ast_parser_test.cc
  lang/spirv/reader/ast_parser/barrier_test.cc
  lang/spirv/reader/ast_parser/constant_test.cc
  lang/spirv/reader/ast_parser/convert_member_decoration_test.cc
  lang/spirv/reader/ast_parser/convert_type_test.cc
  lang/spirv/reader/ast_parser/enum_converter_test.cc
  lang/spirv/reader/ast_parser/fail_stream_test.cc
  lang/spirv/reader/ast_parser/function_arithmetic_test.cc
  lang/spirv/reader/ast_parser/function_bit_test.cc
  lang/spirv/reader/ast_parser/function_call_test.cc
  lang/spirv/reader/ast_parser/function_cfg_test.cc
  lang/spirv/reader/ast_parser/function_composite_test.cc
  lang/spirv/reader/ast_parser/function_conversion_test.cc
  lang/spirv/reader/ast_parser/function_decl_test.cc
  lang/spirv/reader/ast_parser/function_glsl_std_450_test.cc
  lang/spirv/reader/ast_parser/function_logical_test.cc
  lang/spirv/reader/ast_parser/function_memory_test.cc
  lang/spirv/reader/ast_parser/function_misc_test.cc
  lang/spirv/reader/ast_parser/function_var_test.cc
  lang/spirv/reader/ast_parser/get_decorations_test.cc
  lang/spirv/reader/ast_parser/handle_test.cc
  lang/spirv/reader/ast_parser/helper_test.cc
  lang/spirv/reader/ast_parser/helper_test.h
  lang/spirv/reader/ast_parser/import_test.cc
  lang/spirv/reader/ast_parser/module_function_decl_test.cc
  lang/spirv/reader/ast_parser/module_var_test.cc
  lang/spirv/reader/ast_parser/named_types_test.cc
  lang/spirv/reader/ast_parser/namer_test.cc
  lang/spirv/reader/ast_parser/parser_test.cc
  lang/spirv/reader/ast_parser/row_major_matrix_test.cc
  lang/spirv/reader/ast_parser/spirv_tools_helpers_test.cc
  lang/spirv/reader/ast_parser/spirv_tools_helpers_test.h
  lang/spirv/reader/ast_parser/type_test.cc
  lang/spirv/reader/ast_parser/usage_test.cc
  lang/spirv/reader/ast_parser/user_name_test.cc
)

tint_target_add_dependencies(tint_lang_spirv_reader_ast_parser_test test
  tint_api_common
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_type
  tint_lang_wgsl
  tint_lang_wgsl_ast
  tint_lang_wgsl_common
  tint_lang_wgsl_features
  tint_lang_wgsl_program
  tint_lang_wgsl_sem
  tint_lang_wgsl_writer_ir_to_program
  tint_utils
  tint_utils_containers
  tint_utils_diagnostic
  tint_utils_ice
  tint_utils_macros
  tint_utils_math
  tint_utils_memory
  tint_utils_result
  tint_utils_rtti
  tint_utils_symbol
  tint_utils_text
  tint_utils_text_generator
)

tint_target_add_external_dependencies(tint_lang_spirv_reader_ast_parser_test test
  "gtest"
  "src_utils"
)

if(TINT_BUILD_SPV_READER)
  tint_target_add_dependencies(tint_lang_spirv_reader_ast_parser_test test
    tint_lang_spirv_reader_ast_parser
    tint_lang_spirv_reader_common
  )
endif(TINT_BUILD_SPV_READER)

if(TINT_BUILD_SPV_READER OR TINT_BUILD_SPV_WRITER)
  tint_target_add_external_dependencies(tint_lang_spirv_reader_ast_parser_test test
    "spirv-headers"
    "spirv-opt-internal"
    "spirv-tools"
  )
endif(TINT_BUILD_SPV_READER OR TINT_BUILD_SPV_WRITER)

if(TINT_BUILD_WGSL_WRITER)
  tint_target_add_dependencies(tint_lang_spirv_reader_ast_parser_test test
    tint_lang_wgsl_writer
    tint_lang_wgsl_writer_ast_printer
  )
endif(TINT_BUILD_WGSL_WRITER)

endif(TINT_BUILD_SPV_READER AND TINT_BUILD_WGSL_WRITER)