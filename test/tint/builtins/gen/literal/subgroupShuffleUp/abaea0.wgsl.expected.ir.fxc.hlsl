SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
uint3 subgroupShuffleUp_abaea0() {
  uint3 res = WaveReadLaneAt((1u).xxx, (WaveGetLaneIndex() - 1u));
  return res;
}

void fragment_main() {
  prevent_dce.Store3(0u, subgroupShuffleUp_abaea0());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store3(0u, subgroupShuffleUp_abaea0());
}

FXC validation failure:
C:\src\dawn\Shader@0x000002DB6DAA46A0(4,41-58): error X3004: undeclared identifier 'WaveGetLaneIndex'

