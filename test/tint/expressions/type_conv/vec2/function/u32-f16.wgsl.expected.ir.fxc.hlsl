SKIP: INVALID


static uint t = 0u;
uint2 m() {
  t = 1u;
  return uint2((t).xx);
}

void f() {
  vector<float16_t, 2> v = vector<float16_t, 2>(m());
}

[numthreads(1, 1, 1)]
void unused_entry_point() {
}

FXC validation failure:
C:\src\dawn\Shader@0x000002A83A851050(9,10-18): error X3000: syntax error: unexpected token 'float16_t'

