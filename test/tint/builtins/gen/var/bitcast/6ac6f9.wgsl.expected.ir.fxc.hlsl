SKIP: INVALID

struct VertexOutput {
  float4 pos;
  int prevent_dce;
};

struct vertex_main_outputs {
  nointerpolation int VertexOutput_prevent_dce : TEXCOORD0;
  float4 VertexOutput_pos : SV_Position;
};


RWByteAddressBuffer prevent_dce : register(u0);
int tint_bitcast_from_f16(vector<float16_t, 2> src) {
  uint2 r = f32tof16(float2(src));
  return asint(((r.x & 65535u) | ((r.y & 65535u) << 16u)));
}

int bitcast_6ac6f9() {
  vector<float16_t, 2> arg_0 = (float16_t(1.0h)).xx;
  int res = tint_bitcast_from_f16(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(bitcast_6ac6f9()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(bitcast_6ac6f9()));
}

VertexOutput vertex_main_inner() {
  VertexOutput tint_symbol = (VertexOutput)0;
  tint_symbol.pos = (0.0f).xxxx;
  tint_symbol.prevent_dce = bitcast_6ac6f9();
  VertexOutput v = tint_symbol;
  return v;
}

vertex_main_outputs vertex_main() {
  VertexOutput v_1 = vertex_main_inner();
  VertexOutput v_2 = v_1;
  VertexOutput v_3 = v_1;
  vertex_main_outputs v_4 = {v_3.prevent_dce, v_2.pos};
  return v_4;
}

FXC validation failure:
C:\src\dawn\Shader@0x00000187F728A670(13,34-42): error X3000: syntax error: unexpected token 'float16_t'
C:\src\dawn\Shader@0x00000187F728A670(14,29-31): error X3004: undeclared identifier 'src'
C:\src\dawn\Shader@0x00000187F728A670(14,22-32): error X3014: incorrect number of arguments to numeric-type constructor

