SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
uint4 quadSwapY_bb697b() {
  uint4 arg_0 = (1u).xxxx;
  uint4 res = QuadReadAcrossY(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, quadSwapY_bb697b());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, quadSwapY_bb697b());
}

FXC validation failure:
C:\src\dawn\Shader@0x0000024D99047F60(5,15-36): error X3004: undeclared identifier 'QuadReadAcrossY'

