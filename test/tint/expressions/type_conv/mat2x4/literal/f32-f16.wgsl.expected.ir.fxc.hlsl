SKIP: INVALID


static matrix<float16_t, 2, 4> u = matrix<float16_t, 2, 4>(vector<float16_t, 4>(float16_t(1.0h), float16_t(2.0h), float16_t(3.0h), float16_t(4.0h)), vector<float16_t, 4>(float16_t(5.0h), float16_t(6.0h), float16_t(7.0h), float16_t(8.0h)));
[numthreads(1, 1, 1)]
void unused_entry_point() {
}

FXC validation failure:
C:\src\dawn\Shader@0x000001DCF81EB0E0(2,15-23): error X3000: syntax error: unexpected token 'float16_t'

