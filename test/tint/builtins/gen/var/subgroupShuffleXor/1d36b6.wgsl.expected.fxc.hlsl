SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float subgroupShuffleXor_1d36b6() {
  float arg_0 = 1.0f;
  uint arg_1 = 1u;
  float res = WaveReadLaneAt(arg_0, (WaveGetLaneIndex() ^ arg_1));
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(subgroupShuffleXor_1d36b6()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(subgroupShuffleXor_1d36b6()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001D426A54BF0(6,38-55): error X3004: undeclared identifier 'WaveGetLaneIndex'

