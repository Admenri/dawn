SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

uint quadBroadcast_a2d2b4() {
  uint arg_0 = 1u;
  uint res = QuadReadLaneAt(arg_0, 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(quadBroadcast_a2d2b4()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(quadBroadcast_a2d2b4()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001CFFB14C2F0(5,14-37): error X3004: undeclared identifier 'QuadReadLaneAt'

