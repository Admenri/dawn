SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float subgroupBroadcastFirst_0538e1() {
  float arg_0 = 1.0f;
  float res = WaveReadLaneFirst(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(subgroupBroadcastFirst_0538e1()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(subgroupBroadcastFirst_0538e1()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x0000021202725010(5,15-38): error X3004: undeclared identifier 'WaveReadLaneFirst'

