SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float subgroupExclusiveMul_98b2e4() {
  float res = WavePrefixProduct(1.0f);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(subgroupExclusiveMul_98b2e4()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(subgroupExclusiveMul_98b2e4()));
}

FXC validation failure:
C:\src\dawn\Shader@0x000001C4B386F720(4,15-37): error X3004: undeclared identifier 'WavePrefixProduct'

