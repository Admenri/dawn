SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
uint3 subgroupBroadcast_34fa3d() {
  uint3 arg_0 = (1u).xxx;
  uint3 res = WaveReadLaneAt(arg_0, 1u);
  return res;
}

void fragment_main() {
  prevent_dce.Store3(0u, subgroupBroadcast_34fa3d());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store3(0u, subgroupBroadcast_34fa3d());
}

FXC validation failure:
C:\src\dawn\Shader@0x000001AC7A80A970(5,15-39): error X3004: undeclared identifier 'WaveReadLaneAt'

