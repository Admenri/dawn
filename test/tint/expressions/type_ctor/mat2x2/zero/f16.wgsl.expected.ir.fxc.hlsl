SKIP: INVALID


static matrix<float16_t, 2, 2> m = matrix<float16_t, 2, 2>((float16_t(0.0h)).xx, (float16_t(0.0h)).xx);
RWByteAddressBuffer tint_symbol : register(u0);
void v(uint offset, matrix<float16_t, 2, 2> obj) {
  tint_symbol.Store<vector<float16_t, 2> >((offset + 0u), obj[0u]);
  tint_symbol.Store<vector<float16_t, 2> >((offset + 4u), obj[1u]);
}

[numthreads(1, 1, 1)]
void f() {
  v(0u, m);
}

FXC validation failure:
C:\src\dawn\Shader@0x000001A7776DFFE0(2,15-23): error X3000: syntax error: unexpected token 'float16_t'

