SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float16_t subgroupAdd_225207() {
  float16_t res = WaveActiveSum(float16_t(1.0h));
  return res;
}

void fragment_main() {
  prevent_dce.Store<float16_t>(0u, subgroupAdd_225207());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<float16_t>(0u, subgroupAdd_225207());
}

FXC validation failure:
C:\src\dawn\Shader@0x0000024621515BA0(3,1-9): error X3000: unrecognized identifier 'float16_t'

