SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

float16_t subgroupBroadcastFirst_151e52() {
  float16_t arg_0 = float16_t(1.0h);
  float16_t res = WaveReadLaneFirst(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store<float16_t>(0u, subgroupBroadcastFirst_151e52());
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<float16_t>(0u, subgroupBroadcastFirst_151e52());
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001A10EBCBDA0(3,1-9): error X3000: unrecognized identifier 'float16_t'

