SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
int4 subgroupMax_a3d5f7() {
  int4 arg_0 = (1).xxxx;
  int4 res = WaveActiveMax(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(subgroupMax_a3d5f7()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(subgroupMax_a3d5f7()));
}

FXC validation failure:
C:\src\dawn\Shader@0x000001D7C9DA9B00(5,14-33): error X3004: undeclared identifier 'WaveActiveMax'

