#version 310 es
precision highp float;
precision highp int;

void atanh_e431bb() {
  vec4 res = vec4(0.54930615425109863281f);
}
void main() {
  atanh_e431bb();
}
#version 310 es

void atanh_e431bb() {
  vec4 res = vec4(0.54930615425109863281f);
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  atanh_e431bb();
}
#version 310 es


struct VertexOutput {
  vec4 pos;
};

void atanh_e431bb() {
  vec4 res = vec4(0.54930615425109863281f);
}
VertexOutput vertex_main_inner() {
  VertexOutput tint_symbol = VertexOutput(vec4(0.0f));
  tint_symbol.pos = vec4(0.0f);
  atanh_e431bb();
  return tint_symbol;
}
void main() {
  gl_Position = vertex_main_inner().pos;
  gl_Position.y = -(gl_Position.y);
  gl_Position.z = ((2.0f * gl_Position.z) - gl_Position.w);
  gl_PointSize = 1.0f;
}
