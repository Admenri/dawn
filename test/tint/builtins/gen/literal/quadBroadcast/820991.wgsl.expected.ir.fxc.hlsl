SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float4 quadBroadcast_820991() {
  float4 res = QuadReadLaneAt((1.0f).xxxx, 1u);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(quadBroadcast_820991()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(quadBroadcast_820991()));
}

FXC validation failure:
C:\src\dawn\Shader@0x0000019A9FC8FB80(4,16-46): error X3004: undeclared identifier 'QuadReadLaneAt'

