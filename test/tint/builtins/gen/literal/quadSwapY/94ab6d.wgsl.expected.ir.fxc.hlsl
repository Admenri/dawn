SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
int quadSwapY_94ab6d() {
  int res = QuadReadAcrossY(1);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(quadSwapY_94ab6d()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(quadSwapY_94ab6d()));
}

FXC validation failure:
C:\src\dawn\Shader@0x00000277BD745590(4,13-30): error X3004: undeclared identifier 'QuadReadAcrossY'

