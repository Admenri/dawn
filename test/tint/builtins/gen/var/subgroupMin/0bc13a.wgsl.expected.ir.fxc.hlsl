SKIP: INVALID


RWByteAddressBuffer prevent_dce : register(u0);
int2 subgroupMin_0bc13a() {
  int2 arg_0 = (int(1)).xx;
  int2 res = WaveActiveMin(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, asuint(subgroupMin_0bc13a()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, asuint(subgroupMin_0bc13a()));
}

FXC validation failure:
<scrubbed_path>(5,14-33): error X3004: undeclared identifier 'WaveActiveMin'


tint executable returned error: exit status 1
