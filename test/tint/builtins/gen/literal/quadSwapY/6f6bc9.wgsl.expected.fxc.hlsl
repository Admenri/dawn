SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float quadSwapY_6f6bc9() {
  float res = QuadReadAcrossY(1.0f);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(quadSwapY_6f6bc9()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(quadSwapY_6f6bc9()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001ED55396BD0(4,15-35): error X3004: undeclared identifier 'QuadReadAcrossY'

