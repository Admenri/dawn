SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

uint4 subgroupOr_f915e3() {
  uint4 arg_0 = (1u).xxxx;
  uint4 res = WaveActiveBitOr(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(subgroupOr_f915e3()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(subgroupOr_f915e3()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001FCE32A6030(5,15-36): error X3004: undeclared identifier 'WaveActiveBitOr'

