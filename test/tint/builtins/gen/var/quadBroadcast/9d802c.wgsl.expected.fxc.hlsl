SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float4 quadBroadcast_9d802c() {
  float4 arg_0 = (1.0f).xxxx;
  float4 res = QuadReadLaneAt(arg_0, 1);
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
C:\src\dawn\Shader@0x00000279B4E402E0(5,16-39): error X3004: undeclared identifier 'QuadReadLaneAt'

