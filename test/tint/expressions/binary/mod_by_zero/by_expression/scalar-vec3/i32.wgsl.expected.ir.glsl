#version 310 es

ivec3 tint_mod_v3i32(ivec3 lhs, ivec3 rhs) {
  bvec3 v = equal(rhs, ivec3(0));
  bvec3 v_1 = equal(lhs, ivec3((-2147483647 - 1)));
  bvec3 v_2 = equal(rhs, ivec3(-1));
  uvec3 v_3 = uvec3(v_1);
  bvec3 v_4 = bvec3((v_3 & uvec3(v_2)));
  uvec3 v_5 = uvec3(v);
  bvec3 v_6 = bvec3((v_5 | uvec3(v_4)));
  int v_7 = ((v_6.x) ? (ivec3(1).x) : (rhs.x));
  int v_8 = ((v_6.y) ? (ivec3(1).y) : (rhs.y));
  ivec3 v_9 = ivec3(v_7, v_8, ((v_6.z) ? (ivec3(1).z) : (rhs.z)));
  return (lhs - ((lhs / v_9) * v_9));
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  int a = 4;
  ivec3 b = ivec3(0, 2, 0);
  ivec3 v_10 = (b + b);
  ivec3 r = tint_mod_v3i32(ivec3(a), v_10);
}
