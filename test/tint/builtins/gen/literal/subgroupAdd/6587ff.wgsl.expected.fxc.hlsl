SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

uint3 subgroupAdd_6587ff() {
  uint3 res = WaveActiveSum((1u).xxx);
  return res;
}

void fragment_main() {
  prevent_dce.Store3(0u, asuint(subgroupAdd_6587ff()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store3(0u, asuint(subgroupAdd_6587ff()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001D2EF3268F0(4,15-37): error X3004: undeclared identifier 'WaveActiveSum'

