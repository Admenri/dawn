SKIP: FAILED

[numthreads(1, 1, 1)]
void unused_entry_point() {
  return;
}

void f() {
  matrix<float16_t, 2, 3> v = matrix<float16_t, 2, 3>((float16_t(0.0h)).xxx, (float16_t(0.0h)).xxx);
}
FXC validation failure:
C:\src\dawn\Shader@0x000002959E451A00(7,10-18): error X3000: syntax error: unexpected token 'float16_t'

