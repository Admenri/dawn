SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
uint3 quadBroadcast_f1e8ec() {
  uint3 res = QuadReadLaneAt((1u).xxx, 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store3(0u, quadBroadcast_f1e8ec());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store3(0u, quadBroadcast_f1e8ec());
}

FXC validation failure:
C:\src\dawn\Shader@0x00000261E514BE80(4,15-41): error X3004: undeclared identifier 'QuadReadLaneAt'

