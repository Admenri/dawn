SKIP: FAILED

cbuffer cbuffer_u : register(b0) {
  uint4 u[1];
};

matrix<float16_t, 2, 2> u_load(uint offset) {
  const uint scalar_offset = ((offset + 0u)) / 4;
  uint ubo_load = u[scalar_offset / 4][scalar_offset % 4];
  const uint scalar_offset_1 = ((offset + 4u)) / 4;
  uint ubo_load_1 = u[scalar_offset_1 / 4][scalar_offset_1 % 4];
  return matrix<float16_t, 2, 2>(vector<float16_t, 2>(float16_t(f16tof32(ubo_load & 0xFFFF)), float16_t(f16tof32(ubo_load >> 16))), vector<float16_t, 2>(float16_t(f16tof32(ubo_load_1 & 0xFFFF)), float16_t(f16tof32(ubo_load_1 >> 16))));
}

[numthreads(1, 1, 1)]
void f() {
  matrix<float16_t, 2, 2> t = transpose(u_load(0u));
  uint ubo_load_2 = u[0].y;
  float16_t l = length(vector<float16_t, 2>(float16_t(f16tof32(ubo_load_2 & 0xFFFF)), float16_t(f16tof32(ubo_load_2 >> 16))));
  uint ubo_load_3 = u[0].x;
  float16_t a = abs(vector<float16_t, 2>(float16_t(f16tof32(ubo_load_3 & 0xFFFF)), float16_t(f16tof32(ubo_load_3 >> 16))).yx.x);
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001BB2035B9F0(5,8-16): error X3000: syntax error: unexpected token 'float16_t'

