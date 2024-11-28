#version 310 es
precision highp float;
precision highp int;

layout(binding = 0, std430)
buffer prevent_dce_block_1_ssbo {
  ivec4 inner;
} v;
ivec4 min_3941e1() {
  ivec4 arg_0 = ivec4(1);
  ivec4 arg_1 = ivec4(1);
  ivec4 res = min(arg_0, arg_1);
  return res;
}
void main() {
  v.inner = min_3941e1();
}
#version 310 es

layout(binding = 0, std430)
buffer prevent_dce_block_1_ssbo {
  ivec4 inner;
} v;
ivec4 min_3941e1() {
  ivec4 arg_0 = ivec4(1);
  ivec4 arg_1 = ivec4(1);
  ivec4 res = min(arg_0, arg_1);
  return res;
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  v.inner = min_3941e1();
}
#version 310 es


struct VertexOutput {
  vec4 pos;
  ivec4 prevent_dce;
};

layout(location = 0) flat out ivec4 vertex_main_loc0_Output;
ivec4 min_3941e1() {
  ivec4 arg_0 = ivec4(1);
  ivec4 arg_1 = ivec4(1);
  ivec4 res = min(arg_0, arg_1);
  return res;
}
VertexOutput vertex_main_inner() {
  VertexOutput tint_symbol = VertexOutput(vec4(0.0f), ivec4(0));
  tint_symbol.pos = vec4(0.0f);
  tint_symbol.prevent_dce = min_3941e1();
  return tint_symbol;
}
void main() {
  VertexOutput v = vertex_main_inner();
  gl_Position = v.pos;
  gl_Position.y = -(gl_Position.y);
  gl_Position.z = ((2.0f * gl_Position.z) - gl_Position.w);
  vertex_main_loc0_Output = v.prevent_dce;
  gl_PointSize = 1.0f;
}
