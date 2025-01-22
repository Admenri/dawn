// Copyright 2024 The Dawn & Tint Authors
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "src/tint/lang/spirv/reader/lower/builtins.h"

#include <string>

#include "src/tint/lang/core/ir/transform/helper_test.h"
#include "src/tint/lang/spirv/ir/builtin_call.h"

namespace tint::spirv::reader::lower {
namespace {

using namespace tint::core::fluent_types;     // NOLINT
using namespace tint::core::number_suffixes;  // NOLINT

using SpirvParser_BuiltinsTest = core::ir::transform::TransformTest;

TEST_F(SpirvParser_BuiltinsTest, Normalize_Scalar) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.Call<spirv::ir::BuiltinCall>(ty.f32(), spirv::BuiltinFn::kNormalize, 10_f);
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:f32 = spirv.normalize 10.0f
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:f32 = sign 10.0f
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, Normalize_Vector) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.Call<spirv::ir::BuiltinCall>(ty.vec2<f32>(), spirv::BuiltinFn::kNormalize,
                                       b.Splat(ty.vec2<f32>(), 10_f));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:vec2<f32> = spirv.normalize vec2<f32>(10.0f)
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:vec2<f32> = normalize vec2<f32>(10.0f)
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, Inverse_Mat2x2f) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.Call<spirv::ir::BuiltinCall>(ty.mat2x2<f32>(), spirv::BuiltinFn::kInverse,
                                       b.Construct(ty.mat2x2<f32>(), b.Splat(ty.vec2<f32>(), 10_f),
                                                   b.Splat(ty.vec2<f32>(), 20_f)));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:mat2x2<f32> = construct vec2<f32>(10.0f), vec2<f32>(20.0f)
    %3:mat2x2<f32> = spirv.inverse %2
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:mat2x2<f32> = construct vec2<f32>(10.0f), vec2<f32>(20.0f)
    %3:f32 = determinant %2
    %4:f32 = div 1.0f, %3
    %5:f32 = negation %4
    %6:f32 = access %2, 0u, 0u
    %7:f32 = access %2, 0u, 1u
    %8:f32 = access %2, 1u, 0u
    %9:f32 = access %2, 1u, 1u
    %10:f32 = mul %4, %9
    %11:f32 = mul %5, %7
    %12:f32 = mul %5, %8
    %13:f32 = mul %4, %6
    %14:vec2<f32> = construct %10, %11
    %15:vec2<f32> = construct %12, %13
    %16:mat2x2<f32> = construct %14, %15
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, Inverse_Mat2x2h) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.Call<spirv::ir::BuiltinCall>(ty.mat2x2<f16>(), spirv::BuiltinFn::kInverse,
                                       b.Construct(ty.mat2x2<f16>(), b.Splat(ty.vec2<f16>(), 10_h),
                                                   b.Splat(ty.vec2<f16>(), 20_h)));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:mat2x2<f16> = construct vec2<f16>(10.0h), vec2<f16>(20.0h)
    %3:mat2x2<f16> = spirv.inverse %2
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:mat2x2<f16> = construct vec2<f16>(10.0h), vec2<f16>(20.0h)
    %3:f16 = determinant %2
    %4:f16 = div 1.0h, %3
    %5:f16 = negation %4
    %6:f16 = access %2, 0u, 0u
    %7:f16 = access %2, 0u, 1u
    %8:f16 = access %2, 1u, 0u
    %9:f16 = access %2, 1u, 1u
    %10:f16 = mul %4, %9
    %11:f16 = mul %5, %7
    %12:f16 = mul %5, %8
    %13:f16 = mul %4, %6
    %14:vec2<f16> = construct %10, %11
    %15:vec2<f16> = construct %12, %13
    %16:mat2x2<f16> = construct %14, %15
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, Inverse_Mat3x3f) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.Call<spirv::ir::BuiltinCall>(
            ty.mat3x3<f32>(), spirv::BuiltinFn::kInverse,
            b.Construct(ty.mat3x3<f32>(), b.Splat(ty.vec3<f32>(), 10_f),
                        b.Splat(ty.vec3<f32>(), 20_f), b.Splat(ty.vec3<f32>(), 30_f)));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:mat3x3<f32> = construct vec3<f32>(10.0f), vec3<f32>(20.0f), vec3<f32>(30.0f)
    %3:mat3x3<f32> = spirv.inverse %2
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:mat3x3<f32> = construct vec3<f32>(10.0f), vec3<f32>(20.0f), vec3<f32>(30.0f)
    %3:f32 = determinant %2
    %4:f32 = div 1.0f, %3
    %5:f32 = access %2, 0u, 0u
    %6:f32 = access %2, 0u, 1u
    %7:f32 = access %2, 0u, 2u
    %8:f32 = access %2, 1u, 0u
    %9:f32 = access %2, 1u, 1u
    %10:f32 = access %2, 1u, 2u
    %11:f32 = access %2, 2u, 0u
    %12:f32 = access %2, 2u, 1u
    %13:f32 = access %2, 2u, 2u
    %14:f32 = mul %9, %13
    %15:f32 = mul %10, %12
    %16:f32 = sub %14, %15
    %17:f32 = mul %7, %12
    %18:f32 = mul %6, %13
    %19:f32 = sub %17, %18
    %20:f32 = mul %6, %10
    %21:f32 = mul %7, %9
    %22:f32 = sub %20, %21
    %23:f32 = mul %10, %11
    %24:f32 = mul %8, %13
    %25:f32 = sub %23, %24
    %26:f32 = mul %5, %13
    %27:f32 = mul %7, %11
    %28:f32 = sub %26, %27
    %29:f32 = mul %7, %8
    %30:f32 = mul %5, %10
    %31:f32 = sub %29, %30
    %32:f32 = mul %8, %12
    %33:f32 = mul %9, %11
    %34:f32 = sub %32, %33
    %35:f32 = mul %6, %11
    %36:f32 = mul %5, %12
    %37:f32 = sub %35, %36
    %38:f32 = mul %5, %9
    %39:f32 = mul %6, %8
    %40:f32 = sub %38, %39
    %41:vec3<f32> = construct %16, %19, %22
    %42:vec3<f32> = construct %25, %28, %31
    %43:vec3<f32> = construct %34, %37, %40
    %44:mat3x3<f32> = construct %41, %42, %43
    %45:mat3x3<f32> = mul %4, %44
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, Inverse_Mat3x3h) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.Call<spirv::ir::BuiltinCall>(
            ty.mat3x3<f16>(), spirv::BuiltinFn::kInverse,
            b.Construct(ty.mat3x3<f16>(), b.Splat(ty.vec3<f16>(), 10_h),
                        b.Splat(ty.vec3<f16>(), 20_h), b.Splat(ty.vec3<f16>(), 30_h)));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:mat3x3<f16> = construct vec3<f16>(10.0h), vec3<f16>(20.0h), vec3<f16>(30.0h)
    %3:mat3x3<f16> = spirv.inverse %2
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:mat3x3<f16> = construct vec3<f16>(10.0h), vec3<f16>(20.0h), vec3<f16>(30.0h)
    %3:f16 = determinant %2
    %4:f16 = div 1.0h, %3
    %5:f16 = access %2, 0u, 0u
    %6:f16 = access %2, 0u, 1u
    %7:f16 = access %2, 0u, 2u
    %8:f16 = access %2, 1u, 0u
    %9:f16 = access %2, 1u, 1u
    %10:f16 = access %2, 1u, 2u
    %11:f16 = access %2, 2u, 0u
    %12:f16 = access %2, 2u, 1u
    %13:f16 = access %2, 2u, 2u
    %14:f16 = mul %9, %13
    %15:f16 = mul %10, %12
    %16:f16 = sub %14, %15
    %17:f16 = mul %7, %12
    %18:f16 = mul %6, %13
    %19:f16 = sub %17, %18
    %20:f16 = mul %6, %10
    %21:f16 = mul %7, %9
    %22:f16 = sub %20, %21
    %23:f16 = mul %10, %11
    %24:f16 = mul %8, %13
    %25:f16 = sub %23, %24
    %26:f16 = mul %5, %13
    %27:f16 = mul %7, %11
    %28:f16 = sub %26, %27
    %29:f16 = mul %7, %8
    %30:f16 = mul %5, %10
    %31:f16 = sub %29, %30
    %32:f16 = mul %8, %12
    %33:f16 = mul %9, %11
    %34:f16 = sub %32, %33
    %35:f16 = mul %6, %11
    %36:f16 = mul %5, %12
    %37:f16 = sub %35, %36
    %38:f16 = mul %5, %9
    %39:f16 = mul %6, %8
    %40:f16 = sub %38, %39
    %41:vec3<f16> = construct %16, %19, %22
    %42:vec3<f16> = construct %25, %28, %31
    %43:vec3<f16> = construct %34, %37, %40
    %44:mat3x3<f16> = construct %41, %42, %43
    %45:mat3x3<f16> = mul %4, %44
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, Inverse_Mat4x4f) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.Call<spirv::ir::BuiltinCall>(
            ty.mat4x4<f32>(), spirv::BuiltinFn::kInverse,
            b.Construct(ty.mat4x4<f32>(), b.Splat(ty.vec4<f32>(), 10_f),
                        b.Splat(ty.vec4<f32>(), 20_f), b.Splat(ty.vec4<f32>(), 30_f),
                        b.Splat(ty.vec4<f32>(), 40_f)));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:mat4x4<f32> = construct vec4<f32>(10.0f), vec4<f32>(20.0f), vec4<f32>(30.0f), vec4<f32>(40.0f)
    %3:mat4x4<f32> = spirv.inverse %2
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:mat4x4<f32> = construct vec4<f32>(10.0f), vec4<f32>(20.0f), vec4<f32>(30.0f), vec4<f32>(40.0f)
    %3:f32 = determinant %2
    %4:f32 = div 1.0f, %3
    %5:f32 = access %2, 0u, 0u
    %6:f32 = access %2, 0u, 1u
    %7:f32 = access %2, 0u, 2u
    %8:f32 = access %2, 0u, 3u
    %9:f32 = access %2, 1u, 0u
    %10:f32 = access %2, 1u, 1u
    %11:f32 = access %2, 1u, 2u
    %12:f32 = access %2, 1u, 3u
    %13:f32 = access %2, 2u, 0u
    %14:f32 = access %2, 2u, 1u
    %15:f32 = access %2, 2u, 2u
    %16:f32 = access %2, 2u, 3u
    %17:f32 = access %2, 3u, 0u
    %18:f32 = access %2, 3u, 1u
    %19:f32 = access %2, 3u, 2u
    %20:f32 = access %2, 3u, 3u
    %21:f32 = mul %15, %20
    %22:f32 = mul %16, %19
    %23:f32 = sub %21, %22
    %24:f32 = mul %14, %20
    %25:f32 = mul %16, %18
    %26:f32 = sub %24, %25
    %27:f32 = mul %14, %19
    %28:f32 = mul %15, %18
    %29:f32 = sub %27, %28
    %30:f32 = mul %11, %20
    %31:f32 = mul %12, %19
    %32:f32 = sub %30, %31
    %33:f32 = mul %10, %20
    %34:f32 = mul %12, %18
    %35:f32 = sub %33, %34
    %36:f32 = mul %10, %19
    %37:f32 = mul %11, %18
    %38:f32 = sub %36, %37
    %39:f32 = mul %11, %16
    %40:f32 = mul %12, %15
    %41:f32 = sub %39, %40
    %42:f32 = mul %10, %16
    %43:f32 = mul %12, %14
    %44:f32 = sub %42, %43
    %45:f32 = mul %10, %15
    %46:f32 = mul %11, %14
    %47:f32 = sub %45, %46
    %48:f32 = mul %13, %20
    %49:f32 = mul %16, %17
    %50:f32 = sub %48, %49
    %51:f32 = mul %13, %19
    %52:f32 = mul %15, %17
    %53:f32 = sub %51, %52
    %54:f32 = mul %9, %20
    %55:f32 = mul %12, %17
    %56:f32 = sub %54, %55
    %57:f32 = mul %9, %19
    %58:f32 = mul %11, %17
    %59:f32 = sub %57, %58
    %60:f32 = mul %9, %16
    %61:f32 = mul %12, %13
    %62:f32 = sub %60, %61
    %63:f32 = mul %9, %15
    %64:f32 = mul %11, %13
    %65:f32 = sub %63, %64
    %66:f32 = mul %13, %18
    %67:f32 = mul %14, %17
    %68:f32 = sub %66, %67
    %69:f32 = mul %9, %18
    %70:f32 = mul %10, %17
    %71:f32 = sub %69, %70
    %72:f32 = mul %9, %14
    %73:f32 = mul %10, %13
    %74:f32 = sub %72, %73
    %75:f32 = negation %6
    %76:f32 = mul %10, %23
    %77:f32 = mul %11, %26
    %78:f32 = mul %12, %29
    %79:f32 = sub %76, %77
    %80:f32 = add %79, %78
    %81:f32 = mul %75, %23
    %82:f32 = mul %7, %26
    %83:f32 = mul %8, %29
    %84:f32 = add %81, %82
    %85:f32 = sub %84, %83
    %86:f32 = mul %6, %32
    %87:f32 = mul %7, %35
    %88:f32 = mul %8, %38
    %89:f32 = sub %86, %87
    %90:f32 = add %89, %88
    %91:f32 = mul %75, %41
    %92:f32 = mul %7, %44
    %93:f32 = mul %8, %47
    %94:f32 = add %91, %92
    %95:f32 = sub %94, %93
    %96:f32 = negation %9
    %97:f32 = negation %5
    %98:f32 = mul %96, %23
    %99:f32 = mul %11, %50
    %100:f32 = mul %12, %53
    %101:f32 = add %98, %99
    %102:f32 = sub %101, %100
    %103:f32 = mul %5, %23
    %104:f32 = mul %7, %50
    %105:f32 = mul %8, %53
    %106:f32 = sub %103, %104
    %107:f32 = add %106, %105
    %108:f32 = mul %97, %32
    %109:f32 = mul %7, %56
    %110:f32 = mul %8, %59
    %111:f32 = add %108, %109
    %112:f32 = sub %111, %110
    %113:f32 = mul %5, %41
    %114:f32 = mul %7, %62
    %115:f32 = mul %8, %65
    %116:f32 = sub %113, %114
    %117:f32 = add %116, %115
    %118:f32 = mul %9, %26
    %119:f32 = mul %10, %50
    %120:f32 = mul %12, %68
    %121:f32 = sub %118, %119
    %122:f32 = add %121, %120
    %123:f32 = mul %97, %26
    %124:f32 = mul %6, %50
    %125:f32 = mul %8, %68
    %126:f32 = add %123, %124
    %127:f32 = sub %126, %125
    %128:f32 = mul %5, %35
    %129:f32 = mul %6, %56
    %130:f32 = mul %8, %71
    %131:f32 = sub %128, %129
    %132:f32 = add %131, %130
    %133:f32 = mul %97, %44
    %134:f32 = mul %6, %62
    %135:f32 = mul %8, %74
    %136:f32 = add %133, %134
    %137:f32 = sub %136, %135
    %138:f32 = mul %96, %29
    %139:f32 = mul %10, %53
    %140:f32 = mul %11, %68
    %141:f32 = add %138, %139
    %142:f32 = sub %141, %140
    %143:f32 = mul %5, %29
    %144:f32 = mul %6, %53
    %145:f32 = mul %7, %68
    %146:f32 = sub %143, %144
    %147:f32 = add %146, %145
    %148:f32 = mul %97, %38
    %149:f32 = mul %6, %59
    %150:f32 = mul %7, %71
    %151:f32 = add %148, %149
    %152:f32 = sub %151, %150
    %153:f32 = mul %5, %47
    %154:f32 = mul %6, %65
    %155:f32 = mul %7, %74
    %156:f32 = sub %153, %154
    %157:f32 = add %156, %155
    %158:vec3<f32> = construct %80, %85, %90, %95
    %159:vec3<f32> = construct %102, %107, %112, %117
    %160:vec3<f32> = construct %122, %127, %132, %137
    %161:vec3<f32> = construct %142, %147, %152, %157
    %162:mat4x4<f32> = construct %158, %159, %160, %161
    %163:mat4x4<f32> = mul %4, %162
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, Inverse_Mat4x4h) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.Call<spirv::ir::BuiltinCall>(
            ty.mat4x4<f16>(), spirv::BuiltinFn::kInverse,
            b.Construct(ty.mat4x4<f16>(), b.Splat(ty.vec4<f16>(), 10_h),
                        b.Splat(ty.vec4<f16>(), 20_h), b.Splat(ty.vec4<f16>(), 30_h),
                        b.Splat(ty.vec4<f16>(), 40_h)));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:mat4x4<f16> = construct vec4<f16>(10.0h), vec4<f16>(20.0h), vec4<f16>(30.0h), vec4<f16>(40.0h)
    %3:mat4x4<f16> = spirv.inverse %2
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:mat4x4<f16> = construct vec4<f16>(10.0h), vec4<f16>(20.0h), vec4<f16>(30.0h), vec4<f16>(40.0h)
    %3:f16 = determinant %2
    %4:f16 = div 1.0h, %3
    %5:f16 = access %2, 0u, 0u
    %6:f16 = access %2, 0u, 1u
    %7:f16 = access %2, 0u, 2u
    %8:f16 = access %2, 0u, 3u
    %9:f16 = access %2, 1u, 0u
    %10:f16 = access %2, 1u, 1u
    %11:f16 = access %2, 1u, 2u
    %12:f16 = access %2, 1u, 3u
    %13:f16 = access %2, 2u, 0u
    %14:f16 = access %2, 2u, 1u
    %15:f16 = access %2, 2u, 2u
    %16:f16 = access %2, 2u, 3u
    %17:f16 = access %2, 3u, 0u
    %18:f16 = access %2, 3u, 1u
    %19:f16 = access %2, 3u, 2u
    %20:f16 = access %2, 3u, 3u
    %21:f16 = mul %15, %20
    %22:f16 = mul %16, %19
    %23:f16 = sub %21, %22
    %24:f16 = mul %14, %20
    %25:f16 = mul %16, %18
    %26:f16 = sub %24, %25
    %27:f16 = mul %14, %19
    %28:f16 = mul %15, %18
    %29:f16 = sub %27, %28
    %30:f16 = mul %11, %20
    %31:f16 = mul %12, %19
    %32:f16 = sub %30, %31
    %33:f16 = mul %10, %20
    %34:f16 = mul %12, %18
    %35:f16 = sub %33, %34
    %36:f16 = mul %10, %19
    %37:f16 = mul %11, %18
    %38:f16 = sub %36, %37
    %39:f16 = mul %11, %16
    %40:f16 = mul %12, %15
    %41:f16 = sub %39, %40
    %42:f16 = mul %10, %16
    %43:f16 = mul %12, %14
    %44:f16 = sub %42, %43
    %45:f16 = mul %10, %15
    %46:f16 = mul %11, %14
    %47:f16 = sub %45, %46
    %48:f16 = mul %13, %20
    %49:f16 = mul %16, %17
    %50:f16 = sub %48, %49
    %51:f16 = mul %13, %19
    %52:f16 = mul %15, %17
    %53:f16 = sub %51, %52
    %54:f16 = mul %9, %20
    %55:f16 = mul %12, %17
    %56:f16 = sub %54, %55
    %57:f16 = mul %9, %19
    %58:f16 = mul %11, %17
    %59:f16 = sub %57, %58
    %60:f16 = mul %9, %16
    %61:f16 = mul %12, %13
    %62:f16 = sub %60, %61
    %63:f16 = mul %9, %15
    %64:f16 = mul %11, %13
    %65:f16 = sub %63, %64
    %66:f16 = mul %13, %18
    %67:f16 = mul %14, %17
    %68:f16 = sub %66, %67
    %69:f16 = mul %9, %18
    %70:f16 = mul %10, %17
    %71:f16 = sub %69, %70
    %72:f16 = mul %9, %14
    %73:f16 = mul %10, %13
    %74:f16 = sub %72, %73
    %75:f16 = negation %6
    %76:f16 = mul %10, %23
    %77:f16 = mul %11, %26
    %78:f16 = mul %12, %29
    %79:f16 = sub %76, %77
    %80:f16 = add %79, %78
    %81:f16 = mul %75, %23
    %82:f16 = mul %7, %26
    %83:f16 = mul %8, %29
    %84:f16 = add %81, %82
    %85:f16 = sub %84, %83
    %86:f16 = mul %6, %32
    %87:f16 = mul %7, %35
    %88:f16 = mul %8, %38
    %89:f16 = sub %86, %87
    %90:f16 = add %89, %88
    %91:f16 = mul %75, %41
    %92:f16 = mul %7, %44
    %93:f16 = mul %8, %47
    %94:f16 = add %91, %92
    %95:f16 = sub %94, %93
    %96:f16 = negation %9
    %97:f16 = negation %5
    %98:f16 = mul %96, %23
    %99:f16 = mul %11, %50
    %100:f16 = mul %12, %53
    %101:f16 = add %98, %99
    %102:f16 = sub %101, %100
    %103:f16 = mul %5, %23
    %104:f16 = mul %7, %50
    %105:f16 = mul %8, %53
    %106:f16 = sub %103, %104
    %107:f16 = add %106, %105
    %108:f16 = mul %97, %32
    %109:f16 = mul %7, %56
    %110:f16 = mul %8, %59
    %111:f16 = add %108, %109
    %112:f16 = sub %111, %110
    %113:f16 = mul %5, %41
    %114:f16 = mul %7, %62
    %115:f16 = mul %8, %65
    %116:f16 = sub %113, %114
    %117:f16 = add %116, %115
    %118:f16 = mul %9, %26
    %119:f16 = mul %10, %50
    %120:f16 = mul %12, %68
    %121:f16 = sub %118, %119
    %122:f16 = add %121, %120
    %123:f16 = mul %97, %26
    %124:f16 = mul %6, %50
    %125:f16 = mul %8, %68
    %126:f16 = add %123, %124
    %127:f16 = sub %126, %125
    %128:f16 = mul %5, %35
    %129:f16 = mul %6, %56
    %130:f16 = mul %8, %71
    %131:f16 = sub %128, %129
    %132:f16 = add %131, %130
    %133:f16 = mul %97, %44
    %134:f16 = mul %6, %62
    %135:f16 = mul %8, %74
    %136:f16 = add %133, %134
    %137:f16 = sub %136, %135
    %138:f16 = mul %96, %29
    %139:f16 = mul %10, %53
    %140:f16 = mul %11, %68
    %141:f16 = add %138, %139
    %142:f16 = sub %141, %140
    %143:f16 = mul %5, %29
    %144:f16 = mul %6, %53
    %145:f16 = mul %7, %68
    %146:f16 = sub %143, %144
    %147:f16 = add %146, %145
    %148:f16 = mul %97, %38
    %149:f16 = mul %6, %59
    %150:f16 = mul %7, %71
    %151:f16 = add %148, %149
    %152:f16 = sub %151, %150
    %153:f16 = mul %5, %47
    %154:f16 = mul %6, %65
    %155:f16 = mul %7, %74
    %156:f16 = sub %153, %154
    %157:f16 = add %156, %155
    %158:vec3<f16> = construct %80, %85, %90, %95
    %159:vec3<f16> = construct %102, %107, %112, %117
    %160:vec3<f16> = construct %122, %127, %132, %137
    %161:vec3<f16> = construct %142, %147, %152, %157
    %162:mat4x4<f16> = construct %158, %159, %160, %161
    %163:mat4x4<f16> = mul %4, %162
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, SSign_Scalar_UnsignedArg) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.i32(), spirv::BuiltinFn::kSign,
                                               Vector<const core::type::Type*, 1>{ty.i32()},
                                               b.Constant(10_u));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = spirv.sign<i32> 10u
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = bitcast 10u
    %3:i32 = sign %2
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, SSign_Scalar_UnsignedResult) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.u32(), spirv::BuiltinFn::kSign,
                                               Vector<const core::type::Type*, 1>{ty.u32()},
                                               b.Constant(10_i));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:u32 = spirv.sign<u32> 10i
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = sign 10i
    %3:u32 = bitcast %2
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, SSign_Scalar_UnsignedArgAndResult) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.u32(), spirv::BuiltinFn::kSign,
                                               Vector<const core::type::Type*, 1>{ty.u32()},
                                               b.Constant(10_u));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:u32 = spirv.sign<u32> 10u
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = bitcast 10u
    %3:i32 = sign %2
    %4:u32 = bitcast %3
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, SSign_Scalar_SignedArgAndResult) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.i32(), spirv::BuiltinFn::kSign,
                                               Vector<const core::type::Type*, 1>{ty.i32()},
                                               b.Constant(10_i));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = spirv.sign<i32> 10i
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = sign 10i
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, SSign_Vector_UnsignedArg) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.vec2<i32>(), spirv::BuiltinFn::kSign,
                                               Vector<const core::type::Type*, 1>{ty.i32()},
                                               b.Splat(ty.vec2<u32>(), (10_u)));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:vec2<i32> = spirv.sign<i32> vec2<u32>(10u)
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:vec2<i32> = bitcast vec2<u32>(10u)
    %3:vec2<i32> = sign %2
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, SSign_Vector_UnsignedResult) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.vec2<u32>(), spirv::BuiltinFn::kSign,
                                               Vector<const core::type::Type*, 1>{ty.u32()},
                                               b.Splat(ty.vec2<i32>(), 10_i));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:vec2<u32> = spirv.sign<u32> vec2<i32>(10i)
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:vec2<i32> = sign vec2<i32>(10i)
    %3:vec2<u32> = bitcast %2
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, SSign_Vector_UnsignedArgAndResult) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.vec2<u32>(), spirv::BuiltinFn::kSign,
                                               Vector<const core::type::Type*, 1>{ty.u32()},
                                               b.Splat(ty.vec2<u32>(), 10_u));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:vec2<u32> = spirv.sign<u32> vec2<u32>(10u)
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:vec2<i32> = bitcast vec2<u32>(10u)
    %3:vec2<i32> = sign %2
    %4:vec2<u32> = bitcast %3
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, SSign_Vector_SignedArgAndResult) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.vec2<i32>(), spirv::BuiltinFn::kSign,
                                               Vector<const core::type::Type*, 1>{ty.i32()},
                                               b.Splat(ty.vec2<i32>(), 10_i));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:vec2<i32> = spirv.sign<i32> vec2<i32>(10i)
    ret
  }
}
)";
    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:vec2<i32> = sign vec2<i32>(10i)
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, SAbs_UnsignedToUnsigned) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.u32(), spirv::BuiltinFn::kAbs,
                                               Vector<const core::type::Type*, 1>{ty.u32()}, 10_u);
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.vec2<u32>(), spirv::BuiltinFn::kAbs,
                                               Vector<const core::type::Type*, 1>{ty.u32()},
                                               b.Splat(ty.vec2<u32>(), 10_u));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:u32 = spirv.abs<u32> 10u
    %3:vec2<u32> = spirv.abs<u32> vec2<u32>(10u)
    ret
  }
}
)";

    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = bitcast 10u
    %3:i32 = abs %2
    %4:u32 = bitcast %3
    %5:vec2<i32> = bitcast vec2<u32>(10u)
    %6:vec2<i32> = abs %5
    %7:vec2<u32> = bitcast %6
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, SAbs_UnsignedToSigned) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.i32(), spirv::BuiltinFn::kAbs,
                                               Vector<const core::type::Type*, 1>{ty.i32()}, 10_u);
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.vec2<i32>(), spirv::BuiltinFn::kAbs,
                                               Vector<const core::type::Type*, 1>{ty.i32()},
                                               b.Splat(ty.vec2<u32>(), 10_u));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = spirv.abs<i32> 10u
    %3:vec2<i32> = spirv.abs<i32> vec2<u32>(10u)
    ret
  }
}
)";

    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = bitcast 10u
    %3:i32 = abs %2
    %4:vec2<i32> = bitcast vec2<u32>(10u)
    %5:vec2<i32> = abs %4
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, SAbs_SignedToSigned) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.i32(), spirv::BuiltinFn::kAbs,
                                               Vector<const core::type::Type*, 1>{ty.i32()}, 10_i);
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.vec2<i32>(), spirv::BuiltinFn::kAbs,
                                               Vector<const core::type::Type*, 1>{ty.i32()},
                                               b.Splat(ty.vec2<i32>(), 10_i));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = spirv.abs<i32> 10i
    %3:vec2<i32> = spirv.abs<i32> vec2<i32>(10i)
    ret
  }
}
)";

    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = abs 10i
    %3:vec2<i32> = abs vec2<i32>(10i)
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_F(SpirvParser_BuiltinsTest, SAbs_SignedToUnsigned) {
    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.u32(), spirv::BuiltinFn::kAbs,
                                               Vector<const core::type::Type*, 1>{ty.u32()}, 10_i);
        b.CallExplicit<spirv::ir::BuiltinCall>(ty.vec2<u32>(), spirv::BuiltinFn::kAbs,
                                               Vector<const core::type::Type*, 1>{ty.u32()},
                                               b.Splat(ty.vec2<i32>(), 10_i));
        b.Return(ep);
    });

    auto* src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:u32 = spirv.abs<u32> 10i
    %3:vec2<u32> = spirv.abs<u32> vec2<i32>(10i)
    ret
  }
}
)";

    EXPECT_EQ(src, str());
    Run(Builtins);

    auto* expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = abs 10i
    %3:u32 = bitcast %2
    %4:vec2<i32> = abs vec2<i32>(10i)
    %5:vec2<u32> = bitcast %4
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

