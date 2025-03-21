//
// fragment_main
//
vector<float16_t, 2> tint_atanh(vector<float16_t, 2> x) {
  return (log(((float16_t(1.0h) + x) / (float16_t(1.0h) - x))) * float16_t(0.5h));
}

RWByteAddressBuffer prevent_dce : register(u0);

vector<float16_t, 2> atanh_5bf88d() {
  vector<float16_t, 2> arg_0 = (float16_t(0.5h)).xx;
  vector<float16_t, 2> res = tint_atanh(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store<vector<float16_t, 2> >(0u, atanh_5bf88d());
  return;
}
//
// compute_main
//
vector<float16_t, 2> tint_atanh(vector<float16_t, 2> x) {
  return (log(((float16_t(1.0h) + x) / (float16_t(1.0h) - x))) * float16_t(0.5h));
}

RWByteAddressBuffer prevent_dce : register(u0);

vector<float16_t, 2> atanh_5bf88d() {
  vector<float16_t, 2> arg_0 = (float16_t(0.5h)).xx;
  vector<float16_t, 2> res = tint_atanh(arg_0);
  return res;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store<vector<float16_t, 2> >(0u, atanh_5bf88d());
  return;
}
//
// vertex_main
//
vector<float16_t, 2> tint_atanh(vector<float16_t, 2> x) {
  return (log(((float16_t(1.0h) + x) / (float16_t(1.0h) - x))) * float16_t(0.5h));
}

vector<float16_t, 2> atanh_5bf88d() {
  vector<float16_t, 2> arg_0 = (float16_t(0.5h)).xx;
  vector<float16_t, 2> res = tint_atanh(arg_0);
  return res;
}

struct VertexOutput {
  float4 pos;
  vector<float16_t, 2> prevent_dce;
};
struct tint_symbol_1 {
  nointerpolation vector<float16_t, 2> prevent_dce : TEXCOORD0;
  float4 pos : SV_Position;
};

VertexOutput vertex_main_inner() {
  VertexOutput tint_symbol = (VertexOutput)0;
  tint_symbol.pos = (0.0f).xxxx;
  tint_symbol.prevent_dce = atanh_5bf88d();
  return tint_symbol;
}

tint_symbol_1 vertex_main() {
  VertexOutput inner_result = vertex_main_inner();
  tint_symbol_1 wrapper_result = (tint_symbol_1)0;
  wrapper_result.pos = inner_result.pos;
  wrapper_result.prevent_dce = inner_result.prevent_dce;
  return wrapper_result;
}
