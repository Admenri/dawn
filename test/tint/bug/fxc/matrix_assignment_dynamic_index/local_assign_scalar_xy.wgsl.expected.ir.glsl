#version 310 es

struct Uniforms {
  uint i;
  uint j;
};

uniform Uniforms uniforms;
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  mat2x4 m1 = mat2x4(vec4(0.0f), vec4(0.0f));
  m1[uniforms.i][uniforms.j] = 1.0f;
}
