SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
uint2 subgroupShuffleXor_e3c10b() {
  uint2 res = WaveReadLaneAt((1u).xx, (WaveGetLaneIndex() ^ 1u));
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, subgroupShuffleXor_e3c10b());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, subgroupShuffleXor_e3c10b());
}

FXC validation failure:
C:\src\dawn\Shader@0x000001763EFE14C0(4,40-57): error X3004: undeclared identifier 'WaveGetLaneIndex'

