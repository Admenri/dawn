SKIP: INVALID

uint2 tint_bitcast_from_f16(vector<float16_t, 4> src) {
  uint4 r = f32tof16(float4(src));
  return asuint(uint2((r.x & 0xffff) | ((r.y & 0xffff) << 16), (r.z & 0xffff) | ((r.w & 0xffff) << 16)));
}

[numthreads(1, 1, 1)]
void f() {
  vector<float16_t, 4> a = vector<float16_t, 4>(float16_t(1.0h), float16_t(2.0h), float16_t(3.0h), float16_t(-4.0h));
  uint2 b = tint_bitcast_from_f16(a);
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001D8F200B0C0(1,36-44): error X3000: syntax error: unexpected token 'float16_t'
C:\src\dawn\Shader@0x000001D8F200B0C0(2,29-31): error X3004: undeclared identifier 'src'
C:\src\dawn\Shader@0x000001D8F200B0C0(2,22-32): error X3014: incorrect number of arguments to numeric-type constructor

