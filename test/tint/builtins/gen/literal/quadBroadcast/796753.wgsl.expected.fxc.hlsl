SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

vector<float16_t, 3> quadBroadcast_796753() {
  vector<float16_t, 3> res = QuadReadLaneAt((float16_t(1.0h)).xxx, 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store<vector<float16_t, 3> >(0u, quadBroadcast_796753());
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<vector<float16_t, 3> >(0u, quadBroadcast_796753());
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x00000223E0924700(3,8-16): error X3000: syntax error: unexpected token 'float16_t'

