SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

int subgroupShuffleXor_445e83() {
  int res = WaveReadLaneAt(1, (WaveGetLaneIndex() ^ 1u));
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(subgroupShuffleXor_445e83()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(subgroupShuffleXor_445e83()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001E165554690(4,32-49): error X3004: undeclared identifier 'WaveGetLaneIndex'

