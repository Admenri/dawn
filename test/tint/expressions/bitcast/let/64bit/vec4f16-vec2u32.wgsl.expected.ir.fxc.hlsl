SKIP: INVALID


uint2 tint_bitcast_from_f16(vector<float16_t, 4> src) {
  uint4 r = f32tof16(float4(src));
  return uint2(((r.x & 65535u) | ((r.y & 65535u) << 16u)), ((r.z & 65535u) | ((r.w & 65535u) << 16u)));
}

[numthreads(1, 1, 1)]
void f() {
  vector<float16_t, 4> a = vector<float16_t, 4>(float16_t(1.0h), float16_t(2.0h), float16_t(3.0h), float16_t(-4.0h));
  uint2 b = tint_bitcast_from_f16(a);
}

FXC validation failure:
C:\src\dawn\Shader@0x00000257BCBEB0E0(2,36-44): error X3000: syntax error: unexpected token 'float16_t'
C:\src\dawn\Shader@0x00000257BCBEB0E0(3,29-31): error X3004: undeclared identifier 'src'
C:\src\dawn\Shader@0x00000257BCBEB0E0(3,22-32): error X3014: incorrect number of arguments to numeric-type constructor

