SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

int3 subgroupShuffleDown_1b530f() {
  int3 res = WaveReadLaneAt((1).xxx, (WaveGetLaneIndex() + 1u));
  return res;
}

void fragment_main() {
  prevent_dce.Store3(0u, asuint(subgroupShuffleDown_1b530f()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store3(0u, asuint(subgroupShuffleDown_1b530f()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x0000021C54244630(4,39-56): error X3004: undeclared identifier 'WaveGetLaneIndex'

