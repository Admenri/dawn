# Copyright 2024 The Dawn & Tint Authors
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

if(TINT_BUILD_IR_BINARY AND TINT_BUILD_IR_FUZZER AND TINT_BUILD_WGSL_WRITER AND TINT_BUILD_SPV_WRITER)
################################################################################
# Target:    tint_cmd_fuzz_ir_dis_cmd
# Kind:      cmd
# Condition: TINT_BUILD_IR_BINARY AND TINT_BUILD_IR_FUZZER AND TINT_BUILD_WGSL_WRITER AND TINT_BUILD_SPV_WRITER
################################################################################
tint_add_target(tint_cmd_fuzz_ir_dis_cmd cmd
  cmd/fuzz/ir/dis/main.cc
)

tint_target_add_dependencies(tint_cmd_fuzz_ir_dis_cmd cmd
  tint_api
  tint_api_common
  tint_cmd_common
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_ir
  tint_lang_core_type
  tint_lang_wgsl
  tint_lang_wgsl_ast
  tint_lang_wgsl_common
  tint_lang_wgsl_features
  tint_lang_wgsl_inspector
  tint_lang_wgsl_program
  tint_lang_wgsl_sem
  tint_lang_wgsl_writer_ir_to_program
  tint_utils_cli
  tint_utils_containers
  tint_utils_diagnostic
  tint_utils_ice
  tint_utils_id
  tint_utils_macros
  tint_utils_math
  tint_utils_memory
  tint_utils_reflection
  tint_utils_result
  tint_utils_rtti
  tint_utils_strconv
  tint_utils_symbol
  tint_utils_text
  tint_utils_traits
)

if(TINT_BUILD_IR_BINARY)
  tint_target_add_dependencies(tint_cmd_fuzz_ir_dis_cmd cmd
    tint_lang_core_ir_binary
  )
endif(TINT_BUILD_IR_BINARY)

if(TINT_BUILD_IR_BINARY AND TINT_BUILD_IR_FUZZER)
  tint_target_add_dependencies(tint_cmd_fuzz_ir_dis_cmd cmd
    tint_utils_protos_ir_fuzz_proto
  )
endif(TINT_BUILD_IR_BINARY AND TINT_BUILD_IR_FUZZER)

if(TINT_BUILD_SPV_READER)
  tint_target_add_dependencies(tint_cmd_fuzz_ir_dis_cmd cmd
    tint_lang_spirv_reader_common
  )
endif(TINT_BUILD_SPV_READER)

if(TINT_BUILD_SPV_READER OR TINT_BUILD_SPV_WRITER)
  tint_target_add_external_dependencies(tint_cmd_fuzz_ir_dis_cmd cmd
    "spirv-tools"
  )
endif(TINT_BUILD_SPV_READER OR TINT_BUILD_SPV_WRITER)

if(TINT_BUILD_SPV_WRITER)
  tint_target_add_dependencies(tint_cmd_fuzz_ir_dis_cmd cmd
    tint_lang_spirv_writer
    tint_lang_spirv_writer_common
  )
endif(TINT_BUILD_SPV_WRITER)

if(TINT_BUILD_WGSL_WRITER)
  tint_target_add_dependencies(tint_cmd_fuzz_ir_dis_cmd cmd
    tint_lang_wgsl_writer
  )
endif(TINT_BUILD_WGSL_WRITER)

tint_target_set_output_name(tint_cmd_fuzz_ir_dis_cmd cmd "ir_fuzz_dis")

endif(TINT_BUILD_IR_BINARY AND TINT_BUILD_IR_FUZZER AND TINT_BUILD_WGSL_WRITER AND TINT_BUILD_SPV_WRITER)