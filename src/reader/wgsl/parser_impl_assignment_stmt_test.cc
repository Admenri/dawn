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
#include "src/ast/array_accessor_expression.h"
#include "src/ast/assignment_statement.h"
#include "src/ast/const_initializer_expression.h"
#include "src/ast/identifier_expression.h"
#include "src/ast/int_literal.h"
#include "src/ast/literal.h"
#include "src/ast/member_accessor_expression.h"
#include "src/reader/wgsl/parser_impl.h"

namespace tint {
namespace reader {
namespace wgsl {

using ParserImplTest = testing::Test;

TEST_F(ParserImplTest, AssignmentStmt_Parses_ToVariable) {
  ParserImpl p{"a = 123"};
  auto e = p.assignment_stmt();
  ASSERT_FALSE(p.has_error()) << p.error();
  ASSERT_NE(e, nullptr);

  ASSERT_TRUE(e->IsAssign());
  ASSERT_NE(e->lhs(), nullptr);
  ASSERT_NE(e->rhs(), nullptr);

  ASSERT_TRUE(e->lhs()->IsIdentifier());
  auto ident = e->lhs()->AsIdentifier();
  ASSERT_EQ(ident->name().size(), 1);
  EXPECT_EQ(ident->name()[0], "a");

  ASSERT_TRUE(e->rhs()->IsInitializer());
  ASSERT_TRUE(e->rhs()->AsInitializer()->IsConstInitializer());

  auto init = e->rhs()->AsInitializer()->AsConstInitializer();
  ASSERT_NE(init->literal(), nullptr);
  ASSERT_TRUE(init->literal()->IsInt());
  EXPECT_EQ(init->literal()->AsInt()->value(), 123);
}

TEST_F(ParserImplTest, AssignmentStmt_Parses_ToMember) {
  ParserImpl p{"a.b.c[2].d = 123"};
  auto e = p.assignment_stmt();
  ASSERT_FALSE(p.has_error()) << p.error();
  ASSERT_NE(e, nullptr);

  ASSERT_TRUE(e->IsAssign());
  ASSERT_NE(e->lhs(), nullptr);
  ASSERT_NE(e->rhs(), nullptr);

  ASSERT_TRUE(e->rhs()->IsInitializer());
  ASSERT_TRUE(e->rhs()->AsInitializer()->IsConstInitializer());
  auto init = e->rhs()->AsInitializer()->AsConstInitializer();
  ASSERT_NE(init->literal(), nullptr);
  ASSERT_TRUE(init->literal()->IsInt());
  EXPECT_EQ(init->literal()->AsInt()->value(), 123);

  ASSERT_TRUE(e->lhs()->IsMemberAccessor());
  auto mem = e->lhs()->AsMemberAccessor();

  ASSERT_TRUE(mem->member()->IsIdentifier());
  auto ident = mem->member()->AsIdentifier();
  ASSERT_EQ(ident->name().size(), 1);
  EXPECT_EQ(ident->name()[0], "d");

  ASSERT_TRUE(mem->structure()->IsArrayAccessor());
  auto ary = mem->structure()->AsArrayAccessor();

  ASSERT_TRUE(ary->idx_expr()->IsInitializer());
  ASSERT_TRUE(ary->idx_expr()->AsInitializer()->IsConstInitializer());
  init = ary->idx_expr()->AsInitializer()->AsConstInitializer();
  ASSERT_NE(init->literal(), nullptr);
  ASSERT_TRUE(init->literal()->IsInt());
  EXPECT_EQ(init->literal()->AsInt()->value(), 2);

  ASSERT_TRUE(ary->array()->IsMemberAccessor());
  mem = ary->array()->AsMemberAccessor();
  ASSERT_TRUE(mem->member()->IsIdentifier());
  ident = mem->member()->AsIdentifier();
  ASSERT_EQ(ident->name().size(), 1);
  EXPECT_EQ(ident->name()[0], "c");

  ASSERT_TRUE(mem->structure()->IsMemberAccessor());
  mem = mem->structure()->AsMemberAccessor();

  ASSERT_TRUE(mem->structure()->IsIdentifier());
  ident = mem->structure()->AsIdentifier();
  ASSERT_EQ(ident->name().size(), 1);
  EXPECT_EQ(ident->name()[0], "a");

  ASSERT_TRUE(mem->member()->IsIdentifier());
  ident = mem->member()->AsIdentifier();
  ASSERT_EQ(ident->name().size(), 1);
  EXPECT_EQ(ident->name()[0], "b");
}

TEST_F(ParserImplTest, AssignmentStmt_MissingEqual) {
  ParserImpl p{"a.b.c[2].d 123"};
  auto e = p.assignment_stmt();
  ASSERT_TRUE(p.has_error());
  ASSERT_EQ(e, nullptr);
  EXPECT_EQ(p.error(), "1:12: missing = for assignment");
}

TEST_F(ParserImplTest, AssignmentStmt_InvalidLHS) {
  ParserImpl p{"if (true) {} = 123"};
  auto e = p.assignment_stmt();
  ASSERT_FALSE(p.has_error()) << p.error();
  ASSERT_EQ(e, nullptr);
}

TEST_F(ParserImplTest, AssignmentStmt_InvalidRHS) {
  ParserImpl p{"a.b.c[2].d = if (true) {}"};
  auto e = p.assignment_stmt();
  ASSERT_TRUE(p.has_error());
  ASSERT_EQ(e, nullptr);
  EXPECT_EQ(p.error(), "1:14: unable to parse right side of assignment");
}

}  // namespace wgsl
}  // namespace reader
}  // namespace tint
