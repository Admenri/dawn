SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float2 subgroupBroadcast_cd7aa1() {
  float2 res = WaveReadLaneAt((1.0f).xx, 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, asuint(subgroupBroadcast_cd7aa1()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, asuint(subgroupBroadcast_cd7aa1()));
}

FXC validation failure:
C:\src\dawn\Shader@0x00000234FD6EFDC0(4,16-43): error X3004: undeclared identifier 'WaveReadLaneAt'

