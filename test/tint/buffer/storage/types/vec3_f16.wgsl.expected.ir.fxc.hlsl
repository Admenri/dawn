SKIP: FAILED


ByteAddressBuffer tint_symbol : register(t0);
RWByteAddressBuffer tint_symbol_1 : register(u1);
[numthreads(1, 1, 1)]
void main() {
  tint_symbol_1.Store<vector<float16_t, 3> >(0u, tint_symbol.Load<vector<float16_t, 3> >(0u));
}

FXC validation failure:
C:\src\dawn\Shader@0x000002AE00E53750(6,3-21): error X3018: invalid subscript 'Store'

