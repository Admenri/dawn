SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
int4 subgroupBroadcast_f637f9() {
  int4 res = WaveReadLaneAt((1).xxxx, 1u);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(subgroupBroadcast_f637f9()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(subgroupBroadcast_f637f9()));
}

FXC validation failure:
C:\src\dawn\Shader@0x0000011D4807C250(4,14-41): error X3004: undeclared identifier 'WaveReadLaneAt'

