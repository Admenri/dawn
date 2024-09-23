#version 310 es

ivec3 tint_div_v3i32(ivec3 lhs, ivec3 rhs) {
  bvec3 v = equal(rhs, ivec3(0));
  bvec3 v_1 = equal(lhs, ivec3((-2147483647 - 1)));
  bvec3 v_2 = equal(rhs, ivec3(-1));
  uvec3 v_3 = uvec3(v_1);
  bvec3 v_4 = bvec3((v_3 & uvec3(v_2)));
  uvec3 v_5 = uvec3(v);
  bvec3 v_6 = bvec3((v_5 | uvec3(v_4)));
  int v_7 = ((v_6.x) ? (ivec3(1).x) : (rhs.x));
  int v_8 = ((v_6.y) ? (ivec3(1).y) : (rhs.y));
  return (lhs / ivec3(v_7, v_8, ((v_6.z) ? (ivec3(1).z) : (rhs.z))));
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  ivec3 a = ivec3(1, 2, 3);
  int b = 4;
  ivec3 r = tint_div_v3i32(a, ivec3(b));
}
