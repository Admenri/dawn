SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

int quadBroadcast_f9d579() {
  int arg_0 = 1;
  int res = QuadReadLaneAt(arg_0, 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(quadBroadcast_f9d579()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(quadBroadcast_f9d579()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000002594DDA9B90(5,13-36): error X3004: undeclared identifier 'QuadReadLaneAt'

