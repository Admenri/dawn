SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
vector<float16_t, 2> quadSwapY_a50fcb() {
  vector<float16_t, 2> arg_0 = (float16_t(1.0h)).xx;
  vector<float16_t, 2> res = QuadReadAcrossY(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store<vector<float16_t, 2> >(0u, quadSwapY_a50fcb());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<vector<float16_t, 2> >(0u, quadSwapY_a50fcb());
}

FXC validation failure:
C:\src\dawn\Shader@0x000002830A7AFFB0(3,8-16): error X3000: syntax error: unexpected token 'float16_t'

