SKIP: INVALID


RWByteAddressBuffer tint_symbol : register(u0);
void v(uint offset, matrix<float16_t, 3, 4> obj) {
  tint_symbol.Store<vector<float16_t, 4> >((offset + 0u), obj[0u]);
  tint_symbol.Store<vector<float16_t, 4> >((offset + 8u), obj[1u]);
  tint_symbol.Store<vector<float16_t, 4> >((offset + 16u), obj[2u]);
}

[numthreads(1, 1, 1)]
void f() {
  matrix<float16_t, 3, 4> m = matrix<float16_t, 3, 4>((float16_t(0.0h)).xxxx, (float16_t(0.0h)).xxxx, (float16_t(0.0h)).xxxx);
  v(0u, matrix<float16_t, 3, 4>(m));
}

FXC validation failure:
C:\src\dawn\Shader@0x000002D0CE96C140(3,28-36): error X3000: syntax error: unexpected token 'float16_t'
C:\src\dawn\Shader@0x000002D0CE96C140(4,3-19): error X3018: invalid subscript 'Store'

