#version 310 es
precision highp float;
precision highp int;

void sinh_a3da7c() {
  vec4 res = vec4(1.17520117759704589844f);
}
void main() {
  sinh_a3da7c();
}
#version 310 es

void sinh_a3da7c() {
  vec4 res = vec4(1.17520117759704589844f);
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  sinh_a3da7c();
}
#version 310 es


struct VertexOutput {
  vec4 pos;
};

void sinh_a3da7c() {
  vec4 res = vec4(1.17520117759704589844f);
}
VertexOutput vertex_main_inner() {
  VertexOutput tint_symbol = VertexOutput(vec4(0.0f));
  tint_symbol.pos = vec4(0.0f);
  sinh_a3da7c();
  return tint_symbol;
}
void main() {
  gl_Position = vertex_main_inner().pos;
  gl_Position.y = -(gl_Position.y);
  gl_Position.z = ((2.0f * gl_Position.z) - gl_Position.w);
  gl_PointSize = 1.0f;
}
