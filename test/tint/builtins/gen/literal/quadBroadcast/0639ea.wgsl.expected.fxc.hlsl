SKIP: FAILED

RWByteAddressBuffer prevent_dce : register(u0);

int quadBroadcast_0639ea() {
  int res = QuadReadLaneAt(1, 1u);
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(quadBroadcast_0639ea()));
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(quadBroadcast_0639ea()));
  return;
}
FXC validation failure:
C:\src\dawn\Shader@0x000001FA88846D30(4,13-33): error X3004: undeclared identifier 'QuadReadLaneAt'

