//
// fragment_main
//

RWByteAddressBuffer prevent_dce : register(u0);
int transpose_4ce359() {
  float2x4 arg_0 = float2x4((1.0f).xxxx, (1.0f).xxxx);
  float4x2 res = transpose(arg_0);
  return (((res[0u].x == 0.0f)) ? (int(1)) : (int(0)));
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(transpose_4ce359()));
}

//
// compute_main
//

RWByteAddressBuffer prevent_dce : register(u0);
int transpose_4ce359() {
  float2x4 arg_0 = float2x4((1.0f).xxxx, (1.0f).xxxx);
  float4x2 res = transpose(arg_0);
  return (((res[0u].x == 0.0f)) ? (int(1)) : (int(0)));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(transpose_4ce359()));
}

//
// vertex_main
//
struct VertexOutput {
  float4 pos;
  int prevent_dce;
};

struct vertex_main_outputs {
  nointerpolation int VertexOutput_prevent_dce : TEXCOORD0;
  float4 VertexOutput_pos : SV_Position;
};


int transpose_4ce359() {
  float2x4 arg_0 = float2x4((1.0f).xxxx, (1.0f).xxxx);
  float4x2 res = transpose(arg_0);
  return (((res[0u].x == 0.0f)) ? (int(1)) : (int(0)));
}

VertexOutput vertex_main_inner() {
  VertexOutput v = (VertexOutput)0;
  v.pos = (0.0f).xxxx;
  v.prevent_dce = transpose_4ce359();
  VertexOutput v_1 = v;
  return v_1;
}

vertex_main_outputs vertex_main() {
  VertexOutput v_2 = vertex_main_inner();
  vertex_main_outputs v_3 = {v_2.prevent_dce, v_2.pos};
  return v_3;
}

