SKIP: FAILED

struct In {
  float4 pos;
  float4 uv;
  float4 fbf;
};

struct f_inputs {
  float4 In_fbf;
  float4 In_uv : TEXCOORD0;
  float4 In_pos : SV_Position;
};


void g(float a, float b, float c) {
}

void f_inner(In tint_symbol) {
  g(tint_symbol.pos[0u], tint_symbol.uv[0u], tint_symbol.fbf[1u]);
}

void f(f_inputs inputs) {
  In v = {float4(inputs.In_pos.xyz, (1.0f / inputs.In_pos[3u])), inputs.In_uv, inputs.In_fbf};
  f_inner(v);
}

FXC validation failure:
C:\src\dawn\Shader@0x000001A8DE766710(21,17-22): error X3502: 'f': input parameter 'inputs' missing semantics

