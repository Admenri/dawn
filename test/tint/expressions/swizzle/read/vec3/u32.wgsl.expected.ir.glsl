#version 310 es

struct S {
  uvec3 v;
};

S P = S(uvec3(0u));
void f() {
  uvec3 v = P.v;
  uint x = P.v.x;
  uint y = P.v.y;
  uint z = P.v.z;
  uvec2 xx = P.v.xx;
  uvec2 xy = P.v.xy;
  uvec2 xz = P.v.xz;
  uvec2 yx = P.v.yx;
  uvec2 yy = P.v.yy;
  uvec2 yz = P.v.yz;
  uvec2 zx = P.v.zx;
  uvec2 zy = P.v.zy;
  uvec2 zz = P.v.zz;
  uvec3 xxx = P.v.xxx;
  uvec3 xxy = P.v.xxy;
  uvec3 xxz = P.v.xxz;
  uvec3 xyx = P.v.xyx;
  uvec3 xyy = P.v.xyy;
  uvec3 xyz = P.v.xyz;
  uvec3 xzx = P.v.xzx;
  uvec3 xzy = P.v.xzy;
  uvec3 xzz = P.v.xzz;
  uvec3 yxx = P.v.yxx;
  uvec3 yxy = P.v.yxy;
  uvec3 yxz = P.v.yxz;
  uvec3 yyx = P.v.yyx;
  uvec3 yyy = P.v.yyy;
  uvec3 yyz = P.v.yyz;
  uvec3 yzx = P.v.yzx;
  uvec3 yzy = P.v.yzy;
  uvec3 yzz = P.v.yzz;
  uvec3 zxx = P.v.zxx;
  uvec3 zxy = P.v.zxy;
  uvec3 zxz = P.v.zxz;
  uvec3 zyx = P.v.zyx;
  uvec3 zyy = P.v.zyy;
  uvec3 zyz = P.v.zyz;
  uvec3 zzx = P.v.zzx;
  uvec3 zzy = P.v.zzy;
  uvec3 zzz = P.v.zzz;
  uvec4 xxxx = P.v.xxxx;
  uvec4 xxxy = P.v.xxxy;
  uvec4 xxxz = P.v.xxxz;
  uvec4 xxyx = P.v.xxyx;
  uvec4 xxyy = P.v.xxyy;
  uvec4 xxyz = P.v.xxyz;
  uvec4 xxzx = P.v.xxzx;
  uvec4 xxzy = P.v.xxzy;
  uvec4 xxzz = P.v.xxzz;
  uvec4 xyxx = P.v.xyxx;
  uvec4 xyxy = P.v.xyxy;
  uvec4 xyxz = P.v.xyxz;
  uvec4 xyyx = P.v.xyyx;
  uvec4 xyyy = P.v.xyyy;
  uvec4 xyyz = P.v.xyyz;
  uvec4 xyzx = P.v.xyzx;
  uvec4 xyzy = P.v.xyzy;
  uvec4 xyzz = P.v.xyzz;
  uvec4 xzxx = P.v.xzxx;
  uvec4 xzxy = P.v.xzxy;
  uvec4 xzxz = P.v.xzxz;
  uvec4 xzyx = P.v.xzyx;
  uvec4 xzyy = P.v.xzyy;
  uvec4 xzyz = P.v.xzyz;
  uvec4 xzzx = P.v.xzzx;
  uvec4 xzzy = P.v.xzzy;
  uvec4 xzzz = P.v.xzzz;
  uvec4 yxxx = P.v.yxxx;
  uvec4 yxxy = P.v.yxxy;
  uvec4 yxxz = P.v.yxxz;
  uvec4 yxyx = P.v.yxyx;
  uvec4 yxyy = P.v.yxyy;
  uvec4 yxyz = P.v.yxyz;
  uvec4 yxzx = P.v.yxzx;
  uvec4 yxzy = P.v.yxzy;
  uvec4 yxzz = P.v.yxzz;
  uvec4 yyxx = P.v.yyxx;
  uvec4 yyxy = P.v.yyxy;
  uvec4 yyxz = P.v.yyxz;
  uvec4 yyyx = P.v.yyyx;
  uvec4 yyyy = P.v.yyyy;
  uvec4 yyyz = P.v.yyyz;
  uvec4 yyzx = P.v.yyzx;
  uvec4 yyzy = P.v.yyzy;
  uvec4 yyzz = P.v.yyzz;
  uvec4 yzxx = P.v.yzxx;
  uvec4 yzxy = P.v.yzxy;
  uvec4 yzxz = P.v.yzxz;
  uvec4 yzyx = P.v.yzyx;
  uvec4 yzyy = P.v.yzyy;
  uvec4 yzyz = P.v.yzyz;
  uvec4 yzzx = P.v.yzzx;
  uvec4 yzzy = P.v.yzzy;
  uvec4 yzzz = P.v.yzzz;
  uvec4 zxxx = P.v.zxxx;
  uvec4 zxxy = P.v.zxxy;
  uvec4 zxxz = P.v.zxxz;
  uvec4 zxyx = P.v.zxyx;
  uvec4 zxyy = P.v.zxyy;
  uvec4 zxyz = P.v.zxyz;
  uvec4 zxzx = P.v.zxzx;
  uvec4 zxzy = P.v.zxzy;
  uvec4 zxzz = P.v.zxzz;
  uvec4 zyxx = P.v.zyxx;
  uvec4 zyxy = P.v.zyxy;
  uvec4 zyxz = P.v.zyxz;
  uvec4 zyyx = P.v.zyyx;
  uvec4 zyyy = P.v.zyyy;
  uvec4 zyyz = P.v.zyyz;
  uvec4 zyzx = P.v.zyzx;
  uvec4 zyzy = P.v.zyzy;
  uvec4 zyzz = P.v.zyzz;
  uvec4 zzxx = P.v.zzxx;
  uvec4 zzxy = P.v.zzxy;
  uvec4 zzxz = P.v.zzxz;
  uvec4 zzyx = P.v.zzyx;
  uvec4 zzyy = P.v.zzyy;
  uvec4 zzyz = P.v.zzyz;
  uvec4 zzzx = P.v.zzzx;
  uvec4 zzzy = P.v.zzzy;
  uvec4 zzzz = P.v.zzzz;
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
}
