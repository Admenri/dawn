SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
uint2 subgroupBroadcast_a279d7() {
  uint2 arg_0 = (1u).xx;
  uint2 res = WaveReadLaneAt(arg_0, 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, subgroupBroadcast_a279d7());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, subgroupBroadcast_a279d7());
}

FXC validation failure:
C:\src\dawn\Shader@0x0000023818AA58D0(5,15-38): error X3004: undeclared identifier 'WaveReadLaneAt'

