SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
float16_t quadBroadcast_78129b() {
  float16_t res = QuadReadLaneAt(float16_t(1.0h), 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store<float16_t>(0u, quadBroadcast_78129b());
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<float16_t>(0u, quadBroadcast_78129b());
}

FXC validation failure:
C:\src\dawn\Shader@0x00000214151646B0(3,1-9): error X3000: unrecognized identifier 'float16_t'

