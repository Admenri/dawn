SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
int4 quadSwapDiagonal_a665b1() {
  int4 arg_0 = (1).xxxx;
  int4 res = QuadReadAcrossDiagonal(arg_0);
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
C:\src\dawn\Shader@0x000002B41C1A6080(5,14-42): error X3004: undeclared identifier 'QuadReadAcrossDiagonal'

