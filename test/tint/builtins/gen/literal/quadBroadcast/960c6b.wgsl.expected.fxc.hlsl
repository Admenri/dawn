SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float quadBroadcast_960c6b() {
  float res = QuadReadLaneAt(1.0f, 1u);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(quadBroadcast_960c6b()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(quadBroadcast_960c6b()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001CB7B8BFED0(4,15-38): error X3004: undeclared identifier 'QuadReadLaneAt'

