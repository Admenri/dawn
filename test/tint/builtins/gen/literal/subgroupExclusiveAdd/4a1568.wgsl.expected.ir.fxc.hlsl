SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float16_t subgroupExclusiveAdd_4a1568() {
  float16_t res = WavePrefixSum(float16_t(1.0h));
  return res;
}

void fragment_main() {
  prevent_dce.Store<float16_t>(0u, subgroupExclusiveAdd_4a1568());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<float16_t>(0u, subgroupExclusiveAdd_4a1568());
}

FXC validation failure:
C:\src\dawn\Shader@0x000001B697DE5000(3,1-9): error X3000: unrecognized identifier 'float16_t'

