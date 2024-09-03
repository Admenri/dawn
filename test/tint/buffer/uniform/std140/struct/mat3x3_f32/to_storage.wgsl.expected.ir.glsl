#version 310 es

struct S {
  int before;
  mat3 m;
  int after;
};

uniform S u[4];
S s[4];
void tint_store_and_preserve_padding_2(inout mat3 target, mat3 value_param) {
  target[0u] = value_param[0u];
  target[1u] = value_param[1u];
  target[2u] = value_param[2u];
}
void tint_store_and_preserve_padding_1(inout S target, S value_param) {
  target.before = value_param.before;
  tint_store_and_preserve_padding_2(target.m, value_param.m);
  target.after = value_param.after;
}
void tint_store_and_preserve_padding(inout S target[4], S value_param[4]) {
  {
    uint v = 0u;
    v = 0u;
    while(true) {
      uint v_1 = v;
      if ((v_1 >= 4u)) {
        break;
      }
      tint_store_and_preserve_padding_1(target[v_1], value_param[v_1]);
      {
        v = (v_1 + 1u);
      }
      continue;
    }
  }
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  tint_store_and_preserve_padding(s, u);
  tint_store_and_preserve_padding_1(s[1], u[2]);
  tint_store_and_preserve_padding_2(s[3].m, u[2].m);
  s[1].m[0] = u[0].m[1].zxy;
}
