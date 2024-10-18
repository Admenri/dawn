
cbuffer cbuffer_a : register(b0) {
  uint4 a[4];
};
RWByteAddressBuffer s : register(u1);
vector<float16_t, 4> tint_bitcast_to_f16(uint4 src) {
  uint4 v = src;
  uint4 mask = (65535u).xxxx;
  uint4 shift = (16u).xxxx;
  float4 t_low = f16tof32((v & mask));
  float4 t_high = f16tof32(((v >> shift) & mask));
  float16_t v_1 = float16_t(t_low.x);
  float16_t v_2 = float16_t(t_high.x);
  float16_t v_3 = float16_t(t_low.y);
  return vector<float16_t, 4>(v_1, v_2, v_3, float16_t(t_high.y));
}

matrix<float16_t, 2, 4> v_4(uint start_byte_offset) {
  vector<float16_t, 4> v_5 = tint_bitcast_to_f16(a[(start_byte_offset / 16u)]);
  return matrix<float16_t, 2, 4>(v_5, tint_bitcast_to_f16(a[((8u + start_byte_offset) / 16u)]));
}

typedef matrix<float16_t, 2, 4> ary_ret[4];
ary_ret v_6(uint start_byte_offset) {
  matrix<float16_t, 2, 4> a_1[4] = (matrix<float16_t, 2, 4>[4])0;
  {
    uint v_7 = 0u;
    v_7 = 0u;
    while(true) {
      uint v_8 = v_7;
      if ((v_8 >= 4u)) {
        break;
      }
      a_1[v_8] = v_4((start_byte_offset + (v_8 * 16u)));
      {
        v_7 = (v_8 + 1u);
      }
      continue;
    }
  }
  matrix<float16_t, 2, 4> v_9[4] = a_1;
  return v_9;
}

[numthreads(1, 1, 1)]
void f() {
  matrix<float16_t, 2, 4> v_10[4] = v_6(0u);
  matrix<float16_t, 2, 4> l_a_i = v_4(32u);
  vector<float16_t, 4> l_a_i_i = tint_bitcast_to_f16(a[2u]);
  matrix<float16_t, 2, 4> l_a[4] = v_10;
  s.Store<float16_t>(0u, (((float16_t(f16tof32(a[2u].z)) + l_a[int(0)][int(0)][0u]) + l_a_i[int(0)][0u]) + l_a_i_i[0u]));
}

