SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float subgroupMul_0de9d3() {
  float res = WaveActiveProduct(1.0f);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(subgroupMul_0de9d3()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(subgroupMul_0de9d3()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000002041E5BAFA0(4,15-37): error X3004: undeclared identifier 'WaveActiveProduct'

