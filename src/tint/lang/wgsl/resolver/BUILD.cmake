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
# Target:    tint_lang_wgsl_resolver
# Kind:      lib
################################################################################
tint_add_target(tint_lang_wgsl_resolver lib
  lang/wgsl/resolver/dependency_graph.cc
  lang/wgsl/resolver/dependency_graph.h
  lang/wgsl/resolver/incomplete_type.cc
  lang/wgsl/resolver/incomplete_type.h
  lang/wgsl/resolver/resolve.cc
  lang/wgsl/resolver/resolve.h
  lang/wgsl/resolver/resolver.cc
  lang/wgsl/resolver/resolver.h
  lang/wgsl/resolver/sem_helper.cc
  lang/wgsl/resolver/sem_helper.h
  lang/wgsl/resolver/uniformity.cc
  lang/wgsl/resolver/uniformity.h
  lang/wgsl/resolver/unresolved_identifier.cc
  lang/wgsl/resolver/unresolved_identifier.h
  lang/wgsl/resolver/validator.cc
  lang/wgsl/resolver/validator.h
)

tint_target_add_dependencies(tint_lang_wgsl_resolver lib
  tint_api_common
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_intrinsic
  tint_lang_core_type
  tint_lang_wgsl
  tint_lang_wgsl_ast
  tint_lang_wgsl_common
  tint_lang_wgsl_features
  tint_lang_wgsl_intrinsic
  tint_lang_wgsl_program
  tint_lang_wgsl_sem
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
  tint_utils_symbol
  tint_utils_text
  tint_utils_traits
)

################################################################################
# Target:    tint_lang_wgsl_resolver_test
# Kind:      test
################################################################################
tint_add_target(tint_lang_wgsl_resolver_test test
  lang/wgsl/resolver/address_space_layout_validation_test.cc
  lang/wgsl/resolver/address_space_validation_test.cc
  lang/wgsl/resolver/alias_analysis_test.cc
  lang/wgsl/resolver/array_accessor_test.cc
  lang/wgsl/resolver/assignment_validation_test.cc
  lang/wgsl/resolver/atomics_test.cc
  lang/wgsl/resolver/atomics_validation_test.cc
  lang/wgsl/resolver/attribute_validation_test.cc
  lang/wgsl/resolver/bitcast_validation_test.cc
  lang/wgsl/resolver/builtin_enum_test.cc
  lang/wgsl/resolver/builtin_structs_test.cc
  lang/wgsl/resolver/builtin_test.cc
  lang/wgsl/resolver/builtin_validation_test.cc
  lang/wgsl/resolver/builtins_validation_test.cc
  lang/wgsl/resolver/call_test.cc
  lang/wgsl/resolver/call_validation_test.cc
  lang/wgsl/resolver/compound_assignment_validation_test.cc
  lang/wgsl/resolver/compound_statement_test.cc
  lang/wgsl/resolver/const_assert_test.cc
  lang/wgsl/resolver/control_block_validation_test.cc
  lang/wgsl/resolver/dependency_graph_test.cc
  lang/wgsl/resolver/diagnostic_control_test.cc
  lang/wgsl/resolver/dual_source_blending_extension_test.cc
  lang/wgsl/resolver/entry_point_validation_test.cc
  lang/wgsl/resolver/evaluation_stage_test.cc
  lang/wgsl/resolver/expression_kind_test.cc
  lang/wgsl/resolver/f16_extension_test.cc
  lang/wgsl/resolver/framebuffer_fetch_extension_test.cc
  lang/wgsl/resolver/function_validation_test.cc
  lang/wgsl/resolver/graphite_extension_test.cc
  lang/wgsl/resolver/host_shareable_validation_test.cc
  lang/wgsl/resolver/increment_decrement_validation_test.cc
  lang/wgsl/resolver/inferred_type_test.cc
  lang/wgsl/resolver/input_attachments_extension_test.cc
  lang/wgsl/resolver/is_host_shareable_test.cc
  lang/wgsl/resolver/is_storeable_test.cc
  lang/wgsl/resolver/language_features_test.cc
  lang/wgsl/resolver/load_test.cc
  lang/wgsl/resolver/materialize_test.cc
  lang/wgsl/resolver/override_test.cc
  lang/wgsl/resolver/pixel_local_extension_test.cc
  lang/wgsl/resolver/ptr_ref_test.cc
  lang/wgsl/resolver/ptr_ref_validation_test.cc
  lang/wgsl/resolver/resolver_behavior_test.cc
  lang/wgsl/resolver/resolver_helper_test.cc
  lang/wgsl/resolver/resolver_helper_test.h
  lang/wgsl/resolver/resolver_test.cc
  lang/wgsl/resolver/root_identifier_test.cc
  lang/wgsl/resolver/side_effects_test.cc
  lang/wgsl/resolver/struct_address_space_use_test.cc
  lang/wgsl/resolver/struct_layout_test.cc
  lang/wgsl/resolver/struct_pipeline_stage_use_test.cc
  lang/wgsl/resolver/subgroups_extension_test.cc
  lang/wgsl/resolver/type_validation_test.cc
  lang/wgsl/resolver/unresolved_identifier_test.cc
  lang/wgsl/resolver/validation_test.cc
  lang/wgsl/resolver/validator_is_storeable_test.cc
  lang/wgsl/resolver/value_constructor_validation_test.cc
  lang/wgsl/resolver/variable_test.cc
  lang/wgsl/resolver/variable_validation_test.cc
)

tint_target_add_dependencies(tint_lang_wgsl_resolver_test test
  tint_api_common
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_intrinsic
  tint_lang_core_ir
  tint_lang_core_type
  tint_lang_core_type_test
  tint_lang_wgsl
  tint_lang_wgsl_ast
  tint_lang_wgsl_ast_transform
  tint_lang_wgsl_ast_test
  tint_lang_wgsl_common
  tint_lang_wgsl_features
  tint_lang_wgsl_intrinsic
  tint_lang_wgsl_program
  tint_lang_wgsl_resolver
  tint_lang_wgsl_sem
  tint_lang_wgsl_sem_test
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
  tint_utils_symbol
  tint_utils_text
  tint_utils_traits
)

tint_target_add_external_dependencies(tint_lang_wgsl_resolver_test test
  "gtest"
)

if(TINT_BUILD_WGSL_READER)
  tint_target_add_sources(tint_lang_wgsl_resolver_test test
    "lang/wgsl/resolver/uniformity_test.cc"
  )
  tint_target_add_dependencies(tint_lang_wgsl_resolver_test test
    tint_lang_wgsl_reader
  )
endif(TINT_BUILD_WGSL_READER)
