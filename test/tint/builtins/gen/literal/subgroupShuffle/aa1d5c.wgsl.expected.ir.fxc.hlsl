SKIP: INVALID


RWByteAddressBuffer prevent_dce : register(u0);
vector<float16_t, 2> subgroupShuffle_aa1d5c() {
  vector<float16_t, 2> res = WaveReadLaneAt((float16_t(1.0h)).xx, 1u);
  return res;
}

void fragment_main() {
  prevent_dce.Store<vector<float16_t, 2> >(0u, subgroupShuffle_aa1d5c());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<vector<float16_t, 2> >(0u, subgroupShuffle_aa1d5c());
}

FXC validation failure:
C:\src\dawn\Shader@0x000001A248324CE0(3,8-16): error X3000: syntax error: unexpected token 'float16_t'

