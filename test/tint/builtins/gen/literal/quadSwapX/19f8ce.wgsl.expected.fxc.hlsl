SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

uint2 quadSwapX_19f8ce() {
  uint2 res = QuadReadAcrossX((1u).xx);
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, asuint(quadSwapX_19f8ce()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, asuint(quadSwapX_19f8ce()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x0000028CB7D9D850(4,15-38): error X3004: undeclared identifier 'QuadReadAcrossX'

