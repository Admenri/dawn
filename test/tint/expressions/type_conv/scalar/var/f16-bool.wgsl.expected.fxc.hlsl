SKIP: FAILED

[numthreads(1, 1, 1)]
void unused_entry_point() {
  return;
}

static float16_t u = float16_t(1.0h);

void f() {
  bool v = bool(u);
}
FXC validation failure:
C:\src\dawn\Shader@0x0000029A3F2B87B0(6,8-16): error X3000: unrecognized identifier 'float16_t'

