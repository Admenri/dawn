#version 310 es

struct S {
  int before;
  mat2x4 m;
  int after;
};

uniform S u[4];
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  mat4x2 t = transpose(u[2].m);
  float l = length(u[0].m[1].ywxz);
  float a = abs(u[0].m[1].ywxz[0u]);
}
