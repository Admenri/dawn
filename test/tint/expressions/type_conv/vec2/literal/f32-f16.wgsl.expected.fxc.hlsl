SKIP: FAILED

[numthreads(1, 1, 1)]
void unused_entry_point() {
  return;
}

static vector<float16_t, 2> u = (float16_t(1.0h)).xx;
FXC validation failure:
C:\src\dawn\Shader@0x000001AE1A3F5E80(6,15-23): error X3000: syntax error: unexpected token 'float16_t'

