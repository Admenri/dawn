#version 310 es

layout(binding = 0) uniform u_block_ubo {
  mat3x2 inner;
} u;

void tint_symbol() {
  mat3x2 x = u.inner;
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  tint_symbol();
  return;
}
