SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float subgroupBroadcast_867093() {
  float res = WaveReadLaneAt(1.0f, 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(subgroupBroadcast_867093()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(subgroupBroadcast_867093()));
}

FXC validation failure:
C:\src\dawn\Shader@0x0000019F641EF700(4,15-37): error X3004: undeclared identifier 'WaveReadLaneAt'

