SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

int4 subgroupShuffleUp_3e609f() {
  int4 arg_0 = (1).xxxx;
  uint arg_1 = 1u;
  int4 res = WaveReadLaneAt(arg_0, (WaveGetLaneIndex() - arg_1));
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(subgroupShuffleUp_3e609f()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(subgroupShuffleUp_3e609f()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x0000020A3197B660(6,37-54): error X3004: undeclared identifier 'WaveGetLaneIndex'

