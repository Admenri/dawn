SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float2 subgroupBroadcastFirst_6945f6() {
  float2 arg_0 = (1.0f).xx;
  float2 res = WaveReadLaneFirst(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, asuint(subgroupBroadcastFirst_6945f6()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, asuint(subgroupBroadcastFirst_6945f6()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001AA2277FCD0(5,16-39): error X3004: undeclared identifier 'WaveReadLaneFirst'

