SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

uint4 subgroupShuffle_e13c81() {
  uint4 res = WaveReadLaneAt((1u).xxxx, 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(subgroupShuffle_e13c81()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(subgroupShuffle_e13c81()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001E9CA070680(4,15-42): error X3004: undeclared identifier 'WaveReadLaneAt'

