SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float subgroupShuffleXor_1d36b6() {
  float res = WaveReadLaneAt(1.0f, (WaveGetLaneIndex() ^ 1u));
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
C:\src\dawn\Shader@0x00000265F1244E70(4,37-54): error X3004: undeclared identifier 'WaveGetLaneIndex'

