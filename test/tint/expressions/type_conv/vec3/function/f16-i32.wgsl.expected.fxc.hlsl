SKIP: FAILED

[numthreads(1, 1, 1)]
void unused_entry_point() {
  return;
}

static float16_t t = float16_t(0.0h);

vector<float16_t, 3> m() {
  t = float16_t(1.0h);
  return vector<float16_t, 3>((t).xxx);
}

void f() {
  vector<float16_t, 3> tint_symbol = m();
  int3 v = int3(tint_symbol);
}
FXC validation failure:
C:\src\dawn\Shader@0x000001F7CBACFCE0(6,8-16): error X3000: unrecognized identifier 'float16_t'

