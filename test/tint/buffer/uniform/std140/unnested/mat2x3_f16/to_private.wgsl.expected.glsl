#version 310 es
#extension GL_AMD_gpu_shader_half_float: require

layout(binding = 0, std140)
uniform u_block_std140_1_ubo {
  f16vec3 inner_col0;
  f16vec3 inner_col1;
} v;
f16mat2x3 p = f16mat2x3(f16vec3(0.0hf), f16vec3(0.0hf));
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  p = f16mat2x3(v.inner_col0, v.inner_col1);
  p[1u] = f16mat2x3(v.inner_col0, v.inner_col1)[0u];
  p[1u] = f16mat2x3(v.inner_col0, v.inner_col1)[0u].zxy;
  p[0u].y = f16mat2x3(v.inner_col0, v.inner_col1)[1u].x;
}
