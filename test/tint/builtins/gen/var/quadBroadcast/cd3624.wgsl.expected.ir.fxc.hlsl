SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float2 quadBroadcast_cd3624() {
  float2 arg_0 = (1.0f).xx;
  float2 res = QuadReadLaneAt(arg_0, 1u);
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, asuint(quadBroadcast_cd3624()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, asuint(quadBroadcast_cd3624()));
}

FXC validation failure:
C:\src\dawn\Shader@0x0000018ABC148DC0(5,16-40): error X3004: undeclared identifier 'QuadReadLaneAt'

