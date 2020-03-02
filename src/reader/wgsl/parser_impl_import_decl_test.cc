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

#include "gtest/gtest.h"
#include "src/reader/wgsl/parser_impl.h"

namespace tint {
namespace reader {
namespace wgsl {

using ParserImplTest = testing::Test;

TEST_F(ParserImplTest, ImportDecl_Import) {
  ParserImpl p{R"(import "GLSL.std.450" as glsl)"};

  auto import = p.import_decl();
  ASSERT_NE(import, nullptr);
  ASSERT_FALSE(p.has_error()) << p.error();

  EXPECT_EQ("GLSL.std.450", import->path());
  EXPECT_EQ("glsl", import->name());
  EXPECT_EQ(1, import->line());
  EXPECT_EQ(1, import->column());
}

TEST_F(ParserImplTest, ImportDecl_Import_WithNamespace) {
  ParserImpl p{R"(import "GLSL.std.450" as std::glsl)"};
  auto import = p.import_decl();
  ASSERT_NE(import, nullptr);
  ASSERT_FALSE(p.has_error()) << p.error();
  EXPECT_EQ("std::glsl", import->name());
}

TEST_F(ParserImplTest, ImportDecl_Invalid_MissingPath) {
  ParserImpl p{R"(import as glsl)"};
  auto import = p.import_decl();
  ASSERT_EQ(import, nullptr);
  ASSERT_TRUE(p.has_error());
  EXPECT_EQ(p.error(), "1:8: missing path for import");
}

TEST_F(ParserImplTest, ImportDecl_Invalid_EmptyPath) {
  ParserImpl p{R"(import "" as glsl)"};
  auto import = p.import_decl();
  ASSERT_EQ(import, nullptr);
  ASSERT_TRUE(p.has_error());
  EXPECT_EQ(p.error(), "1:8: import path must not be empty");
}

TEST_F(ParserImplTest, ImportDecl_Invalid_NameMissingTerminatingIdentifier) {
  ParserImpl p{R"(import "GLSL.std.450" as glsl::)"};
  auto import = p.import_decl();
  ASSERT_EQ(import, nullptr);
  ASSERT_TRUE(p.has_error());
  EXPECT_EQ(p.error(), "1:32: invalid name for import");
}

TEST_F(ParserImplTest, ImportDecl_Invalid_NameInvalid) {
  ParserImpl p{R"(import "GLSL.std.450" as 12glsl)"};
  auto import = p.import_decl();
  ASSERT_EQ(import, nullptr);
  ASSERT_TRUE(p.has_error());
  EXPECT_EQ(p.error(), "1:26: invalid name for import");
}

TEST_F(ParserImplTest, ImportDecl_Invalid_MissingName) {
  ParserImpl p{R"(import "GLSL.std.450" as)"};
  auto import = p.import_decl();
  ASSERT_EQ(import, nullptr);
  ASSERT_TRUE(p.has_error());
  EXPECT_EQ(p.error(), "1:25: missing name for import");
}

TEST_F(ParserImplTest, ImportDecl_Invalid_MissingAs) {
  ParserImpl p{R"(import "GLSL.std.450" glsl)"};
  auto import = p.import_decl();
  ASSERT_EQ(import, nullptr);
  ASSERT_TRUE(p.has_error());
  EXPECT_EQ(p.error(), "1:23: missing 'as' for import");
}

}  // namespace wgsl
}  // namespace reader
}  // namespace tint
