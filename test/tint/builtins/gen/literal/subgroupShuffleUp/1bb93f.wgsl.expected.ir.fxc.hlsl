SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
int subgroupShuffleUp_1bb93f() {
  int res = WaveReadLaneAt(1, (WaveGetLaneIndex() - 1u));
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(subgroupShuffleUp_1bb93f()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(subgroupShuffleUp_1bb93f()));
}

FXC validation failure:
C:\src\dawn\Shader@0x00000266ACB24680(4,32-49): error X3004: undeclared identifier 'WaveGetLaneIndex'

