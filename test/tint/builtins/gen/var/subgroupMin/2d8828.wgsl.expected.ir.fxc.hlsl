SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float2 subgroupMin_2d8828() {
  float2 arg_0 = (1.0f).xx;
  float2 res = WaveActiveMin(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store2(0u, asuint(subgroupMin_2d8828()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store2(0u, asuint(subgroupMin_2d8828()));
}

FXC validation failure:
C:\src\dawn\Shader@0x000002290D1306D0(5,16-35): error X3004: undeclared identifier 'WaveActiveMin'

