SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float2 subgroupExclusiveMul_25d1b9() {
  float2 arg_0 = (1.0f).xx;
  float2 res = WavePrefixProduct(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, asuint(subgroupExclusiveMul_25d1b9()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, asuint(subgroupExclusiveMul_25d1b9()));
}

FXC validation failure:
C:\src\dawn\Shader@0x0000012AF6CB3D30(5,16-39): error X3004: undeclared identifier 'WavePrefixProduct'

