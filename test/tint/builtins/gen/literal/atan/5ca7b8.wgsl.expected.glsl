#version 310 es
precision highp float;
precision highp int;

void atan_5ca7b8() {
  vec2 res = vec2(0.78539818525314331055f);
}
void main() {
  atan_5ca7b8();
}
#version 310 es

void atan_5ca7b8() {
  vec2 res = vec2(0.78539818525314331055f);
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  atan_5ca7b8();
}
#version 310 es


struct VertexOutput {
  vec4 pos;
};

void atan_5ca7b8() {
  vec2 res = vec2(0.78539818525314331055f);
}
VertexOutput vertex_main_inner() {
  VertexOutput tint_symbol = VertexOutput(vec4(0.0f));
  tint_symbol.pos = vec4(0.0f);
  atan_5ca7b8();
  return tint_symbol;
}
void main() {
  gl_Position = vertex_main_inner().pos;
  gl_Position.y = -(gl_Position.y);
  gl_Position.z = ((2.0f * gl_Position.z) - gl_Position.w);
  gl_PointSize = 1.0f;
}
