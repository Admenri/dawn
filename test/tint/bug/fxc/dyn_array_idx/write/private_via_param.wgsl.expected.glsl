#version 310 es

layout(binding = 0) uniform UBO_ubo {
  int dynamic_idx;
} ubo;

struct S {
  int data[64];
};

layout(binding = 1, std430) buffer Result_ssbo {
  int tint_symbol;
} result;

S s = S(int[64](0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
void x(inout S p) {
  p.data[ubo.dynamic_idx] = 1;
}

void f() {
  x(s);
  result.tint_symbol = s.data[3];
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  f();
  return;
}
