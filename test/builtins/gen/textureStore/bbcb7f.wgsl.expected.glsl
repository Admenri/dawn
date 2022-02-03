#version 310 es
precision mediump float;

layout(rgba8i) uniform highp writeonly iimage2D arg_0;
void textureStore_bbcb7f() {
  imageStore(arg_0, ivec2(0, 0), ivec4(0, 0, 0, 0));
}

vec4 vertex_main() {
  textureStore_bbcb7f();
  return vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

void main() {
  vec4 inner_result = vertex_main();
  gl_Position = inner_result;
  gl_Position.y = -(gl_Position.y);
  gl_Position.z = ((2.0f * gl_Position.z) - gl_Position.w);
  return;
}
#version 310 es
precision mediump float;

layout(rgba8i) uniform highp writeonly iimage2D arg_0;
void textureStore_bbcb7f() {
  imageStore(arg_0, ivec2(0, 0), ivec4(0, 0, 0, 0));
}

void fragment_main() {
  textureStore_bbcb7f();
}

void main() {
  fragment_main();
  return;
}
#version 310 es
precision mediump float;

layout(rgba8i) uniform highp writeonly iimage2D arg_0;
void textureStore_bbcb7f() {
  imageStore(arg_0, ivec2(0, 0), ivec4(0, 0, 0, 0));
}

void compute_main() {
  textureStore_bbcb7f();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
