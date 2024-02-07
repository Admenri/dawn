#version 310 es

ivec4 tint_unpack_4xi8(uint a) {
  uvec4 a_vec4u = uvec4(a);
  ivec4 a_vec4i = ivec4((a_vec4u << uvec4(24u, 16u, 8u, 0u)));
  return (a_vec4i >> uvec4(24u));
}

layout(binding = 0, std430) buffer prevent_dce_block_ssbo {
  ivec4 inner;
} prevent_dce;

void unpack4xI8_830900() {
  uint arg_0 = 1u;
  ivec4 res = tint_unpack_4xi8(arg_0);
  prevent_dce.inner = res;
}

vec4 vertex_main() {
  unpack4xI8_830900();
  return vec4(0.0f);
}

void main() {
  gl_PointSize = 1.0;
  vec4 inner_result = vertex_main();
  gl_Position = inner_result;
  gl_Position.y = -(gl_Position.y);
  gl_Position.z = ((2.0f * gl_Position.z) - gl_Position.w);
  return;
}
#version 310 es
precision highp float;
precision highp int;

ivec4 tint_unpack_4xi8(uint a) {
  uvec4 a_vec4u = uvec4(a);
  ivec4 a_vec4i = ivec4((a_vec4u << uvec4(24u, 16u, 8u, 0u)));
  return (a_vec4i >> uvec4(24u));
}

layout(binding = 0, std430) buffer prevent_dce_block_ssbo {
  ivec4 inner;
} prevent_dce;

void unpack4xI8_830900() {
  uint arg_0 = 1u;
  ivec4 res = tint_unpack_4xi8(arg_0);
  prevent_dce.inner = res;
}

void fragment_main() {
  unpack4xI8_830900();
}

void main() {
  fragment_main();
  return;
}
#version 310 es

ivec4 tint_unpack_4xi8(uint a) {
  uvec4 a_vec4u = uvec4(a);
  ivec4 a_vec4i = ivec4((a_vec4u << uvec4(24u, 16u, 8u, 0u)));
  return (a_vec4i >> uvec4(24u));
}

layout(binding = 0, std430) buffer prevent_dce_block_ssbo {
  ivec4 inner;
} prevent_dce;

void unpack4xI8_830900() {
  uint arg_0 = 1u;
  ivec4 res = tint_unpack_4xi8(arg_0);
  prevent_dce.inner = res;
}

void compute_main() {
  unpack4xI8_830900();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
