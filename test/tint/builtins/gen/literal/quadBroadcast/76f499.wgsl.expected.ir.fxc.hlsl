SKIP: FAILED


RWByteAddressBuffer prevent_dce : register(u0);
int4 quadBroadcast_76f499() {
  int4 res = QuadReadLaneAt((1).xxxx, 1);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(quadBroadcast_76f499()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(quadBroadcast_76f499()));
}

FXC validation failure:
C:\src\dawn\Shader@0x0000027A4F83A420(4,14-40): error X3004: undeclared identifier 'QuadReadLaneAt'

