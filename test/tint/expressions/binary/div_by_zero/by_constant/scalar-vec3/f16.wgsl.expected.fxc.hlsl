SKIP: FAILED

[numthreads(1, 1, 1)]
void f() {
  float16_t a = float16_t(4.0h);
  vector<float16_t, 3> b = vector<float16_t, 3>(float16_t(0.0h), float16_t(2.0h), float16_t(0.0h));
  vector<float16_t, 3> r = (a / b);
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x00000286CA54FAC0(3,3-11): error X3000: unrecognized identifier 'float16_t'
C:\src\dawn\Shader@0x00000286CA54FAC0(3,13): error X3000: unrecognized identifier 'a'

