SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
uint4 quadBroadcast_b68331() {
  uint4 res = QuadReadLaneAt((1u).xxxx, 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, quadBroadcast_b68331());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, quadBroadcast_b68331());
}

FXC validation failure:
C:\src\dawn\Shader@0x0000022034AA6550(4,15-42): error X3004: undeclared identifier 'QuadReadLaneAt'

