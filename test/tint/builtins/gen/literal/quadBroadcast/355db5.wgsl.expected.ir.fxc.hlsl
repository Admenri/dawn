SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float3 quadBroadcast_355db5() {
  float3 res = QuadReadLaneAt((1.0f).xxx, 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store3(0u, asuint(quadBroadcast_355db5()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store3(0u, asuint(quadBroadcast_355db5()));
}

FXC validation failure:
C:\src\dawn\Shader@0x000001880A2CFB80(4,16-44): error X3004: undeclared identifier 'QuadReadLaneAt'

