SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
uint2 quadSwapDiagonal_348173() {
  uint2 arg_0 = (1u).xx;
  uint2 res = QuadReadAcrossDiagonal(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, quadSwapDiagonal_348173());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, quadSwapDiagonal_348173());
}

FXC validation failure:
C:\src\dawn\Shader@0x0000020D3AD0FDC0(5,15-43): error X3004: undeclared identifier 'QuadReadAcrossDiagonal'

