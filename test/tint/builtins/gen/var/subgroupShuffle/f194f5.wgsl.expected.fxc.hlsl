SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

uint subgroupShuffle_f194f5() {
  uint arg_0 = 1u;
  uint arg_1 = 1u;
  uint res = WaveReadLaneAt(arg_0, arg_1);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(subgroupShuffle_f194f5()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(subgroupShuffle_f194f5()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x0000017540A45ED0(6,14-41): error X3004: undeclared identifier 'WaveReadLaneAt'

