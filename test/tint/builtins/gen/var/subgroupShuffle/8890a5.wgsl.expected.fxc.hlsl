SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float2 subgroupShuffle_8890a5() {
  float2 arg_0 = (1.0f).xx;
  uint arg_1 = 1u;
  float2 res = WaveReadLaneAt(arg_0, arg_1);
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, asuint(subgroupShuffle_8890a5()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, asuint(subgroupShuffle_8890a5()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001E2E8124720(6,16-43): error X3004: undeclared identifier 'WaveReadLaneAt'

