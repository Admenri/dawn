SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float4 subgroupMul_66c813() {
  float4 res = WaveActiveProduct((1.0f).xxxx);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(subgroupMul_66c813()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(subgroupMul_66c813()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x00000178F5B46910(4,16-45): error X3004: undeclared identifier 'WaveActiveProduct'

