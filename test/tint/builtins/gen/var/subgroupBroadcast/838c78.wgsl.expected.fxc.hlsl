SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float4 subgroupBroadcast_838c78() {
  float4 arg_0 = (1.0f).xxxx;
  float4 res = WaveReadLaneAt(arg_0, 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(subgroupBroadcast_838c78()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(subgroupBroadcast_838c78()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000002504F7B5670(5,16-39): error X3004: undeclared identifier 'WaveReadLaneAt'

