SKIP: INVALID


static float4 u = (1.0f).xxxx;
void f() {
  vector<float16_t, 4> v = vector<float16_t, 4>(u);
}

[numthreads(1, 1, 1)]
void unused_entry_point() {
}

FXC validation failure:
C:\src\dawn\Shader@0x000001E2003D6890(4,10-18): error X3000: syntax error: unexpected token 'float16_t'

