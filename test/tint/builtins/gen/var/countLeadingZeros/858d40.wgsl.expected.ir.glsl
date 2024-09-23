#version 310 es
precision highp float;
precision highp int;

layout(binding = 0, std430)
buffer tint_symbol_1_1_ssbo {
  ivec2 tint_symbol;
} v;
ivec2 countLeadingZeros_858d40() {
  ivec2 arg_0 = ivec2(1);
  uvec2 v_1 = uvec2(arg_0);
  bvec2 v_2 = lessThanEqual(v_1, uvec2(65535u));
  uint v_3 = ((v_2.x) ? (uvec2(16u).x) : (uvec2(0u).x));
  uvec2 v_4 = uvec2(v_3, ((v_2.y) ? (uvec2(16u).y) : (uvec2(0u).y)));
  bvec2 v_5 = lessThanEqual((v_1 << v_4), uvec2(16777215u));
  uint v_6 = ((v_5.x) ? (uvec2(8u).x) : (uvec2(0u).x));
  uvec2 v_7 = uvec2(v_6, ((v_5.y) ? (uvec2(8u).y) : (uvec2(0u).y)));
  bvec2 v_8 = lessThanEqual(((v_1 << v_4) << v_7), uvec2(268435455u));
  uint v_9 = ((v_8.x) ? (uvec2(4u).x) : (uvec2(0u).x));
  uvec2 v_10 = uvec2(v_9, ((v_8.y) ? (uvec2(4u).y) : (uvec2(0u).y)));
  bvec2 v_11 = lessThanEqual((((v_1 << v_4) << v_7) << v_10), uvec2(1073741823u));
  uint v_12 = ((v_11.x) ? (uvec2(2u).x) : (uvec2(0u).x));
  uvec2 v_13 = uvec2(v_12, ((v_11.y) ? (uvec2(2u).y) : (uvec2(0u).y)));
  bvec2 v_14 = lessThanEqual(((((v_1 << v_4) << v_7) << v_10) << v_13), uvec2(2147483647u));
  uint v_15 = ((v_14.x) ? (uvec2(1u).x) : (uvec2(0u).x));
  uvec2 v_16 = uvec2(v_15, ((v_14.y) ? (uvec2(1u).y) : (uvec2(0u).y)));
  bvec2 v_17 = equal(((((v_1 << v_4) << v_7) << v_10) << v_13), uvec2(0u));
  uint v_18 = ((v_17.x) ? (uvec2(1u).x) : (uvec2(0u).x));
  uvec2 v_19 = uvec2(v_18, ((v_17.y) ? (uvec2(1u).y) : (uvec2(0u).y)));
  ivec2 res = ivec2(((v_4 | (v_7 | (v_10 | (v_13 | (v_16 | v_19))))) + v_19));
  return res;
}
void main() {
  v.tint_symbol = countLeadingZeros_858d40();
}
#version 310 es

layout(binding = 0, std430)
buffer tint_symbol_1_1_ssbo {
  ivec2 tint_symbol;
} v;
ivec2 countLeadingZeros_858d40() {
  ivec2 arg_0 = ivec2(1);
  uvec2 v_1 = uvec2(arg_0);
  bvec2 v_2 = lessThanEqual(v_1, uvec2(65535u));
  uint v_3 = ((v_2.x) ? (uvec2(16u).x) : (uvec2(0u).x));
  uvec2 v_4 = uvec2(v_3, ((v_2.y) ? (uvec2(16u).y) : (uvec2(0u).y)));
  bvec2 v_5 = lessThanEqual((v_1 << v_4), uvec2(16777215u));
  uint v_6 = ((v_5.x) ? (uvec2(8u).x) : (uvec2(0u).x));
  uvec2 v_7 = uvec2(v_6, ((v_5.y) ? (uvec2(8u).y) : (uvec2(0u).y)));
  bvec2 v_8 = lessThanEqual(((v_1 << v_4) << v_7), uvec2(268435455u));
  uint v_9 = ((v_8.x) ? (uvec2(4u).x) : (uvec2(0u).x));
  uvec2 v_10 = uvec2(v_9, ((v_8.y) ? (uvec2(4u).y) : (uvec2(0u).y)));
  bvec2 v_11 = lessThanEqual((((v_1 << v_4) << v_7) << v_10), uvec2(1073741823u));
  uint v_12 = ((v_11.x) ? (uvec2(2u).x) : (uvec2(0u).x));
  uvec2 v_13 = uvec2(v_12, ((v_11.y) ? (uvec2(2u).y) : (uvec2(0u).y)));
  bvec2 v_14 = lessThanEqual(((((v_1 << v_4) << v_7) << v_10) << v_13), uvec2(2147483647u));
  uint v_15 = ((v_14.x) ? (uvec2(1u).x) : (uvec2(0u).x));
  uvec2 v_16 = uvec2(v_15, ((v_14.y) ? (uvec2(1u).y) : (uvec2(0u).y)));
  bvec2 v_17 = equal(((((v_1 << v_4) << v_7) << v_10) << v_13), uvec2(0u));
  uint v_18 = ((v_17.x) ? (uvec2(1u).x) : (uvec2(0u).x));
  uvec2 v_19 = uvec2(v_18, ((v_17.y) ? (uvec2(1u).y) : (uvec2(0u).y)));
  ivec2 res = ivec2(((v_4 | (v_7 | (v_10 | (v_13 | (v_16 | v_19))))) + v_19));
  return res;
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  v.tint_symbol = countLeadingZeros_858d40();
}
#version 310 es


