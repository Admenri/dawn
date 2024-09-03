#version 310 es

uniform mat2 u;
mat2 p = mat2(vec2(0.0f), vec2(0.0f));
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  p = u;
  p[1] = u[0];
  p[1] = u[0].yx;
  p[0][1] = u[1].x;
}
