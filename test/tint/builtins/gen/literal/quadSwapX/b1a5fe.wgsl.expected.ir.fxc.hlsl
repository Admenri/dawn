SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
int2 quadSwapX_b1a5fe() {
  int2 res = QuadReadAcrossX((1).xx);
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
C:\src\dawn\Shader@0x0000018A218D60F0(4,14-36): error X3004: undeclared identifier 'QuadReadAcrossX'

