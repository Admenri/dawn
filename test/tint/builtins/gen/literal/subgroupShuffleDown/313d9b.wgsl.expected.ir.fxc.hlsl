SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
int4 subgroupShuffleDown_313d9b() {
  int4 res = WaveReadLaneAt((1).xxxx, (WaveGetLaneIndex() + 1u));
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(subgroupShuffleDown_313d9b()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(subgroupShuffleDown_313d9b()));
}

FXC validation failure:
C:\src\dawn\Shader@0x000002333AA64D30(4,40-57): error X3004: undeclared identifier 'WaveGetLaneIndex'

