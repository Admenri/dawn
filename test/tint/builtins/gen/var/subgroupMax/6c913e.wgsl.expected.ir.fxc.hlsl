SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
int subgroupMax_6c913e() {
  int arg_0 = 1;
  int res = WaveActiveMax(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(subgroupMax_6c913e()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(subgroupMax_6c913e()));
}

FXC validation failure:
C:\src\dawn\Shader@0x000001DD40494D20(5,13-32): error X3004: undeclared identifier 'WaveActiveMax'

