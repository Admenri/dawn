SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
vector<float16_t, 3> quadSwapDiagonal_e4bec8() {
  vector<float16_t, 3> res = QuadReadAcrossDiagonal((float16_t(1.0h)).xxx);
  return res;
}

void fragment_main() {
  prevent_dce.Store<vector<float16_t, 3> >(0u, quadSwapDiagonal_e4bec8());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<vector<float16_t, 3> >(0u, quadSwapDiagonal_e4bec8());
}

FXC validation failure:
C:\src\dawn\Shader@0x0000017B83C34CE0(3,8-16): error X3000: syntax error: unexpected token 'float16_t'

