
cbuffer cbuffer_u : register(b0) {
  uint4 u[2];
};
void a(matrix<float16_t, 4, 4> m) {
}

void b(vector<float16_t, 4> v) {
}

void c(float16_t f_1) {
}

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

matrix<float16_t, 4, 4> v_4(uint start_byte_offset) {
  vector<float16_t, 4> v_5 = tint_bitcast_to_f16(u[(start_byte_offset / 16u)]);
  vector<float16_t, 4> v_6 = tint_bitcast_to_f16(u[((8u + start_byte_offset) / 16u)]);
  vector<float16_t, 4> v_7 = tint_bitcast_to_f16(u[((16u + start_byte_offset) / 16u)]);
  return matrix<float16_t, 4, 4>(v_5, v_6, v_7, tint_bitcast_to_f16(u[((24u + start_byte_offset) / 16u)]));
}

[numthreads(1, 1, 1)]
void f() {
  a(v_4(0u));
  b(tint_bitcast_to_f16(u[0u]));
  b(tint_bitcast_to_f16(u[0u]).ywxz);
  c(float16_t(f16tof32(u[0u].z)));
  c(tint_bitcast_to_f16(u[0u]).ywxz[0u]);
}

