SKIP: INVALID


RWByteAddressBuffer prevent_dce : register(u0);
vector<float16_t, 4> subgroupMax_33e339() {
  vector<float16_t, 4> res = WaveActiveMax((float16_t(1.0h)).xxxx);
  return res;
}

void fragment_main() {
  prevent_dce.Store<vector<float16_t, 4> >(0u, subgroupMax_33e339());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<vector<float16_t, 4> >(0u, subgroupMax_33e339());
}

FXC validation failure:
C:\src\dawn\Shader@0x000001DEEB8DFAC0(3,8-16): error X3000: syntax error: unexpected token 'float16_t'

