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

################################################################################
# Target:    tint_lang_core_type
# Kind:      lib
################################################################################
tint_add_target(tint_lang_core_type lib
  lang/core/type/abstract_float.cc
  lang/core/type/abstract_float.h
  lang/core/type/abstract_int.cc
  lang/core/type/abstract_int.h
  lang/core/type/abstract_numeric.cc
  lang/core/type/abstract_numeric.h
  lang/core/type/array.cc
  lang/core/type/array.h
  lang/core/type/array_count.cc
  lang/core/type/array_count.h
  lang/core/type/atomic.cc
  lang/core/type/atomic.h
  lang/core/type/binding_array.cc
  lang/core/type/binding_array.h
  lang/core/type/bool.cc
  lang/core/type/bool.h
  lang/core/type/builtin_structs.cc
  lang/core/type/builtin_structs.h
  lang/core/type/clone_context.h
  lang/core/type/depth_multisampled_texture.cc
  lang/core/type/depth_multisampled_texture.h
  lang/core/type/depth_texture.cc
  lang/core/type/depth_texture.h
  lang/core/type/external_texture.cc
  lang/core/type/external_texture.h
  lang/core/type/f16.cc
  lang/core/type/f16.h
  lang/core/type/f32.cc
  lang/core/type/f32.h
  lang/core/type/function.cc
  lang/core/type/function.h
  lang/core/type/i32.cc
  lang/core/type/i32.h
  lang/core/type/i8.cc
  lang/core/type/i8.h
  lang/core/type/input_attachment.cc
  lang/core/type/input_attachment.h
  lang/core/type/invalid.cc
  lang/core/type/invalid.h
  lang/core/type/manager.cc
  lang/core/type/manager.h
  lang/core/type/matrix.cc
  lang/core/type/matrix.h
  lang/core/type/memory_view.cc
  lang/core/type/memory_view.h
  lang/core/type/multisampled_texture.cc
  lang/core/type/multisampled_texture.h
  lang/core/type/node.cc
  lang/core/type/node.h
  lang/core/type/numeric_scalar.cc
  lang/core/type/numeric_scalar.h
  lang/core/type/pointer.cc
  lang/core/type/pointer.h
  lang/core/type/reference.cc
  lang/core/type/reference.h
  lang/core/type/sampled_texture.cc
  lang/core/type/sampled_texture.h
  lang/core/type/sampler.cc
  lang/core/type/sampler.h
  lang/core/type/sampler_kind.cc
  lang/core/type/sampler_kind.h
  lang/core/type/scalar.cc
  lang/core/type/scalar.h
  lang/core/type/storage_texture.cc
  lang/core/type/storage_texture.h
  lang/core/type/struct.cc
  lang/core/type/struct.h
  lang/core/type/subgroup_matrix.cc
  lang/core/type/subgroup_matrix.h
  lang/core/type/texture.cc
  lang/core/type/texture.h
  lang/core/type/texture_dimension.cc
  lang/core/type/texture_dimension.h
  lang/core/type/type.cc
  lang/core/type/type.h
  lang/core/type/u32.cc
  lang/core/type/u32.h
  lang/core/type/u64.cc
  lang/core/type/u64.h
  lang/core/type/u8.cc
  lang/core/type/u8.h
  lang/core/type/unique_node.cc
  lang/core/type/unique_node.h
  lang/core/type/vector.cc
  lang/core/type/vector.h
  lang/core/type/void.cc
  lang/core/type/void.h
)

tint_target_add_dependencies(tint_lang_core_type lib
  tint_lang_core
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

tint_target_add_external_dependencies(tint_lang_core_type lib
  "src_utils"
)

################################################################################
# Target:    tint_lang_core_type_test
# Kind:      test
################################################################################
tint_add_target(tint_lang_core_type_test test
  lang/core/type/array_test.cc
  lang/core/type/atomic_test.cc
  lang/core/type/binding_array_test.cc
  lang/core/type/bool_test.cc
  lang/core/type/builtin_structs_test.cc
  lang/core/type/depth_multisampled_texture_test.cc
  lang/core/type/depth_texture_test.cc
  lang/core/type/external_texture_test.cc
  lang/core/type/f16_test.cc
  lang/core/type/f32_test.cc
  lang/core/type/helper_test.h
  lang/core/type/i32_test.cc
  lang/core/type/i8_test.cc
  lang/core/type/input_attachment_test.cc
  lang/core/type/manager_test.cc
  lang/core/type/matrix_test.cc
  lang/core/type/multisampled_texture_test.cc
  lang/core/type/pointer_test.cc
  lang/core/type/reference_test.cc
  lang/core/type/sampled_texture_test.cc
  lang/core/type/sampler_test.cc
  lang/core/type/storage_texture_test.cc
  lang/core/type/struct_test.cc
  lang/core/type/subgroup_matrix_test.cc
  lang/core/type/texture_test.cc
  lang/core/type/type_test.cc
  lang/core/type/u32_test.cc
  lang/core/type/u64_test.cc
  lang/core/type/u8_test.cc
  lang/core/type/vector_test.cc
)

tint_target_add_dependencies(tint_lang_core_type_test test
  tint_api_common
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_type
  tint_lang_wgsl
  tint_lang_wgsl_ast
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

tint_target_add_external_dependencies(tint_lang_core_type_test test
  "gtest"
  "src_utils"
)
