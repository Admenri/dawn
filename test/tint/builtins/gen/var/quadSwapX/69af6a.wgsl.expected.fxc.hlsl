SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float4 quadSwapX_69af6a() {
  float4 arg_0 = (1.0f).xxxx;
  float4 res = QuadReadAcrossX(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(quadSwapX_69af6a()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(quadSwapX_69af6a()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001CDB1A702E0(5,16-37): error X3004: undeclared identifier 'QuadReadAcrossX'

