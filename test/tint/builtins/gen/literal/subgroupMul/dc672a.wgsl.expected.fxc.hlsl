SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

uint2 subgroupMul_dc672a() {
  uint2 res = WaveActiveProduct((1u).xx);
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, asuint(subgroupMul_dc672a()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, asuint(subgroupMul_dc672a()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x0000021496A77F60(4,15-40): error X3004: undeclared identifier 'WaveActiveProduct'

