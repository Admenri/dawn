SKIP: FAILED

[numthreads(1, 1, 1)]
void unused_entry_point() {
  return;
}

static float4 u = (1.0f).xxxx;

void f() {
  vector<float16_t, 4> v = vector<float16_t, 4>(u);
}
FXC validation failure:
C:\src\dawn\Shader@0x000001FEEC6F4940(9,10-18): error X3000: syntax error: unexpected token 'float16_t'

