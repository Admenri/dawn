SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float16_t subgroupBroadcast_07e2d8() {
  float16_t arg_0 = float16_t(1.0h);
  float16_t res = WaveReadLaneAt(arg_0, 1u);
  return res;
}

void fragment_main() {
  prevent_dce.Store<float16_t>(0u, subgroupBroadcast_07e2d8());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<float16_t>(0u, subgroupBroadcast_07e2d8());
}

FXC validation failure:
C:\src\dawn\Shader@0x000001A47C08C400(3,1-9): error X3000: unrecognized identifier 'float16_t'

