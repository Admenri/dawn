SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float3 quadSwapX_150d6f() {
  float3 res = QuadReadAcrossX((1.0f).xxx);
  return res;
}

void fragment_main() {
  prevent_dce.Store3(0u, asuint(quadSwapX_150d6f()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store3(0u, asuint(quadSwapX_150d6f()));
}

FXC validation failure:
C:\src\dawn\Shader@0x0000020DB93AFB60(4,16-42): error X3004: undeclared identifier 'QuadReadAcrossX'

