SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

int subgroupAll_c962bd() {
  bool res = WaveActiveAllTrue(true);
  return (all((res == false)) ? 1 : 0);
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(subgroupAll_c962bd()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(subgroupAll_c962bd()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001CFBD5A9C10(4,14-36): error X3004: undeclared identifier 'WaveActiveAllTrue'

