#version 310 es

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void unused_entry_point() {
  return;
}
layout(binding = 0, std430) buffer S_ssbo {
  mat2 m;
} SSBO;

layout(binding = 0) uniform S_std140_ubo {
  vec2 m_0;
  vec2 m_1;
} UBO;

