SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float4 subgroupMin_bbd9b0() {
  float4 arg_0 = (1.0f).xxxx;
  float4 res = WaveActiveMin(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(subgroupMin_bbd9b0()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(subgroupMin_bbd9b0()));
}

FXC validation failure:
C:\src\dawn\Shader@0x00000144B05E0540(5,16-35): error X3004: undeclared identifier 'WaveActiveMin'

