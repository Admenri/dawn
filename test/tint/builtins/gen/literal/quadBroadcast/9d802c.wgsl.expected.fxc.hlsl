SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float4 quadBroadcast_9d802c() {
  float4 res = QuadReadLaneAt((1.0f).xxxx, 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(quadBroadcast_9d802c()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(quadBroadcast_9d802c()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x0000025CC04546C0(4,16-45): error X3004: undeclared identifier 'QuadReadLaneAt'

