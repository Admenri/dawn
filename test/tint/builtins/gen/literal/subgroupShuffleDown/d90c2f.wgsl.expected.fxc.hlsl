SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

uint subgroupShuffleDown_d90c2f() {
  uint res = WaveReadLaneAt(1u, (WaveGetLaneIndex() + 1u));
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(subgroupShuffleDown_d90c2f()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(subgroupShuffleDown_d90c2f()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x0000022474326B10(4,34-51): error X3004: undeclared identifier 'WaveGetLaneIndex'

