SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

vector<float16_t, 4> subgroupMin_cd3b9d() {
  vector<float16_t, 4> res = WaveActiveMin((float16_t(1.0h)).xxxx);
  return res;
}

void fragment_main() {
  prevent_dce.Store<vector<float16_t, 4> >(0u, subgroupMin_cd3b9d());
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<vector<float16_t, 4> >(0u, subgroupMin_cd3b9d());
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001AA6D4046A0(3,8-16): error X3000: syntax error: unexpected token 'float16_t'

