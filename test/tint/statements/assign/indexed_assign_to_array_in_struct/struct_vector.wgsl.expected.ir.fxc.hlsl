SKIP: FAILED

struct OuterS {
  float3 v1;
};


cbuffer cbuffer_uniforms : register(b4, space1) {
  uint4 uniforms[1];
};
[numthreads(1, 1, 1)]
void main() {
  OuterS s1 = (OuterS)0;
  s1.v1[uniforms[0u].x] = 1.0f;
}

FXC validation failure:
C:\src\dawn\Shader@0x0000024C292020F0(12,3-23): error X3500: array reference cannot be used as an l-value; not natively addressable

