#version 310 es
#extension GL_AMD_gpu_shader_half_float: require

uniform f16mat2 u;
void a(f16mat2 m) {
}
void b(f16vec2 v) {
}
void c(float16_t f) {
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  a(u);
  b(u[1]);
  b(u[1].yx);
  c(u[1].x);
  c(u[1].yx[0u]);
}
