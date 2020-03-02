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

#include "src/reader/wgsl/parser_impl.h"

#include "gtest/gtest.h"
#include "src/ast/type/i32_type.h"

namespace tint {
namespace reader {
namespace wgsl {

using ParserImplTest = testing::Test;

TEST_F(ParserImplTest, Empty) {
  ParserImpl p{""};
  ASSERT_TRUE(p.Parse()) << p.error();
}

TEST_F(ParserImplTest, DISABLED_Parses) {
  ParserImpl p{R"(
import "GLSL.std.430" as glsl;

[[location 0]] var<out> gl_FragColor : vec4<f32>;

fn main() -> void {
  gl_FragColor = vec4<f32>(.4, .2, .3, 1);
}
)"};
  ASSERT_TRUE(p.Parse()) << p.error();

  auto m = p.module();
  ASSERT_EQ(1, m.imports().size());

  // TODO(dsinclair) check rest of AST ...
}

TEST_F(ParserImplTest, DISABLED_HandlesError) {
  ParserImpl p{R"(
import "GLSL.std.430" as glsl;

fn main() ->  {  # missing return type
  return;
})"};

  ASSERT_FALSE(p.Parse());
  ASSERT_TRUE(p.has_error());
  EXPECT_EQ(p.error(), "4:15: missing return type for function");
}

TEST_F(ParserImplTest, GetRegisteredType) {
  ParserImpl p{""};
  ast::type::I32Type i32;
  p.register_alias("my_alias", &i32);

  auto alias = p.get_alias("my_alias");
  ASSERT_NE(alias, nullptr);
  ASSERT_EQ(alias, &i32);
}

TEST_F(ParserImplTest, GetUnregisteredType) {
  ParserImpl p{""};
  auto alias = p.get_alias("my_alias");
  ASSERT_EQ(alias, nullptr);
}

}  // namespace wgsl
}  // namespace reader
}  // namespace tint
