SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

uint2 subgroupBroadcastFirst_1d9530() {
  uint2 arg_0 = (1u).xx;
  uint2 res = WaveReadLaneFirst(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, asuint(subgroupBroadcastFirst_1d9530()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, asuint(subgroupBroadcastFirst_1d9530()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x0000026B73DDC9A0(5,15-38): error X3004: undeclared identifier 'WaveReadLaneFirst'

