#version 310 es


struct S {
  int before;
  uint tint_pad_0;
  uint tint_pad_1;
  uint tint_pad_2;
  mat3x4 m;
  int after;
  uint tint_pad_3;
  uint tint_pad_4;
  uint tint_pad_5;
  uint tint_pad_6;
  uint tint_pad_7;
  uint tint_pad_8;
  uint tint_pad_9;
  uint tint_pad_10;
  uint tint_pad_11;
  uint tint_pad_12;
  uint tint_pad_13;
  uint tint_pad_14;
  uint tint_pad_15;
  uint tint_pad_16;
  uint tint_pad_17;
};

layout(binding = 0, std140)
uniform u_block_1_ubo {
  S inner[4];
} v_1;
void a(S a_1[4]) {
}
void b(S s) {
}
void c(mat3x4 m) {
}
void d(vec4 v) {
}
void e(float f_1) {
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  a(v_1.inner);
  b(v_1.inner[2u]);
  c(v_1.inner[2u].m);
  d(v_1.inner[0u].m[1u].ywxz);
  e(v_1.inner[0u].m[1u].ywxz.x);
}
