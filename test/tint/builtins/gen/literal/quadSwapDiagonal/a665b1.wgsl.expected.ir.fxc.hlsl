SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
int4 quadSwapDiagonal_a665b1() {
  int4 res = QuadReadAcrossDiagonal((1).xxxx);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(quadSwapDiagonal_a665b1()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(quadSwapDiagonal_a665b1()));
}

FXC validation failure:
C:\src\dawn\Shader@0x000001F83F5DF880(4,14-45): error X3004: undeclared identifier 'QuadReadAcrossDiagonal'

