SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

vector<float16_t, 2> subgroupBroadcastFirst_a11307() {
  vector<float16_t, 2> res = WaveReadLaneFirst((float16_t(1.0h)).xx);
  return res;
}

void fragment_main() {
  prevent_dce.Store<vector<float16_t, 2> >(0u, subgroupBroadcastFirst_a11307());
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<vector<float16_t, 2> >(0u, subgroupBroadcastFirst_a11307());
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001C81ACF60B0(3,8-16): error X3000: syntax error: unexpected token 'float16_t'