struct SpirvReaderTwoParams {
    spirv::BuiltinFn fn;
    std::string name;
};
[[maybe_unused]] inline std::ostream& operator<<(std::ostream& out, SpirvReaderTwoParams c) {
    out << c.name;
    return out;
}

using SpirvParser_BuiltinsTest_TwoParam =
    core::ir::transform::TransformTestWithParam<SpirvReaderTwoParams>;

TEST_P(SpirvParser_BuiltinsTest_TwoParam, UnsignedToUnsigned) {
    auto& params = GetParam();

    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(
            ty.u32(), params.fn, Vector<const core::type::Type*, 1>{ty.u32()}, 10_u, 15_u);
        b.CallExplicit<spirv::ir::BuiltinCall>(
            ty.vec2<u32>(), params.fn, Vector<const core::type::Type*, 1>{ty.u32()},
            b.Splat(ty.vec2<u32>(), 10_u), b.Splat(ty.vec2<u32>(), 15_u));
        b.Return(ep);
    });

    auto src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:u32 = spirv.)" +
               params.name + R"(<u32> 10u, 15u
    %3:vec2<u32> = spirv.)" +
               params.name + R"(<u32> vec2<u32>(10u), vec2<u32>(15u)
    ret
  }
}
)";

    EXPECT_EQ(src, str());
    Run(Builtins);

    auto expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = bitcast 10u
    %3:i32 = bitcast 15u
    %4:i32 = )" + params.name +
                  R"( %2, %3
    %5:u32 = bitcast %4
    %6:vec2<i32> = bitcast vec2<u32>(10u)
    %7:vec2<i32> = bitcast vec2<u32>(15u)
    %8:vec2<i32> = )" +
                  params.name + R"( %6, %7
    %9:vec2<u32> = bitcast %8
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_P(SpirvParser_BuiltinsTest_TwoParam, SignedToSigned) {
    auto params = GetParam();

    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(
            ty.i32(), params.fn, Vector<const core::type::Type*, 1>{ty.i32()}, 10_i, 15_i);
        b.CallExplicit<spirv::ir::BuiltinCall>(
            ty.vec2<i32>(), params.fn, Vector<const core::type::Type*, 1>{ty.i32()},
            b.Splat(ty.vec2<i32>(), 10_i), b.Splat(ty.vec2<i32>(), 15_i));
        b.Return(ep);
    });

    auto src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = spirv.)" +
               params.name + R"(<i32> 10i, 15i
    %3:vec2<i32> = spirv.)" +
               params.name + R"(<i32> vec2<i32>(10i), vec2<i32>(15i)
    ret
  }
}
)";

    EXPECT_EQ(src, str());
    Run(Builtins);

    auto expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = )" + params.name +
                  R"( 10i, 15i
    %3:vec2<i32> = )" +
                  params.name + R"( vec2<i32>(10i), vec2<i32>(15i)
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_P(SpirvParser_BuiltinsTest_TwoParam, MixedToUnsigned) {
    auto params = GetParam();

    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(
            ty.u32(), params.fn, Vector<const core::type::Type*, 1>{ty.u32()}, 10_i, 10_u);
        b.CallExplicit<spirv::ir::BuiltinCall>(
            ty.vec2<u32>(), params.fn, Vector<const core::type::Type*, 1>{ty.u32()},
            b.Splat(ty.vec2<i32>(), 10_i), b.Splat(ty.vec2<u32>(), 10_u));
        b.Return(ep);
    });

    auto src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:u32 = spirv.)" +
               params.name + R"(<u32> 10i, 10u
    %3:vec2<u32> = spirv.)" +
               params.name + R"(<u32> vec2<i32>(10i), vec2<u32>(10u)
    ret
  }
}
)";

    EXPECT_EQ(src, str());
    Run(Builtins);

    auto expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = bitcast 10u
    %3:i32 = )" + params.name +
                  R"( 10i, %2
    %4:u32 = bitcast %3
    %5:vec2<i32> = bitcast vec2<u32>(10u)
    %6:vec2<i32> = )" +
                  params.name + R"( vec2<i32>(10i), %5
    %7:vec2<u32> = bitcast %6
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

