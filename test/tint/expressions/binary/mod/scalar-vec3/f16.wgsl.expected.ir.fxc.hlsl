SKIP: FAILED


[numthreads(1, 1, 1)]
void f() {
  float16_t a = float16_t(4.0h);
  vector<float16_t, 3> b = vector<float16_t, 3>(float16_t(1.0h), float16_t(2.0h), float16_t(3.0h));
  vector<float16_t, 3> v = (a / b);
  vector<float16_t, 3> v_1 = floor(v);
  vector<float16_t, 3> r = ((a - (((v < (float16_t(0.0h)).xxx)) ? (ceil(v)) : (v_1))) * b);
}

FXC validation failure:
C:\src\dawn\Shader@0x000001EC0CDDFD60(4,3-11): error X3000: unrecognized identifier 'float16_t'
C:\src\dawn\Shader@0x000001EC0CDDFD60(4,13): error X3000: unrecognized identifier 'a'

