SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float16_t subgroupShuffleXor_d224ab() {
  float16_t res = WaveReadLaneAt(float16_t(1.0h), (WaveGetLaneIndex() ^ 1u));
  return res;
}

void fragment_main() {
  prevent_dce.Store<float16_t>(0u, subgroupShuffleXor_d224ab());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<float16_t>(0u, subgroupShuffleXor_d224ab());
}

FXC validation failure:
C:\src\dawn\Shader@0x000001FD843B4FD0(3,1-9): error X3000: unrecognized identifier 'float16_t'

