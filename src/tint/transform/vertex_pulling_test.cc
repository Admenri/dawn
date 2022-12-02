// Copyright 2020 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/tint/transform/vertex_pulling.h"

#include <utility>

#include "src/tint/transform/test_helper.h"

namespace tint::transform {
namespace {

using VertexPullingTest = TransformTest;

TEST_F(VertexPullingTest, Error_NoEntryPoint) {
    auto* src = "";

    auto* expect = "error: Vertex stage entry point not found";

    DataMap data;
    data.Add<VertexPulling::Config>();
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, Error_MultipleEntryPoint) {
    auto* src = R"(
@vertex
fn main() -> @builtin(position) vec4<f32> {
  return vec4<f32>();
}
@vertex
fn main2() -> @builtin(position) vec4<f32> {
  return vec4<f32>();
}
)";

    auto* expect = "error: VertexPulling found more than one vertex entry point";

    VertexPulling::Config cfg;

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, Error_EntryPointWrongStage) {
    auto* src = R"(
@fragment
fn main() {}
)";

    auto* expect = "error: Vertex stage entry point not found";

    VertexPulling::Config cfg;

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, Error_BadStride) {
    auto* src = R"(
@vertex
fn main(@location(0) var_a : f32) -> @builtin(position) vec4<f32> {
  return vec4<f32>(var_a, 0.0, 0.0, 1.0);
}
)";

    auto* expect =
        "error: WebGPU requires that vertex stride must be a multiple of 4 "
        "bytes, but VertexPulling array stride for buffer 0 was 15 bytes";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{15, VertexStepMode::kVertex, {{VertexFormat::kFloat32, 0, 0}}}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, BasicModule) {
    auto* src = R"(
@vertex
fn main() -> @builtin(position) vec4<f32> {
  return vec4<f32>();
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@vertex
fn main() -> @builtin(position) vec4<f32> {
  return vec4<f32>();
}
)";

    VertexPulling::Config cfg;

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, OneAttribute) {
    auto* src = R"(
@vertex
fn main(@location(0) var_a : f32) -> @builtin(position) vec4<f32> {
  return vec4<f32>(var_a, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var var_a : f32;
  {
    let buffer_array_base_0 = tint_pulling_vertex_index;
    var_a = bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[buffer_array_base_0]);
  }
  return vec4<f32>(var_a, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{4, VertexStepMode::kVertex, {{VertexFormat::kFloat32, 0, 0}}}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, OneInstancedAttribute) {
    auto* src = R"(
@vertex
fn main(@location(0) var_a : f32) -> @builtin(position) vec4<f32> {
  return vec4<f32>(var_a, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(instance_index) tint_pulling_instance_index : u32) -> @builtin(position) vec4<f32> {
  var var_a : f32;
  {
    let buffer_array_base_0 = tint_pulling_instance_index;
    var_a = bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[buffer_array_base_0]);
  }
  return vec4<f32>(var_a, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{4, VertexStepMode::kInstance, {{VertexFormat::kFloat32, 0, 0}}}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, OneAttributeDifferentOutputSet) {
    auto* src = R"(
@vertex
fn main(@location(0) var_a : f32) -> @builtin(position) vec4<f32> {
  return vec4<f32>(var_a, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(5) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var var_a : f32;
  {
    let buffer_array_base_0 = tint_pulling_vertex_index;
    var_a = bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[buffer_array_base_0]);
  }
  return vec4<f32>(var_a, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{4, VertexStepMode::kVertex, {{VertexFormat::kFloat32, 0, 0}}}}};
    cfg.pulling_group = 5;

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, OneAttribute_Struct) {
    auto* src = R"(
struct Inputs {
  @location(0) var_a : f32,
};

@vertex
fn main(inputs : Inputs) -> @builtin(position) vec4<f32> {
  return vec4<f32>(inputs.var_a, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

struct Inputs {
  @location(0)
  var_a : f32,
}

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var inputs : Inputs;
  {
    let buffer_array_base_0 = tint_pulling_vertex_index;
    inputs.var_a = bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[buffer_array_base_0]);
  }
  return vec4<f32>(inputs.var_a, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{4, VertexStepMode::kVertex, {{VertexFormat::kFloat32, 0, 0}}}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

// We expect the transform to use an existing builtin variables if it finds them
TEST_F(VertexPullingTest, ExistingVertexIndexAndInstanceIndex) {
    auto* src = R"(
@vertex
fn main(@location(0) var_a : f32,
        @location(1) var_b : f32,
        @builtin(vertex_index) custom_vertex_index : u32,
        @builtin(instance_index) custom_instance_index : u32
        ) -> @builtin(position) vec4<f32> {
  return vec4<f32>(var_a, var_b, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@binding(1) @group(4) var<storage, read> tint_pulling_vertex_buffer_1 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) custom_vertex_index : u32, @builtin(instance_index) custom_instance_index : u32) -> @builtin(position) vec4<f32> {
  var var_a : f32;
  var var_b : f32;
  {
    let buffer_array_base_0 = custom_vertex_index;
    var_a = bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[buffer_array_base_0]);
    let buffer_array_base_1 = custom_instance_index;
    var_b = bitcast<f32>(tint_pulling_vertex_buffer_1.tint_vertex_data[buffer_array_base_1]);
  }
  return vec4<f32>(var_a, var_b, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{
        {
            4,
            VertexStepMode::kVertex,
            {{VertexFormat::kFloat32, 0, 0}},
        },
        {
            4,
            VertexStepMode::kInstance,
            {{VertexFormat::kFloat32, 0, 1}},
        },
    }};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, ExistingVertexIndexAndInstanceIndex_Struct) {
    auto* src = R"(
struct Inputs {
  @location(0) var_a : f32,
  @location(1) var_b : f32,
  @builtin(vertex_index) custom_vertex_index : u32,
  @builtin(instance_index) custom_instance_index : u32,
};

@vertex
fn main(inputs : Inputs) -> @builtin(position) vec4<f32> {
  return vec4<f32>(inputs.var_a, inputs.var_b, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@binding(1) @group(4) var<storage, read> tint_pulling_vertex_buffer_1 : TintVertexData;

struct tint_symbol {
  @builtin(vertex_index)
  custom_vertex_index : u32,
  @builtin(instance_index)
  custom_instance_index : u32,
}

struct Inputs {
  @location(0)
  var_a : f32,
  @location(1)
  var_b : f32,
  @builtin(vertex_index)
  custom_vertex_index : u32,
  @builtin(instance_index)
  custom_instance_index : u32,
}

@vertex
fn main(tint_symbol_1 : tint_symbol) -> @builtin(position) vec4<f32> {
  var inputs : Inputs;
  inputs.custom_vertex_index = tint_symbol_1.custom_vertex_index;
  inputs.custom_instance_index = tint_symbol_1.custom_instance_index;
  {
    let buffer_array_base_0 = inputs.custom_vertex_index;
    inputs.var_a = bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[buffer_array_base_0]);
    let buffer_array_base_1 = inputs.custom_instance_index;
    inputs.var_b = bitcast<f32>(tint_pulling_vertex_buffer_1.tint_vertex_data[buffer_array_base_1]);
  }
  return vec4<f32>(inputs.var_a, inputs.var_b, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{
        {
            4,
            VertexStepMode::kVertex,
            {{VertexFormat::kFloat32, 0, 0}},
        },
        {
            4,
            VertexStepMode::kInstance,
            {{VertexFormat::kFloat32, 0, 1}},
        },
    }};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, ExistingVertexIndexAndInstanceIndex_Struct_OutOfOrder) {
    auto* src = R"(
@vertex
fn main(inputs : Inputs) -> @builtin(position) vec4<f32> {
  return vec4<f32>(inputs.var_a, inputs.var_b, 0.0, 1.0);
}

struct Inputs {
  @location(0) var_a : f32,
  @location(1) var_b : f32,
  @builtin(vertex_index) custom_vertex_index : u32,
  @builtin(instance_index) custom_instance_index : u32,
};
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@binding(1) @group(4) var<storage, read> tint_pulling_vertex_buffer_1 : TintVertexData;

struct tint_symbol {
  @builtin(vertex_index)
  custom_vertex_index : u32,
  @builtin(instance_index)
  custom_instance_index : u32,
}

@vertex
fn main(tint_symbol_1 : tint_symbol) -> @builtin(position) vec4<f32> {
  var inputs : Inputs;
  inputs.custom_vertex_index = tint_symbol_1.custom_vertex_index;
  inputs.custom_instance_index = tint_symbol_1.custom_instance_index;
  {
    let buffer_array_base_0 = inputs.custom_vertex_index;
    inputs.var_a = bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[buffer_array_base_0]);
    let buffer_array_base_1 = inputs.custom_instance_index;
    inputs.var_b = bitcast<f32>(tint_pulling_vertex_buffer_1.tint_vertex_data[buffer_array_base_1]);
  }
  return vec4<f32>(inputs.var_a, inputs.var_b, 0.0, 1.0);
}

struct Inputs {
  @location(0)
  var_a : f32,
  @location(1)
  var_b : f32,
  @builtin(vertex_index)
  custom_vertex_index : u32,
  @builtin(instance_index)
  custom_instance_index : u32,
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{
        {
            4,
            VertexStepMode::kVertex,
            {{VertexFormat::kFloat32, 0, 0}},
        },
        {
            4,
            VertexStepMode::kInstance,
            {{VertexFormat::kFloat32, 0, 1}},
        },
    }};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, ExistingVertexIndexAndInstanceIndex_SeparateStruct) {
    auto* src = R"(
struct Inputs {
  @location(0) var_a : f32,
  @location(1) var_b : f32,
};

struct Indices {
  @builtin(vertex_index) custom_vertex_index : u32,
  @builtin(instance_index) custom_instance_index : u32,
};

@vertex
fn main(inputs : Inputs, indices : Indices) -> @builtin(position) vec4<f32> {
  return vec4<f32>(inputs.var_a, inputs.var_b, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@binding(1) @group(4) var<storage, read> tint_pulling_vertex_buffer_1 : TintVertexData;

struct Inputs {
  @location(0)
  var_a : f32,
  @location(1)
  var_b : f32,
}

struct Indices {
  @builtin(vertex_index)
  custom_vertex_index : u32,
  @builtin(instance_index)
  custom_instance_index : u32,
}

@vertex
fn main(indices : Indices) -> @builtin(position) vec4<f32> {
  var inputs : Inputs;
  {
    let buffer_array_base_0 = indices.custom_vertex_index;
    inputs.var_a = bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[buffer_array_base_0]);
    let buffer_array_base_1 = indices.custom_instance_index;
    inputs.var_b = bitcast<f32>(tint_pulling_vertex_buffer_1.tint_vertex_data[buffer_array_base_1]);
  }
  return vec4<f32>(inputs.var_a, inputs.var_b, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{
        {
            4,
            VertexStepMode::kVertex,
            {{VertexFormat::kFloat32, 0, 0}},
        },
        {
            4,
            VertexStepMode::kInstance,
            {{VertexFormat::kFloat32, 0, 1}},
        },
    }};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, ExistingVertexIndexAndInstanceIndex_SeparateStruct_OutOfOrder) {
    auto* src = R"(
@vertex
fn main(inputs : Inputs, indices : Indices) -> @builtin(position) vec4<f32> {
  return vec4<f32>(inputs.var_a, inputs.var_b, 0.0, 1.0);
}

struct Inputs {
  @location(0) var_a : f32,
  @location(1) var_b : f32,
};

struct Indices {
  @builtin(vertex_index) custom_vertex_index : u32,
  @builtin(instance_index) custom_instance_index : u32,
};
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@binding(1) @group(4) var<storage, read> tint_pulling_vertex_buffer_1 : TintVertexData;

@vertex
fn main(indices : Indices) -> @builtin(position) vec4<f32> {
  var inputs : Inputs;
  {
    let buffer_array_base_0 = indices.custom_vertex_index;
    inputs.var_a = bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[buffer_array_base_0]);
    let buffer_array_base_1 = indices.custom_instance_index;
    inputs.var_b = bitcast<f32>(tint_pulling_vertex_buffer_1.tint_vertex_data[buffer_array_base_1]);
  }
  return vec4<f32>(inputs.var_a, inputs.var_b, 0.0, 1.0);
}

struct Inputs {
  @location(0)
  var_a : f32,
  @location(1)
  var_b : f32,
}

struct Indices {
  @builtin(vertex_index)
  custom_vertex_index : u32,
  @builtin(instance_index)
  custom_instance_index : u32,
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{
        {
            4,
            VertexStepMode::kVertex,
            {{VertexFormat::kFloat32, 0, 0}},
        },
        {
            4,
            VertexStepMode::kInstance,
            {{VertexFormat::kFloat32, 0, 1}},
        },
    }};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, TwoAttributesSameBuffer) {
    auto* src = R"(
@vertex
fn main(@location(0) var_a : f32,
        @location(1) var_b : vec4<f32>) -> @builtin(position) vec4<f32> {
  return vec4<f32>();
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var var_a : f32;
  var var_b : vec4<f32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index * 4u);
    var_a = bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[buffer_array_base_0]);
    var_b = vec4<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[buffer_array_base_0]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 1u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 2u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 3u)]));
  }
  return vec4<f32>();
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{16,
                          VertexStepMode::kVertex,
                          {{VertexFormat::kFloat32, 0, 0}, {VertexFormat::kFloat32x4, 0, 1}}}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, FloatVectorAttributes_F32) {
    auto* src = R"(
@vertex
fn main(@location(0) var_a : vec2<f32>,
        @location(1) var_b : vec3<f32>,
        @location(2) var_c : vec4<f32>
        ) -> @builtin(position) vec4<f32> {
  return vec4<f32>();
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@binding(1) @group(4) var<storage, read> tint_pulling_vertex_buffer_1 : TintVertexData;

@binding(2) @group(4) var<storage, read> tint_pulling_vertex_buffer_2 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var var_a : vec2<f32>;
  var var_b : vec3<f32>;
  var var_c : vec4<f32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index * 2u);
    var_a = vec2<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[buffer_array_base_0]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 1u)]));
    let buffer_array_base_1 = (tint_pulling_vertex_index * 3u);
    var_b = vec3<f32>(bitcast<f32>(tint_pulling_vertex_buffer_1.tint_vertex_data[buffer_array_base_1]), bitcast<f32>(tint_pulling_vertex_buffer_1.tint_vertex_data[(buffer_array_base_1 + 1u)]), bitcast<f32>(tint_pulling_vertex_buffer_1.tint_vertex_data[(buffer_array_base_1 + 2u)]));
    let buffer_array_base_2 = (tint_pulling_vertex_index * 4u);
    var_c = vec4<f32>(bitcast<f32>(tint_pulling_vertex_buffer_2.tint_vertex_data[buffer_array_base_2]), bitcast<f32>(tint_pulling_vertex_buffer_2.tint_vertex_data[(buffer_array_base_2 + 1u)]), bitcast<f32>(tint_pulling_vertex_buffer_2.tint_vertex_data[(buffer_array_base_2 + 2u)]), bitcast<f32>(tint_pulling_vertex_buffer_2.tint_vertex_data[(buffer_array_base_2 + 3u)]));
  }
  return vec4<f32>();
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{
        {8, VertexStepMode::kVertex, {{VertexFormat::kFloat32x2, 0, 0}}},
        {12, VertexStepMode::kVertex, {{VertexFormat::kFloat32x3, 0, 1}}},
        {16, VertexStepMode::kVertex, {{VertexFormat::kFloat32x4, 0, 2}}},
    }};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, AttemptSymbolCollision) {
    auto* src = R"(
@vertex
fn main(@location(0) var_a : f32,
        @location(1) var_b : vec4<f32>) -> @builtin(position) vec4<f32> {
  var tint_pulling_vertex_index : i32;
  var tint_pulling_vertex_buffer_0 : i32;
  var tint_vertex_data : i32;
  var tint_pulling_pos : i32;
  return vec4<f32>();
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data_1 : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0_1 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index_1 : u32) -> @builtin(position) vec4<f32> {
  var var_a : f32;
  var var_b : vec4<f32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index_1 * 4u);
    var_a = bitcast<f32>(tint_pulling_vertex_buffer_0_1.tint_vertex_data_1[buffer_array_base_0]);
    var_b = vec4<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0_1.tint_vertex_data_1[buffer_array_base_0]), bitcast<f32>(tint_pulling_vertex_buffer_0_1.tint_vertex_data_1[(buffer_array_base_0 + 1u)]), bitcast<f32>(tint_pulling_vertex_buffer_0_1.tint_vertex_data_1[(buffer_array_base_0 + 2u)]), bitcast<f32>(tint_pulling_vertex_buffer_0_1.tint_vertex_data_1[(buffer_array_base_0 + 3u)]));
  }
  var tint_pulling_vertex_index : i32;
  var tint_pulling_vertex_buffer_0 : i32;
  var tint_vertex_data : i32;
  var tint_pulling_pos : i32;
  return vec4<f32>();
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{16,
                          VertexStepMode::kVertex,
                          {{VertexFormat::kFloat32, 0, 0}, {VertexFormat::kFloat32x4, 0, 1}}}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, std::move(data));

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, FormatsAligned_SInt) {
    auto* src = R"(
@vertex
fn main(
    @location(0) sint8x2 : vec2<i32>,
    @location(1) sint8x4 : vec4<i32>,
    @location(2) sint16x2 : vec2<i32>,
    @location(3) sint16x4 : vec4<i32>,
    @location(4) sint32 : i32,
    @location(5) sint32x2 : vec2<i32>,
    @location(6) sint32x3 : vec3<i32>,
    @location(7) sint32x4 : vec4<i32>
  ) -> @builtin(position) vec4<f32> {
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var sint8x2 : vec2<i32>;
  var sint8x4 : vec4<i32>;
  var sint16x2 : vec2<i32>;
  var sint16x4 : vec4<i32>;
  var sint32 : i32;
  var sint32x2 : vec2<i32>;
  var sint32x3 : vec3<i32>;
  var sint32x4 : vec4<i32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index * 64u);
    sint8x2 = ((vec2<i32>(bitcast<i32>((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 16u))) << vec2<u32>(8u, 0u)) >> vec2<u32>(24u));
    sint8x4 = ((vec4<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)])) << vec4<u32>(24u, 16u, 8u, 0u)) >> vec4<u32>(24u));
    sint16x2 = ((vec2<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)])) << vec2<u32>(16u, 0u)) >> vec2<u32>(16u));
    sint16x4 = ((vec2<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).xxyy << vec4<u32>(16u, 0u, 16u, 0u)) >> vec4<u32>(16u));
    sint32 = bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]);
    sint32x2 = vec2<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]));
    sint32x3 = vec3<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)]));
    sint32x4 = vec4<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)]));
  }
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{256,
                          VertexStepMode::kVertex,
                          {
                              {VertexFormat::kSint8x2, 64, 0},
                              {VertexFormat::kSint8x4, 64, 1},
                              {VertexFormat::kSint16x2, 64, 2},
                              {VertexFormat::kSint16x4, 64, 3},
                              {VertexFormat::kSint32, 64, 4},
                              {VertexFormat::kSint32x2, 64, 5},
                              {VertexFormat::kSint32x3, 64, 6},
                              {VertexFormat::kSint32x4, 64, 7},
                          }}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, FormatsAligned_UInt) {
    auto* src = R"(
@vertex
fn main(
    @location(0) uint8x2 : vec2<u32>,
    @location(1) uint8x4 : vec4<u32>,
    @location(2) uint16x2 : vec2<u32>,
    @location(3) uint16x4 : vec4<u32>,
    @location(4) uint32 : u32,
    @location(5) uint32x2 : vec2<u32>,
    @location(6) uint32x3 : vec3<u32>,
    @location(7) uint32x4 : vec4<u32>,
  ) -> @builtin(position) vec4<f32> {
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var uint8x2 : vec2<u32>;
  var uint8x4 : vec4<u32>;
  var uint16x2 : vec2<u32>;
  var uint16x4 : vec4<u32>;
  var uint32 : u32;
  var uint32x2 : vec2<u32>;
  var uint32x3 : vec3<u32>;
  var uint32x4 : vec4<u32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index * 64u);
    uint8x2 = ((vec2<u32>((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 16u)) << vec2<u32>(8u, 0u)) >> vec2<u32>(24u));
    uint8x4 = ((vec4<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]) << vec4<u32>(24u, 16u, 8u, 0u)) >> vec4<u32>(24u));
    uint16x2 = ((vec2<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]) << vec2<u32>(16u, 0u)) >> vec2<u32>(16u));
    uint16x4 = ((vec2<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]).xxyy << vec4<u32>(16u, 0u, 16u, 0u)) >> vec4<u32>(16u));
    uint32 = tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)];
    uint32x2 = vec2<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]);
    uint32x3 = vec3<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)]);
    uint32x4 = vec4<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)]);
  }
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{256,
                          VertexStepMode::kVertex,
                          {
                              {VertexFormat::kUint8x2, 64, 0},
                              {VertexFormat::kUint8x4, 64, 1},
                              {VertexFormat::kUint16x2, 64, 2},
                              {VertexFormat::kUint16x4, 64, 3},
                              {VertexFormat::kUint32, 64, 4},
                              {VertexFormat::kUint32x2, 64, 5},
                              {VertexFormat::kUint32x3, 64, 6},
                              {VertexFormat::kUint32x4, 64, 7},
                          }}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, FormatsAligned_Float_F32) {
    auto* src = R"(
@vertex
fn main(
    @location(0) unorm8x2 : vec2<f32>,
    @location(1) unorm8x4 : vec4<f32>,
    @location(2) snorm8x2 : vec2<f32>,
    @location(3) snorm8x4 : vec4<f32>,
    @location(4) unorm16x2 : vec2<f32>,
    @location(5) unorm16x4 : vec4<f32>,
    @location(6) snorm16x2 : vec2<f32>,
    @location(7) snorm16x4 : vec4<f32>,
    @location(8) float16x2 : vec2<f32>,
    @location(9) float16x4 : vec4<f32>,
    @location(10) float32 : f32,
    @location(11) float32x2 : vec2<f32>,
    @location(12) float32x3 : vec3<f32>,
    @location(13) float32x4 : vec4<f32>,
  ) -> @builtin(position) vec4<f32> {
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var unorm8x2 : vec2<f32>;
  var unorm8x4 : vec4<f32>;
  var snorm8x2 : vec2<f32>;
  var snorm8x4 : vec4<f32>;
  var unorm16x2 : vec2<f32>;
  var unorm16x4 : vec4<f32>;
  var snorm16x2 : vec2<f32>;
  var snorm16x4 : vec4<f32>;
  var float16x2 : vec2<f32>;
  var float16x4 : vec4<f32>;
  var float32 : f32;
  var float32x2 : vec2<f32>;
  var float32x3 : vec3<f32>;
  var float32x4 : vec4<f32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index * 64u);
    unorm8x2 = unpack4x8unorm((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] & 65535u)).xy;
    unorm8x4 = unpack4x8unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]);
    snorm8x2 = unpack4x8snorm((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] & 65535u)).xy;
    snorm8x4 = unpack4x8snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]);
    unorm16x2 = unpack2x16unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]);
    unorm16x4 = vec4<f32>(unpack2x16unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), unpack2x16unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]));
    snorm16x2 = unpack2x16snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]);
    snorm16x4 = vec4<f32>(unpack2x16snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), unpack2x16snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]));
    float16x2 = unpack2x16float(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]);
    float16x4 = vec4<f32>(unpack2x16float(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), unpack2x16float(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]));
    float32 = bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]);
    float32x2 = vec2<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]));
    float32x3 = vec3<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)]));
    float32x4 = vec4<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)]));
  }
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{256,
                          VertexStepMode::kVertex,
                          {
                              {VertexFormat::kUnorm8x2, 64, 0},
                              {VertexFormat::kUnorm8x4, 64, 1},
                              {VertexFormat::kSnorm8x2, 64, 2},
                              {VertexFormat::kSnorm8x4, 64, 3},
                              {VertexFormat::kUnorm16x2, 64, 4},
                              {VertexFormat::kUnorm16x4, 64, 5},
                              {VertexFormat::kSnorm16x2, 64, 6},
                              {VertexFormat::kSnorm16x4, 64, 7},
                              {VertexFormat::kFloat16x2, 64, 8},
                              {VertexFormat::kFloat16x4, 64, 9},
                              {VertexFormat::kFloat32, 64, 10},
                              {VertexFormat::kFloat32x2, 64, 11},
                              {VertexFormat::kFloat32x3, 64, 12},
                              {VertexFormat::kFloat32x4, 64, 13},
                          }}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, FormatsUnaligned_SInt) {
    auto* src = R"(
@vertex
fn main(
    @location(0) sint8x2 : vec2<i32>,
    @location(1) sint8x4 : vec4<i32>,
    @location(2) sint16x2 : vec2<i32>,
    @location(3) sint16x4 : vec4<i32>,
    @location(4) sint32 : i32,
    @location(5) sint32x2 : vec2<i32>,
    @location(6) sint32x3 : vec3<i32>,
    @location(7) sint32x4 : vec4<i32>
  ) -> @builtin(position) vec4<f32> {
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var sint8x2 : vec2<i32>;
  var sint8x4 : vec4<i32>;
  var sint16x2 : vec2<i32>;
  var sint16x4 : vec4<i32>;
  var sint32 : i32;
  var sint32x2 : vec2<i32>;
  var sint32x3 : vec3<i32>;
  var sint32x4 : vec4<i32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index * 64u);
    sint8x2 = ((vec2<i32>(bitcast<i32>((((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 8u)) & 4294901760u))) << vec2<u32>(8u, 0u)) >> vec2<u32>(24u));
    sint8x4 = ((vec4<i32>(bitcast<i32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u)))) << vec4<u32>(24u, 16u, 8u, 0u)) >> vec4<u32>(24u));
    sint16x2 = ((vec2<i32>(bitcast<i32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u)))) << vec2<u32>(16u, 0u)) >> vec2<u32>(16u));
    sint16x4 = ((vec2<i32>(bitcast<i32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u))), bitcast<i32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] << 8u)))).xxyy << vec4<u32>(16u, 0u, 16u, 0u)) >> vec4<u32>(16u));
    sint32 = bitcast<i32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u)));
    sint32x2 = vec2<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]));
    sint32x3 = vec3<i32>(bitcast<i32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u))), bitcast<i32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] << 8u))), bitcast<i32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)] << 8u))));
    sint32x4 = vec4<i32>(bitcast<i32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u))), bitcast<i32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] << 8u))), bitcast<i32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)] << 8u))), bitcast<i32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)] << 8u))));
  }
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{256,
                          VertexStepMode::kVertex,
                          {
                              {VertexFormat::kSint8x2, 63, 0},
                              {VertexFormat::kSint8x4, 63, 1},
                              {VertexFormat::kSint16x2, 63, 2},
                              {VertexFormat::kSint16x4, 63, 3},
                              {VertexFormat::kSint32, 63, 4},
                              {VertexFormat::kSint32x2, 64, 5},
                              {VertexFormat::kSint32x3, 63, 6},
                              {VertexFormat::kSint32x4, 63, 7},
                          }}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, FormatsUnaligned_UInt) {
    auto* src = R"(
@vertex
fn main(
    @location(0) uint8x2 : vec2<u32>,
    @location(1) uint8x4 : vec4<u32>,
    @location(2) uint16x2 : vec2<u32>,
    @location(3) uint16x4 : vec4<u32>,
    @location(4) uint32 : u32,
    @location(5) uint32x2 : vec2<u32>,
    @location(6) uint32x3 : vec3<u32>,
    @location(7) uint32x4 : vec4<u32>,
  ) -> @builtin(position) vec4<f32> {
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var uint8x2 : vec2<u32>;
  var uint8x4 : vec4<u32>;
  var uint16x2 : vec2<u32>;
  var uint16x4 : vec4<u32>;
  var uint32 : u32;
  var uint32x2 : vec2<u32>;
  var uint32x3 : vec3<u32>;
  var uint32x4 : vec4<u32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index * 64u);
    uint8x2 = ((vec2<u32>((((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 8u)) & 4294901760u)) << vec2<u32>(8u, 0u)) >> vec2<u32>(24u));
    uint8x4 = ((vec4<u32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u))) << vec4<u32>(24u, 16u, 8u, 0u)) >> vec4<u32>(24u));
    uint16x2 = ((vec2<u32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u))) << vec2<u32>(16u, 0u)) >> vec2<u32>(16u));
    uint16x4 = ((vec2<u32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u)), ((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] << 8u))).xxyy << vec4<u32>(16u, 0u, 16u, 0u)) >> vec4<u32>(16u));
    uint32 = ((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u));
    uint32x2 = vec2<u32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u)), ((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] << 8u)));
    uint32x3 = vec3<u32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u)), ((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] << 8u)), ((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)] << 8u)));
    uint32x4 = vec4<u32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u)), ((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] << 8u)), ((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)] << 8u)), ((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)] << 8u)));
  }
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{256,
                          VertexStepMode::kVertex,
                          {
                              {VertexFormat::kUint8x2, 63, 0},
                              {VertexFormat::kUint8x4, 63, 1},
                              {VertexFormat::kUint16x2, 63, 2},
                              {VertexFormat::kUint16x4, 63, 3},
                              {VertexFormat::kUint32, 63, 4},
                              {VertexFormat::kUint32x2, 63, 5},
                              {VertexFormat::kUint32x3, 63, 6},
                              {VertexFormat::kUint32x4, 63, 7},
                          }}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, FormatsUnaligned_Float_F32) {
    auto* src = R"(
@vertex
fn main(
    @location(0) unorm8x2 : vec2<f32>,
    @location(1) unorm8x4 : vec4<f32>,
    @location(2) snorm8x2 : vec2<f32>,
    @location(3) snorm8x4 : vec4<f32>,
    @location(4) unorm16x2 : vec2<f32>,
    @location(5) unorm16x4 : vec4<f32>,
    @location(6) snorm16x2 : vec2<f32>,
    @location(7) snorm16x4 : vec4<f32>,
    @location(8) float16x2 : vec2<f32>,
    @location(9) float16x4 : vec4<f32>,
    @location(10) float32 : f32,
    @location(11) float32x2 : vec2<f32>,
    @location(12) float32x3 : vec3<f32>,
    @location(13) float32x4 : vec4<f32>,
  ) -> @builtin(position) vec4<f32> {
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var unorm8x2 : vec2<f32>;
  var unorm8x4 : vec4<f32>;
  var snorm8x2 : vec2<f32>;
  var snorm8x4 : vec4<f32>;
  var unorm16x2 : vec2<f32>;
  var unorm16x4 : vec4<f32>;
  var snorm16x2 : vec2<f32>;
  var snorm16x4 : vec4<f32>;
  var float16x2 : vec2<f32>;
  var float16x4 : vec4<f32>;
  var float32 : f32;
  var float32x2 : vec2<f32>;
  var float32x3 : vec3<f32>;
  var float32x4 : vec4<f32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index * 64u);
    unorm8x2 = unpack4x8unorm((((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u)) & 65535u)).xy;
    unorm8x4 = unpack4x8unorm(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u)));
    snorm8x2 = unpack4x8snorm((((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u)) & 65535u)).xy;
    snorm8x4 = unpack4x8snorm(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u)));
    unorm16x2 = unpack2x16unorm(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u)));
    unorm16x4 = vec4<f32>(unpack2x16unorm(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u))), unpack2x16unorm(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] << 8u))));
    snorm16x2 = unpack2x16snorm(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u)));
    snorm16x4 = vec4<f32>(unpack2x16snorm(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u))), unpack2x16snorm(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] << 8u))));
    float16x2 = unpack2x16float(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u)));
    float16x4 = vec4<f32>(unpack2x16float(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u))), unpack2x16float(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] << 8u))));
    float32 = bitcast<f32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u)));
    float32x2 = vec2<f32>(bitcast<f32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u))), bitcast<f32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] << 8u))));
    float32x3 = vec3<f32>(bitcast<f32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u))), bitcast<f32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] << 8u))), bitcast<f32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)] << 8u))));
    float32x4 = vec4<f32>(bitcast<f32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 15u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 8u))), bitcast<f32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] << 8u))), bitcast<f32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)] << 8u))), bitcast<f32>(((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)] >> 24u) | (tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)] << 8u))));
  }
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{256,
                          VertexStepMode::kVertex,
                          {
                              {VertexFormat::kUnorm8x2, 63, 0},
                              {VertexFormat::kUnorm8x4, 63, 1},
                              {VertexFormat::kSnorm8x2, 63, 2},
                              {VertexFormat::kSnorm8x4, 63, 3},
                              {VertexFormat::kUnorm16x2, 63, 4},
                              {VertexFormat::kUnorm16x4, 63, 5},
                              {VertexFormat::kSnorm16x2, 63, 6},
                              {VertexFormat::kSnorm16x4, 63, 7},
                              {VertexFormat::kFloat16x2, 63, 8},
                              {VertexFormat::kFloat16x4, 63, 9},
                              {VertexFormat::kFloat32, 63, 10},
                              {VertexFormat::kFloat32x2, 63, 11},
                              {VertexFormat::kFloat32x3, 63, 12},
                              {VertexFormat::kFloat32x4, 63, 13},
                          }}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, FormatsWithVectorsResized_Padding_SInt) {
    auto* src = R"(
@vertex
fn main(
    @location(0) vec3_sint8x2 :  vec3<i32>,
    @location(1) vec4_sint8x2 :  vec4<i32>,
    @location(2) vec3_sint16x2 : vec3<i32>,
    @location(3) vec4_sint16x2 : vec4<i32>,
    @location(4) vec2_sint32 :   vec2<i32>,
    @location(5) vec3_sint32 :   vec3<i32>,
    @location(6) vec4_sint32 :   vec4<i32>,
    @location(7) vec3_sint32x2 : vec3<i32>,
    @location(8) vec4_sint32x2 : vec4<i32>,
    @location(9) vec4_sint32x3 : vec4<i32>,
  ) -> @builtin(position) vec4<f32> {
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var vec3_sint8x2 : vec3<i32>;
  var vec4_sint8x2 : vec4<i32>;
  var vec3_sint16x2 : vec3<i32>;
  var vec4_sint16x2 : vec4<i32>;
  var vec2_sint32 : vec2<i32>;
  var vec3_sint32 : vec3<i32>;
  var vec4_sint32 : vec4<i32>;
  var vec3_sint32x2 : vec3<i32>;
  var vec4_sint32x2 : vec4<i32>;
  var vec4_sint32x3 : vec4<i32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index * 64u);
    vec3_sint8x2 = vec3<i32>(((vec2<i32>(bitcast<i32>((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 16u))) << vec2<u32>(8u, 0u)) >> vec2<u32>(24u)), 0);
    vec4_sint8x2 = vec4<i32>(((vec2<i32>(bitcast<i32>((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 16u))) << vec2<u32>(8u, 0u)) >> vec2<u32>(24u)), 0, 1);
    vec3_sint16x2 = vec3<i32>(((vec2<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)])) << vec2<u32>(16u, 0u)) >> vec2<u32>(16u)), 0);
    vec4_sint16x2 = vec4<i32>(((vec2<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)])) << vec2<u32>(16u, 0u)) >> vec2<u32>(16u)), 0, 1);
    vec2_sint32 = vec2<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), 0);
    vec3_sint32 = vec3<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), 0, 0);
    vec4_sint32 = vec4<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), 0, 0, 1);
    vec3_sint32x2 = vec3<i32>(vec2<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])), 0);
    vec4_sint32x2 = vec4<i32>(vec2<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])), 0, 1);
    vec4_sint32x3 = vec4<i32>(vec3<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)])), 1);
  }
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{256,
                          VertexStepMode::kVertex,
                          {
                              {VertexFormat::kSint8x2, 64, 0},
                              {VertexFormat::kSint8x2, 64, 1},
                              {VertexFormat::kSint16x2, 64, 2},
                              {VertexFormat::kSint16x2, 64, 3},
                              {VertexFormat::kSint32, 64, 4},
                              {VertexFormat::kSint32, 64, 5},
                              {VertexFormat::kSint32, 64, 6},
                              {VertexFormat::kSint32x2, 64, 7},
                              {VertexFormat::kSint32x2, 64, 8},
                              {VertexFormat::kSint32x3, 64, 9},
                          }}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, FormatsWithVectorsResized_Padding_UInt) {
    auto* src = R"(
@vertex
fn main(
    @location(0) vec3_uint8x2 :  vec3<u32>,
    @location(1) vec4_uint8x2 :  vec4<u32>,
    @location(2) vec3_uint16x2 : vec3<u32>,
    @location(3) vec4_uint16x2 : vec4<u32>,
    @location(4) vec2_uint32 :   vec2<u32>,
    @location(5) vec3_uint32 :   vec3<u32>,
    @location(6) vec4_uint32 :   vec4<u32>,
    @location(7) vec3_uint32x2 : vec3<u32>,
    @location(8) vec4_uint32x2 : vec4<u32>,
    @location(9) vec4_uint32x3 : vec4<u32>,
  ) -> @builtin(position) vec4<f32> {
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var vec3_uint8x2 : vec3<u32>;
  var vec4_uint8x2 : vec4<u32>;
  var vec3_uint16x2 : vec3<u32>;
  var vec4_uint16x2 : vec4<u32>;
  var vec2_uint32 : vec2<u32>;
  var vec3_uint32 : vec3<u32>;
  var vec4_uint32 : vec4<u32>;
  var vec3_uint32x2 : vec3<u32>;
  var vec4_uint32x2 : vec4<u32>;
  var vec4_uint32x3 : vec4<u32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index * 64u);
    vec3_uint8x2 = vec3<u32>(((vec2<u32>((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 16u)) << vec2<u32>(8u, 0u)) >> vec2<u32>(24u)), 0);
    vec4_uint8x2 = vec4<u32>(((vec2<u32>((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 16u)) << vec2<u32>(8u, 0u)) >> vec2<u32>(24u)), 0, 1);
    vec3_uint16x2 = vec3<u32>(((vec2<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]) << vec2<u32>(16u, 0u)) >> vec2<u32>(16u)), 0);
    vec4_uint16x2 = vec4<u32>(((vec2<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]) << vec2<u32>(16u, 0u)) >> vec2<u32>(16u)), 0, 1);
    vec2_uint32 = vec2<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], 0);
    vec3_uint32 = vec3<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], 0, 0);
    vec4_uint32 = vec4<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], 0, 0, 1);
    vec3_uint32x2 = vec3<u32>(vec2<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), 0);
    vec4_uint32x2 = vec4<u32>(vec2<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), 0, 1);
    vec4_uint32x3 = vec4<u32>(vec3<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)]), 1);
  }
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{256,
                          VertexStepMode::kVertex,
                          {
                              {VertexFormat::kUint8x2, 64, 0},
                              {VertexFormat::kUint8x2, 64, 1},
                              {VertexFormat::kUint16x2, 64, 2},
                              {VertexFormat::kUint16x2, 64, 3},
                              {VertexFormat::kUint32, 64, 4},
                              {VertexFormat::kUint32, 64, 5},
                              {VertexFormat::kUint32, 64, 6},
                              {VertexFormat::kUint32x2, 64, 7},
                              {VertexFormat::kUint32x2, 64, 8},
                              {VertexFormat::kUint32x3, 64, 9},
                          }}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, FormatsWithVectorsResized_Padding_Float_F32) {
    auto* src = R"(
@vertex
fn main(
    @location(0)  vec3_unorm8x2 :  vec3<f32>,
    @location(1)  vec4_unorm8x2 :  vec4<f32>,
    @location(2)  vec3_snorm8x2 :  vec3<f32>,
    @location(3)  vec4_snorm8x2 :  vec4<f32>,
    @location(4)  vec3_unorm16x2 : vec3<f32>,
    @location(5)  vec4_unorm16x2 : vec4<f32>,
    @location(6)  vec3_snorm16x2 : vec3<f32>,
    @location(7)  vec4_snorm16x2 : vec4<f32>,
    @location(8)  vec3_float16x2 : vec3<f32>,
    @location(9)  vec4_float16x2 : vec4<f32>,
    @location(10) vec2_float32 :   vec2<f32>,
    @location(11) vec3_float32 :   vec3<f32>,
    @location(12) vec4_float32 :   vec4<f32>,
    @location(13) vec3_float32x2 : vec3<f32>,
    @location(14) vec4_float32x2 : vec4<f32>,
    @location(15) vec4_float32x3 : vec4<f32>,
  ) -> @builtin(position) vec4<f32> {
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var vec3_unorm8x2 : vec3<f32>;
  var vec4_unorm8x2 : vec4<f32>;
  var vec3_snorm8x2 : vec3<f32>;
  var vec4_snorm8x2 : vec4<f32>;
  var vec3_unorm16x2 : vec3<f32>;
  var vec4_unorm16x2 : vec4<f32>;
  var vec3_snorm16x2 : vec3<f32>;
  var vec4_snorm16x2 : vec4<f32>;
  var vec3_float16x2 : vec3<f32>;
  var vec4_float16x2 : vec4<f32>;
  var vec2_float32 : vec2<f32>;
  var vec3_float32 : vec3<f32>;
  var vec4_float32 : vec4<f32>;
  var vec3_float32x2 : vec3<f32>;
  var vec4_float32x2 : vec4<f32>;
  var vec4_float32x3 : vec4<f32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index * 64u);
    vec3_unorm8x2 = vec3<f32>(unpack4x8unorm((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] & 65535u)).xy, 0.0);
    vec4_unorm8x2 = vec4<f32>(unpack4x8unorm((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] & 65535u)).xy, 0.0, 1.0);
    vec3_snorm8x2 = vec3<f32>(unpack4x8snorm((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] & 65535u)).xy, 0.0);
    vec4_snorm8x2 = vec4<f32>(unpack4x8snorm((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] & 65535u)).xy, 0.0, 1.0);
    vec3_unorm16x2 = vec3<f32>(unpack2x16unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), 0.0);
    vec4_unorm16x2 = vec4<f32>(unpack2x16unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), 0.0, 1.0);
    vec3_snorm16x2 = vec3<f32>(unpack2x16snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), 0.0);
    vec4_snorm16x2 = vec4<f32>(unpack2x16snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), 0.0, 1.0);
    vec3_float16x2 = vec3<f32>(unpack2x16float(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), 0.0);
    vec4_float16x2 = vec4<f32>(unpack2x16float(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), 0.0, 1.0);
    vec2_float32 = vec2<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), 0.0);
    vec3_float32 = vec3<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), 0.0, 0.0);
    vec4_float32 = vec4<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), 0.0, 0.0, 1.0);
    vec3_float32x2 = vec3<f32>(vec2<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])), 0.0);
    vec4_float32x2 = vec4<f32>(vec2<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])), 0.0, 1.0);
    vec4_float32x3 = vec4<f32>(vec3<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)])), 1.0);
  }
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{256,
                          VertexStepMode::kVertex,
                          {
                              {VertexFormat::kUnorm8x2, 64, 0},
                              {VertexFormat::kUnorm8x2, 64, 1},
                              {VertexFormat::kSnorm8x2, 64, 2},
                              {VertexFormat::kSnorm8x2, 64, 3},
                              {VertexFormat::kUnorm16x2, 64, 4},
                              {VertexFormat::kUnorm16x2, 64, 5},
                              {VertexFormat::kSnorm16x2, 64, 6},
                              {VertexFormat::kSnorm16x2, 64, 7},
                              {VertexFormat::kFloat16x2, 64, 8},
                              {VertexFormat::kFloat16x2, 64, 9},
                              {VertexFormat::kFloat32, 64, 10},
                              {VertexFormat::kFloat32, 64, 11},
                              {VertexFormat::kFloat32, 64, 12},
                              {VertexFormat::kFloat32x2, 64, 13},
                              {VertexFormat::kFloat32x2, 64, 14},
                              {VertexFormat::kFloat32x3, 64, 15},
                          }}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, FormatsWithVectorsResized_Shrinking_SInt) {
    auto* src = R"(
@vertex
fn main(
    @location(0)  sclr_sint8x2 :       i32 ,
    @location(1)  sclr_sint8x4 :       i32 ,
    @location(2)  vec2_sint8x4 :  vec2<i32>,
    @location(3)  vec3_sint8x4 :  vec3<i32>,
    @location(4)  sclr_sint16x2 :      i32 ,
    @location(5)  sclr_sint16x4 :      i32 ,
    @location(6)  vec2_sint16x4 : vec2<i32>,
    @location(7)  vec3_sint16x4 : vec3<i32>,
    @location(8)  sclr_sint32x2 :      i32 ,
    @location(9)  sclr_sint32x3 :      i32 ,
    @location(10) vec2_sint32x3 : vec2<i32>,
    @location(11) sclr_sint32x4 :      i32 ,
    @location(12) vec2_sint32x4 : vec2<i32>,
    @location(13) vec3_sint32x4 : vec3<i32>,
  ) -> @builtin(position) vec4<f32> {
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var sclr_sint8x2 : i32;
  var sclr_sint8x4 : i32;
  var vec2_sint8x4 : vec2<i32>;
  var vec3_sint8x4 : vec3<i32>;
  var sclr_sint16x2 : i32;
  var sclr_sint16x4 : i32;
  var vec2_sint16x4 : vec2<i32>;
  var vec3_sint16x4 : vec3<i32>;
  var sclr_sint32x2 : i32;
  var sclr_sint32x3 : i32;
  var vec2_sint32x3 : vec2<i32>;
  var sclr_sint32x4 : i32;
  var vec2_sint32x4 : vec2<i32>;
  var vec3_sint32x4 : vec3<i32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index * 64u);
    sclr_sint8x2 = (((vec2<i32>(bitcast<i32>((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 16u))) << vec2<u32>(8u, 0u)) >> vec2<u32>(24u))).x;
    sclr_sint8x4 = (((vec4<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)])) << vec4<u32>(24u, 16u, 8u, 0u)) >> vec4<u32>(24u))).x;
    vec2_sint8x4 = (((vec4<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)])) << vec4<u32>(24u, 16u, 8u, 0u)) >> vec4<u32>(24u))).xy;
    vec3_sint8x4 = (((vec4<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)])) << vec4<u32>(24u, 16u, 8u, 0u)) >> vec4<u32>(24u))).xyz;
    sclr_sint16x2 = (((vec2<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)])) << vec2<u32>(16u, 0u)) >> vec2<u32>(16u))).x;
    sclr_sint16x4 = (((vec2<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).xxyy << vec4<u32>(16u, 0u, 16u, 0u)) >> vec4<u32>(16u))).x;
    vec2_sint16x4 = (((vec2<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).xxyy << vec4<u32>(16u, 0u, 16u, 0u)) >> vec4<u32>(16u))).xy;
    vec3_sint16x4 = (((vec2<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).xxyy << vec4<u32>(16u, 0u, 16u, 0u)) >> vec4<u32>(16u))).xyz;
    sclr_sint32x2 = vec2<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).x;
    sclr_sint32x3 = vec3<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)])).x;
    vec2_sint32x3 = vec3<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)])).xy;
    sclr_sint32x4 = vec4<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)])).x;
    vec2_sint32x4 = vec4<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)])).xy;
    vec3_sint32x4 = vec4<i32>(bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)]), bitcast<i32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)])).xyz;
  }
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{256,
                          VertexStepMode::kVertex,
                          {
                              {VertexFormat::kSint8x2, 64, 0},
                              {VertexFormat::kSint8x4, 64, 1},
                              {VertexFormat::kSint8x4, 64, 2},
                              {VertexFormat::kSint8x4, 64, 3},
                              {VertexFormat::kSint16x2, 64, 4},
                              {VertexFormat::kSint16x4, 64, 5},
                              {VertexFormat::kSint16x4, 64, 6},
                              {VertexFormat::kSint16x4, 64, 7},
                              {VertexFormat::kSint32x2, 64, 8},
                              {VertexFormat::kSint32x3, 64, 9},
                              {VertexFormat::kSint32x3, 64, 10},
                              {VertexFormat::kSint32x4, 64, 11},
                              {VertexFormat::kSint32x4, 64, 12},
                              {VertexFormat::kSint32x4, 64, 13},
                          }}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, FormatsWithVectorsResized_Shrinking_UInt) {
    auto* src = R"(
@vertex
fn main(
    @location(0)  sclr_uint8x2 :       u32 ,
    @location(1)  sclr_uint8x4 :       u32 ,
    @location(2)  vec2_uint8x4 :  vec2<u32>,
    @location(3)  vec3_uint8x4 :  vec3<u32>,
    @location(4)  sclr_uint16x2 :      u32 ,
    @location(5)  sclr_uint16x4 :      u32 ,
    @location(6)  vec2_uint16x4 : vec2<u32>,
    @location(7)  vec3_uint16x4 : vec3<u32>,
    @location(8)  sclr_uint32x2 :      u32 ,
    @location(9)  sclr_uint32x3 :      u32 ,
    @location(10) vec2_uint32x3 : vec2<u32>,
    @location(11) sclr_uint32x4 :      u32 ,
    @location(12) vec2_uint32x4 : vec2<u32>,
    @location(13) vec3_uint32x4 : vec3<u32>,
  ) -> @builtin(position) vec4<f32> {
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var sclr_uint8x2 : u32;
  var sclr_uint8x4 : u32;
  var vec2_uint8x4 : vec2<u32>;
  var vec3_uint8x4 : vec3<u32>;
  var sclr_uint16x2 : u32;
  var sclr_uint16x4 : u32;
  var vec2_uint16x4 : vec2<u32>;
  var vec3_uint16x4 : vec3<u32>;
  var sclr_uint32x2 : u32;
  var sclr_uint32x3 : u32;
  var vec2_uint32x3 : vec2<u32>;
  var sclr_uint32x4 : u32;
  var vec2_uint32x4 : vec2<u32>;
  var vec3_uint32x4 : vec3<u32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index * 64u);
    sclr_uint8x2 = (((vec2<u32>((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] << 16u)) << vec2<u32>(8u, 0u)) >> vec2<u32>(24u))).x;
    sclr_uint8x4 = (((vec4<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]) << vec4<u32>(24u, 16u, 8u, 0u)) >> vec4<u32>(24u))).x;
    vec2_uint8x4 = (((vec4<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]) << vec4<u32>(24u, 16u, 8u, 0u)) >> vec4<u32>(24u))).xy;
    vec3_uint8x4 = (((vec4<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]) << vec4<u32>(24u, 16u, 8u, 0u)) >> vec4<u32>(24u))).xyz;
    sclr_uint16x2 = (((vec2<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]) << vec2<u32>(16u, 0u)) >> vec2<u32>(16u))).x;
    sclr_uint16x4 = (((vec2<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]).xxyy << vec4<u32>(16u, 0u, 16u, 0u)) >> vec4<u32>(16u))).x;
    vec2_uint16x4 = (((vec2<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]).xxyy << vec4<u32>(16u, 0u, 16u, 0u)) >> vec4<u32>(16u))).xy;
    vec3_uint16x4 = (((vec2<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]).xxyy << vec4<u32>(16u, 0u, 16u, 0u)) >> vec4<u32>(16u))).xyz;
    sclr_uint32x2 = vec2<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]).x;
    sclr_uint32x3 = vec3<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)]).x;
    vec2_uint32x3 = vec3<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)]).xy;
    sclr_uint32x4 = vec4<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)]).x;
    vec2_uint32x4 = vec4<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)]).xy;
    vec3_uint32x4 = vec4<u32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)], tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)]).xyz;
  }
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {{{256,
                          VertexStepMode::kVertex,
                          {
                              {VertexFormat::kUint8x2, 64, 0},
                              {VertexFormat::kUint8x4, 64, 1},
                              {VertexFormat::kUint8x4, 64, 2},
                              {VertexFormat::kUint8x4, 64, 3},
                              {VertexFormat::kUint16x2, 64, 4},
                              {VertexFormat::kUint16x4, 64, 5},
                              {VertexFormat::kUint16x4, 64, 6},
                              {VertexFormat::kUint16x4, 64, 7},
                              {VertexFormat::kUint32x2, 64, 8},
                              {VertexFormat::kUint32x3, 64, 9},
                              {VertexFormat::kUint32x3, 64, 10},
                              {VertexFormat::kUint32x4, 64, 11},
                              {VertexFormat::kUint32x4, 64, 12},
                              {VertexFormat::kUint32x4, 64, 13},
                          }}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

TEST_F(VertexPullingTest, FormatsWithVectorsResized_Shrinking_Float_F32) {
    auto* src = R"(
@vertex
fn main(
    @location(0)  sclr_unorm8x2  :      f32 ,
    @location(1)  sclr_unorm8x4  :      f32 ,
    @location(2)  vec2_unorm8x4  : vec2<f32>,
    @location(3)  vec3_unorm8x4  : vec3<f32>,
    @location(4)  sclr_snorm8x2  :      f32 ,
    @location(5)  sclr_snorm8x4  :      f32 ,
    @location(6)  vec2_snorm8x4  : vec2<f32>,
    @location(7)  vec3_snorm8x4  : vec3<f32>,
    @location(8)  sclr_unorm16x2 :      f32 ,
    @location(9)  sclr_unorm16x4 :      f32 ,
    @location(10) vec2_unorm16x4 : vec2<f32>,
    @location(11) vec3_unorm16x4 : vec3<f32>,
    @location(12) sclr_snorm16x2 :      f32 ,
    @location(13) sclr_snorm16x4 :      f32 ,
    @location(14) vec2_snorm16x4 : vec2<f32>,
    @location(15) vec3_snorm16x4 : vec3<f32>,
    @location(16) sclr_float16x2 :      f32 ,
    @location(17) sclr_float16x4 :      f32 ,
    @location(18) vec2_float16x4 : vec2<f32>,
    @location(19) vec3_float16x4 : vec3<f32>,
    @location(20) sclr_float32x2 :      f32 ,
    @location(21) sclr_float32x3 :      f32 ,
    @location(22) vec2_float32x3 : vec2<f32>,
    @location(23) sclr_float32x4 :      f32 ,
    @location(24) vec2_float32x4 : vec2<f32>,
    @location(25) vec3_float32x4 : vec3<f32>,
  ) -> @builtin(position) vec4<f32> {
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    auto* expect = R"(
struct TintVertexData {
  tint_vertex_data : array<u32>,
}

@binding(0) @group(4) var<storage, read> tint_pulling_vertex_buffer_0 : TintVertexData;

@vertex
fn main(@builtin(vertex_index) tint_pulling_vertex_index : u32) -> @builtin(position) vec4<f32> {
  var sclr_unorm8x2 : f32;
  var sclr_unorm8x4 : f32;
  var vec2_unorm8x4 : vec2<f32>;
  var vec3_unorm8x4 : vec3<f32>;
  var sclr_snorm8x2 : f32;
  var sclr_snorm8x4 : f32;
  var vec2_snorm8x4 : vec2<f32>;
  var vec3_snorm8x4 : vec3<f32>;
  var sclr_unorm16x2 : f32;
  var sclr_unorm16x4 : f32;
  var vec2_unorm16x4 : vec2<f32>;
  var vec3_unorm16x4 : vec3<f32>;
  var sclr_snorm16x2 : f32;
  var sclr_snorm16x4 : f32;
  var vec2_snorm16x4 : vec2<f32>;
  var vec3_snorm16x4 : vec3<f32>;
  var sclr_float16x2 : f32;
  var sclr_float16x4 : f32;
  var vec2_float16x4 : vec2<f32>;
  var vec3_float16x4 : vec3<f32>;
  var sclr_float32x2 : f32;
  var sclr_float32x3 : f32;
  var vec2_float32x3 : vec2<f32>;
  var sclr_float32x4 : f32;
  var vec2_float32x4 : vec2<f32>;
  var vec3_float32x4 : vec3<f32>;
  {
    let buffer_array_base_0 = (tint_pulling_vertex_index * 64u);
    sclr_unorm8x2 = unpack4x8unorm((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] & 65535u)).xy.x;
    sclr_unorm8x4 = unpack4x8unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]).x;
    vec2_unorm8x4 = unpack4x8unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]).xy;
    vec3_unorm8x4 = unpack4x8unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]).xyz;
    sclr_snorm8x2 = unpack4x8snorm((tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)] & 65535u)).xy.x;
    sclr_snorm8x4 = unpack4x8snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]).x;
    vec2_snorm8x4 = unpack4x8snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]).xy;
    vec3_snorm8x4 = unpack4x8snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]).xyz;
    sclr_unorm16x2 = unpack2x16unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]).x;
    sclr_unorm16x4 = vec4<f32>(unpack2x16unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), unpack2x16unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).x;
    vec2_unorm16x4 = vec4<f32>(unpack2x16unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), unpack2x16unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).xy;
    vec3_unorm16x4 = vec4<f32>(unpack2x16unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), unpack2x16unorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).xyz;
    sclr_snorm16x2 = unpack2x16snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]).x;
    sclr_snorm16x4 = vec4<f32>(unpack2x16snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), unpack2x16snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).x;
    vec2_snorm16x4 = vec4<f32>(unpack2x16snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), unpack2x16snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).xy;
    vec3_snorm16x4 = vec4<f32>(unpack2x16snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), unpack2x16snorm(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).xyz;
    sclr_float16x2 = unpack2x16float(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]).x;
    sclr_float16x4 = vec4<f32>(unpack2x16float(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), unpack2x16float(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).x;
    vec2_float16x4 = vec4<f32>(unpack2x16float(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), unpack2x16float(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).xy;
    vec3_float16x4 = vec4<f32>(unpack2x16float(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), unpack2x16float(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).xyz;
    sclr_float32x2 = vec2<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)])).x;
    sclr_float32x3 = vec3<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)])).x;
    vec2_float32x3 = vec3<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)])).xy;
    sclr_float32x4 = vec4<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)])).x;
    vec2_float32x4 = vec4<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)])).xy;
    vec3_float32x4 = vec4<f32>(bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 16u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 17u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 18u)]), bitcast<f32>(tint_pulling_vertex_buffer_0.tint_vertex_data[(buffer_array_base_0 + 19u)])).xyz;
  }
  return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
)";

    VertexPulling::Config cfg;
    cfg.vertex_state = {
        {{256,
          VertexStepMode::kVertex,
          {
              {VertexFormat::kUnorm8x2, 64, 0},   {VertexFormat::kUnorm8x4, 64, 1},
              {VertexFormat::kUnorm8x4, 64, 2},   {VertexFormat::kUnorm8x4, 64, 3},
              {VertexFormat::kSnorm8x2, 64, 4},   {VertexFormat::kSnorm8x4, 64, 5},
              {VertexFormat::kSnorm8x4, 64, 6},   {VertexFormat::kSnorm8x4, 64, 7},
              {VertexFormat::kUnorm16x2, 64, 8},  {VertexFormat::kUnorm16x4, 64, 9},
              {VertexFormat::kUnorm16x4, 64, 10}, {VertexFormat::kUnorm16x4, 64, 11},
              {VertexFormat::kSnorm16x2, 64, 12}, {VertexFormat::kSnorm16x4, 64, 13},
              {VertexFormat::kSnorm16x4, 64, 14}, {VertexFormat::kSnorm16x4, 64, 15},
              {VertexFormat::kFloat16x2, 64, 16}, {VertexFormat::kFloat16x4, 64, 17},
              {VertexFormat::kFloat16x4, 64, 18}, {VertexFormat::kFloat16x4, 64, 19},
              {VertexFormat::kFloat32x2, 64, 20}, {VertexFormat::kFloat32x3, 64, 21},
              {VertexFormat::kFloat32x3, 64, 22}, {VertexFormat::kFloat32x4, 64, 23},
              {VertexFormat::kFloat32x4, 64, 24}, {VertexFormat::kFloat32x4, 64, 25},
          }}}};

    DataMap data;
    data.Add<VertexPulling::Config>(cfg);
    auto got = Run<VertexPulling>(src, data);

    EXPECT_EQ(expect, str(got));
}

}  // namespace
}  // namespace tint::transform
