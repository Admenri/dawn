#version 310 es
precision highp float;
precision highp int;

layout(binding = 0, std430)
buffer f_prevent_dce_block_ssbo {
  float inner;
} v;
float dpdy_7f8d84() {
  float res = dFdy(1.0f);
  return res;
}
void main() {
  v.inner = dpdy_7f8d84();
}
