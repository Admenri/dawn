SKIP: FAILED


ByteAddressBuffer tint_symbol : register(t0);
RWByteAddressBuffer tint_symbol_1 : register(u1);
[numthreads(1, 1, 1)]
void main() {
  tint_symbol_1.Store<vector<float16_t, 2> >(0u, tint_symbol.Load<vector<float16_t, 2> >(0u));
}

FXC validation failure:
C:\src\dawn\Shader@0x0000020F8A503780(6,3-21): error X3018: invalid subscript 'Store'

