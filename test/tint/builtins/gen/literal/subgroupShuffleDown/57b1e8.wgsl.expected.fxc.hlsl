SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

vector<float16_t, 2> subgroupShuffleDown_57b1e8() {
  vector<float16_t, 2> res = WaveReadLaneAt((float16_t(1.0h)).xx, (WaveGetLaneIndex() + 1u));
  return res;
}

void fragment_main() {
  prevent_dce.Store<vector<float16_t, 2> >(0u, subgroupShuffleDown_57b1e8());
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<vector<float16_t, 2> >(0u, subgroupShuffleDown_57b1e8());
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000002C2371938C0(3,8-16): error X3000: syntax error: unexpected token 'float16_t'