TEST_P(SpirvParser_BuiltinsTest_TwoParam, MixedToSigned) {
    auto params = GetParam();

    auto* ep = b.ComputeFunction("foo");

    b.Append(ep->Block(), [&] {  //
        b.CallExplicit<spirv::ir::BuiltinCall>(
            ty.i32(), params.fn, Vector<const core::type::Type*, 1>{ty.i32()}, 10_u, 10_i);
        b.CallExplicit<spirv::ir::BuiltinCall>(
            ty.vec2<i32>(), params.fn, Vector<const core::type::Type*, 1>{ty.i32()},
            b.Splat(ty.vec2<u32>(), 10_u), b.Splat(ty.vec2<i32>(), 10_i));
        b.Return(ep);
    });

    auto src = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = spirv.)" +
               params.name + R"(<i32> 10u, 10i
    %3:vec2<i32> = spirv.)" +
               params.name + R"(<i32> vec2<u32>(10u), vec2<i32>(10i)
    ret
  }
}
)";

    EXPECT_EQ(src, str());
    Run(Builtins);

    auto expect = R"(
%foo = @compute @workgroup_size(1u, 1u, 1u) func():void {
  $B1: {
    %2:i32 = bitcast 10u
    %3:i32 = )" + params.name +
                  R"( %2, 10i
    %4:vec2<i32> = bitcast vec2<u32>(10u)
    %5:vec2<i32> = )" +
                  params.name + R"( %4, vec2<i32>(10i)
    ret
  }
}
)";
    EXPECT_EQ(expect, str());
}

INSTANTIATE_TEST_SUITE_P(SpirvReader,
                         SpirvParser_BuiltinsTest_TwoParam,
                         ::testing::Values(SpirvReaderTwoParams{spirv::BuiltinFn::kMax, "max"},
                                           SpirvReaderTwoParams{spirv::BuiltinFn::kMin, "min"}));

}  // namespace
}  // namespace tint::spirv::reader::lower
