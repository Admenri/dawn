SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float4 subgroupAdd_8f4c15() {
  float4 res = WaveActiveSum((1.0f).xxxx);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(subgroupAdd_8f4c15()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(subgroupAdd_8f4c15()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x00000249358A6A80(4,16-41): error X3004: undeclared identifier 'WaveActiveSum'

