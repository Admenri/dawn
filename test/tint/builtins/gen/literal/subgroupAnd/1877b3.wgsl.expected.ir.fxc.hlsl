SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
int3 subgroupAnd_1877b3() {
  int3 arg = (1).xxx;
  int3 res = asint(WaveActiveBitAnd(asuint(arg)));
  return res;
}

void fragment_main() {
  prevent_dce.Store3(0u, asuint(subgroupAnd_1877b3()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store3(0u, asuint(subgroupAnd_1877b3()));
}

FXC validation failure:
C:\src\dawn\Shader@0x000001FF0024BE30(5,20-48): error X3004: undeclared identifier 'WaveActiveBitAnd'

