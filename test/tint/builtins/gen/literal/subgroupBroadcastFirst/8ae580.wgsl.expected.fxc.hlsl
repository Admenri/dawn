SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float4 subgroupBroadcastFirst_8ae580() {
  float4 res = WaveReadLaneFirst((1.0f).xxxx);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(subgroupBroadcastFirst_8ae580()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(subgroupBroadcastFirst_8ae580()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x0000017940DBFD20(4,16-45): error X3004: undeclared identifier 'WaveReadLaneFirst'