struct VertexOutput {
  vec4 pos;
  ivec2 prevent_dce;
};

layout(location = 0) flat out ivec2 vertex_main_loc0_Output;
ivec2 countLeadingZeros_858d40() {
  ivec2 arg_0 = ivec2(1);
  uvec2 v = uvec2(arg_0);
  bvec2 v_1 = lessThanEqual(v, uvec2(65535u));
  uint v_2 = ((v_1.x) ? (uvec2(16u).x) : (uvec2(0u).x));
  uvec2 v_3 = uvec2(v_2, ((v_1.y) ? (uvec2(16u).y) : (uvec2(0u).y)));
  bvec2 v_4 = lessThanEqual((v << v_3), uvec2(16777215u));
  uint v_5 = ((v_4.x) ? (uvec2(8u).x) : (uvec2(0u).x));
  uvec2 v_6 = uvec2(v_5, ((v_4.y) ? (uvec2(8u).y) : (uvec2(0u).y)));
  bvec2 v_7 = lessThanEqual(((v << v_3) << v_6), uvec2(268435455u));
  uint v_8 = ((v_7.x) ? (uvec2(4u).x) : (uvec2(0u).x));
  uvec2 v_9 = uvec2(v_8, ((v_7.y) ? (uvec2(4u).y) : (uvec2(0u).y)));
  bvec2 v_10 = lessThanEqual((((v << v_3) << v_6) << v_9), uvec2(1073741823u));
  uint v_11 = ((v_10.x) ? (uvec2(2u).x) : (uvec2(0u).x));
  uvec2 v_12 = uvec2(v_11, ((v_10.y) ? (uvec2(2u).y) : (uvec2(0u).y)));
  bvec2 v_13 = lessThanEqual(((((v << v_3) << v_6) << v_9) << v_12), uvec2(2147483647u));
  uint v_14 = ((v_13.x) ? (uvec2(1u).x) : (uvec2(0u).x));
  uvec2 v_15 = uvec2(v_14, ((v_13.y) ? (uvec2(1u).y) : (uvec2(0u).y)));
  bvec2 v_16 = equal(((((v << v_3) << v_6) << v_9) << v_12), uvec2(0u));
  uint v_17 = ((v_16.x) ? (uvec2(1u).x) : (uvec2(0u).x));
  uvec2 v_18 = uvec2(v_17, ((v_16.y) ? (uvec2(1u).y) : (uvec2(0u).y)));
  ivec2 res = ivec2(((v_3 | (v_6 | (v_9 | (v_12 | (v_15 | v_18))))) + v_18));
  return res;
}
VertexOutput vertex_main_inner() {
  VertexOutput tint_symbol = VertexOutput(vec4(0.0f), ivec2(0));
  tint_symbol.pos = vec4(0.0f);
  tint_symbol.prevent_dce = countLeadingZeros_858d40();
  return tint_symbol;
}
void main() {
  VertexOutput v_19 = vertex_main_inner();
  gl_Position = v_19.pos;
  gl_Position[1u] = -(gl_Position.y);
  gl_Position[2u] = ((2.0f * gl_Position.z) - gl_Position.w);
  vertex_main_loc0_Output = v_19.prevent_dce;
  gl_PointSize = 1.0f;
}
