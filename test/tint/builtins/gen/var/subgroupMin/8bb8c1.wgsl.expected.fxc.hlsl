SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

uint2 subgroupMin_8bb8c1() {
  uint2 arg_0 = (1u).xx;
  uint2 res = WaveActiveMin(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, asuint(subgroupMin_8bb8c1()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, asuint(subgroupMin_8bb8c1()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000002654EA3B080(5,15-34): error X3004: undeclared identifier 'WaveActiveMin'

