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

#include "src/ast/assignment_statement.h"

namespace tint {
namespace ast {

AssignmentStatement::AssignmentStatement(std::unique_ptr<Expression> lhs,
                                         std::unique_ptr<Expression> rhs)
    : Statement(), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

AssignmentStatement::AssignmentStatement(const Source& source,
                                         std::unique_ptr<Expression> lhs,
                                         std::unique_ptr<Expression> rhs)
    : Statement(source), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

AssignmentStatement::~AssignmentStatement() = default;

bool AssignmentStatement::IsValid() const {
  return lhs_ != nullptr && rhs_ != nullptr;
}

void AssignmentStatement::to_str(std::ostream& out, size_t indent) const {
  make_indent(out, indent);
  out << "Assignment{" << std::endl;
  lhs_->to_str(out, indent + 2);
  out << std::endl;
  rhs_->to_str(out, indent + 2);
  out << std::endl;
  make_indent(out, indent);
  out << "}" << std::endl;
}

}  // namespace ast
}  // namespace tint
