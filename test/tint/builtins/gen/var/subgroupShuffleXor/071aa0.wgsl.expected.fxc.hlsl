SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

int2 subgroupShuffleXor_071aa0() {
  int2 arg_0 = (1).xx;
  uint arg_1 = 1u;
  int2 res = WaveReadLaneAt(arg_0, (WaveGetLaneIndex() ^ arg_1));
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, asuint(subgroupShuffleXor_071aa0()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, asuint(subgroupShuffleXor_071aa0()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001839C5402B0(6,37-54): error X3004: undeclared identifier 'WaveGetLaneIndex'

