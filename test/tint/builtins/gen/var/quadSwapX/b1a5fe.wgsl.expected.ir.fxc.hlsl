SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
int2 quadSwapX_b1a5fe() {
  int2 arg_0 = (1).xx;
  int2 res = QuadReadAcrossX(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, asuint(quadSwapX_b1a5fe()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, asuint(quadSwapX_b1a5fe()));
}

FXC validation failure:
C:\src\dawn\Shader@0x00000272C6A546A0(5,14-35): error X3004: undeclared identifier 'QuadReadAcrossX'

