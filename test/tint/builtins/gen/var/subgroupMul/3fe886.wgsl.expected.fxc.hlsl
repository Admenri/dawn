SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

int subgroupMul_3fe886() {
  int arg_0 = 1;
  int res = WaveActiveProduct(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(subgroupMul_3fe886()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(subgroupMul_3fe886()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x0000023E858B01D0(5,13-36): error X3004: undeclared identifier 'WaveActiveProduct'

