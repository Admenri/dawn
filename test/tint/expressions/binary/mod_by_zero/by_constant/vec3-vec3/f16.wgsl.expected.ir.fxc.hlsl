SKIP: INVALID


[numthreads(1, 1, 1)]
void f() {
  vector<float16_t, 3> a = vector<float16_t, 3>(float16_t(1.0h), float16_t(2.0h), float16_t(3.0h));
  vector<float16_t, 3> b = vector<float16_t, 3>(float16_t(0.0h), float16_t(5.0h), float16_t(0.0h));
  vector<float16_t, 3> v = (a / b);
  vector<float16_t, 3> v_1 = floor(v);
  vector<float16_t, 3> r = ((a - (((v < (float16_t(0.0h)).xxx)) ? (ceil(v)) : (v_1))) * b);
}

FXC validation failure:
C:\src\dawn\Shader@0x0000019069F7DC80(4,10-18): error X3000: syntax error: unexpected token 'float16_t'
C:\src\dawn\Shader@0x0000019069F7DC80(5,10-18): error X3000: syntax error: unexpected token 'float16_t'
C:\src\dawn\Shader@0x0000019069F7DC80(6,10-18): error X3000: syntax error: unexpected token 'float16_t'
C:\src\dawn\Shader@0x0000019069F7DC80(7,10-18): error X3000: syntax error: unexpected token 'float16_t'
C:\src\dawn\Shader@0x0000019069F7DC80(8,10-18): error X3000: syntax error: unexpected token 'float16_t'

