SKIP: INVALID


static uint3 localId = (0u).xxx;
static uint localIndex = 0u;
static uint3 globalId = (0u).xxx;
static uint3 numWorkgroups = (0u).xxx;
static uint3 workgroupId = (0u).xxx;
uint globalId2Index() {
  return globalId.x;
}

[numthreads(1, 1, 1)]
void main() {
  vector<float16_t, 4> a = (float16_t(0.0h)).xxxx;
  float16_t b = float16_t(1.0h);
  a[0] = (a.x + b);
}

FXC validation failure:
C:\src\dawn\Shader@0x00000238C9323FD0(13,10-18): error X3000: syntax error: unexpected token 'float16_t'
C:\src\dawn\Shader@0x00000238C9323FD0(14,3-11): error X3000: unrecognized identifier 'float16_t'
C:\src\dawn\Shader@0x00000238C9323FD0(14,13): error X3000: unrecognized identifier 'b'

