SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
uint4 subgroupBroadcast_727609() {
  uint4 res = WaveReadLaneAt((1u).xxxx, 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, subgroupBroadcast_727609());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, subgroupBroadcast_727609());
}

FXC validation failure:
C:\src\dawn\Shader@0x000002B3C33946B0(4,15-42): error X3004: undeclared identifier 'WaveReadLaneAt'

