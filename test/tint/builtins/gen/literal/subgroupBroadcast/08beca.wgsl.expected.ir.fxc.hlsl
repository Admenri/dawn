SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float subgroupBroadcast_08beca() {
  float res = WaveReadLaneAt(1.0f, 1u);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(subgroupBroadcast_08beca()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(subgroupBroadcast_08beca()));
}

FXC validation failure:
C:\src\dawn\Shader@0x000001C812A146B0(4,15-38): error X3004: undeclared identifier 'WaveReadLaneAt'

