SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

vector<float16_t, 2> subgroupShuffleXor_1e247f() {
  vector<float16_t, 2> arg_0 = (float16_t(1.0h)).xx;
  uint arg_1 = 1u;
  vector<float16_t, 2> res = WaveReadLaneAt(arg_0, (WaveGetLaneIndex() ^ arg_1));
  return res;
}

void fragment_main() {
  prevent_dce.Store<vector<float16_t, 2> >(0u, subgroupShuffleXor_1e247f());
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<vector<float16_t, 2> >(0u, subgroupShuffleXor_1e247f());
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x00000218F13CD220(3,8-16): error X3000: syntax error: unexpected token 'float16_t'

