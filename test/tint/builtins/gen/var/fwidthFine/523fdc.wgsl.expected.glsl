#version 310 es
precision highp float;
precision highp int;

layout(binding = 0, std430) buffer prevent_dce_block_ssbo {
  vec3 inner;
  uint pad;
} prevent_dce;

void fwidthFine_523fdc() {
  vec3 arg_0 = vec3(1.0f);
  vec3 res = fwidth(arg_0);
  prevent_dce.inner = res;
}

void fragment_main() {
  fwidthFine_523fdc();
}

void main() {
  fragment_main();
  return;
}
