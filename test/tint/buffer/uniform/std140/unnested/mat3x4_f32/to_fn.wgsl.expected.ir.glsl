#version 310 es

uniform mat3x4 u;
void a(mat3x4 m) {
}
void b(vec4 v) {
}
void c(float f) {
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  a(u);
  b(u[1]);
  b(u[1].ywxz);
  c(u[1].x);
  c(u[1].ywxz[0u]);
}
