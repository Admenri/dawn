SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float quadSwapDiagonal_486196() {
  float res = QuadReadAcrossDiagonal(1.0f);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(quadSwapDiagonal_486196()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(quadSwapDiagonal_486196()));
}

FXC validation failure:
C:\src\dawn\Shader@0x000002047B7DA360(4,15-42): error X3004: undeclared identifier 'QuadReadAcrossDiagonal'

