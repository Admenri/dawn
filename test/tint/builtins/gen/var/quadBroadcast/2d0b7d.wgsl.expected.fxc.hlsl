SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

uint4 quadBroadcast_2d0b7d() {
  uint4 arg_0 = (1u).xxxx;
  uint4 res = QuadReadLaneAt(arg_0, 1u);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(quadBroadcast_2d0b7d()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(quadBroadcast_2d0b7d()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x00000200F3FD9C50(5,15-39): error X3004: undeclared identifier 'QuadReadLaneAt'

