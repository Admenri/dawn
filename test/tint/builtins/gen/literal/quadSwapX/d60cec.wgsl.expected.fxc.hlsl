SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

vector<float16_t, 2> quadSwapX_d60cec() {
  vector<float16_t, 2> res = QuadReadAcrossX((float16_t(1.0h)).xx);
  return res;
}

void fragment_main() {
  prevent_dce.Store<vector<float16_t, 2> >(0u, quadSwapX_d60cec());
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<vector<float16_t, 2> >(0u, quadSwapX_d60cec());
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x0000027950857040(3,8-16): error X3000: syntax error: unexpected token 'float16_t'

