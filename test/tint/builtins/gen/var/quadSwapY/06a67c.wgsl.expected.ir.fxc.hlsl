SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
uint3 quadSwapY_06a67c() {
  uint3 arg_0 = (1u).xxx;
  uint3 res = QuadReadAcrossY(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store3(0u, quadSwapY_06a67c());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store3(0u, quadSwapY_06a67c());
}

FXC validation failure:
C:\src\dawn\Shader@0x00000244D66046D0(5,15-36): error X3004: undeclared identifier 'QuadReadAcrossY'

