SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

uint subgroupOr_0bc264() {
  uint res = WaveActiveBitOr(1u);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(subgroupOr_0bc264()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(subgroupOr_0bc264()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001F9B28E4FA0(4,14-32): error X3004: undeclared identifier 'WaveActiveBitOr'

