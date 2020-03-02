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

#include "src/ast/cast_expression.h"

namespace tint {
namespace ast {

CastExpression::CastExpression(type::Type* type,
                               std::unique_ptr<Expression> expr)
    : Expression(), type_(type), expr_(std::move(expr)) {}

CastExpression::CastExpression(const Source& source,
                               type::Type* type,
                               std::unique_ptr<Expression> expr)
    : Expression(source), type_(type), expr_(std::move(expr)) {}

CastExpression::~CastExpression() = default;

bool CastExpression::IsValid() const {
  return type_ != nullptr && expr_ != nullptr;
}

void CastExpression::to_str(std::ostream& out, size_t indent) const {
  out << "cast<" << type_->type_name() << ">(";
  expr_->to_str(out, indent);
  out << ")";
}

}  // namespace ast
}  // namespace tint
