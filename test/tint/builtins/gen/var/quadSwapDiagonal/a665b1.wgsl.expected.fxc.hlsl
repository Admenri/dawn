SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

int4 quadSwapDiagonal_a665b1() {
  int4 arg_0 = (1).xxxx;
  int4 res = QuadReadAcrossDiagonal(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(quadSwapDiagonal_a665b1()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(quadSwapDiagonal_a665b1()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x00000259A2B9D0D0(5,14-42): error X3004: undeclared identifier 'QuadReadAcrossDiagonal'

