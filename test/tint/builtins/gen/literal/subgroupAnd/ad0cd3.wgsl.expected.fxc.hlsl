SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

uint3 subgroupAnd_ad0cd3() {
  uint3 res = WaveActiveBitAnd((1u).xxx);
  return res;
}

void fragment_main() {
  prevent_dce.Store3(0u, asuint(subgroupAnd_ad0cd3()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store3(0u, asuint(subgroupAnd_ad0cd3()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x0000026A18D246A0(4,15-40): error X3004: undeclared identifier 'WaveActiveBitAnd'

