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

#ifndef SRC_AST_VARIABLE_STATEMENT_H_
#define SRC_AST_VARIABLE_STATEMENT_H_

#include <memory>
#include <utility>

#include "src/ast/expression.h"
#include "src/ast/statement.h"
#include "src/ast/variable.h"

namespace tint {
namespace ast {

/// A variable statement
class VariableStatement : public Statement {
 public:
  /// Constructor
  /// @param variable the variable
  explicit VariableStatement(std::unique_ptr<Variable> variable);
  /// Constructor
  /// @param source the initializer source
  /// @param variable the variable
  VariableStatement(const Source& source, std::unique_ptr<Variable> variable);
  /// Move constructor
  VariableStatement(VariableStatement&&) = default;
  ~VariableStatement() override;

  /// Sets the variable
  /// @param variable the variable to set
  void set_variable(std::unique_ptr<Variable> variable) {
    variable_ = std::move(variable);
  }
  /// @returns the variable
  Variable* variable() const { return variable_.get(); }

  /// @returns true if this is an variable statement
  bool IsVariable() const override { return true; }

  /// @returns true if the node is valid
  bool IsValid() const override;

  /// Writes a representation of the node to the output stream
  /// @param out the stream to write to
  /// @param indent number of spaces to indent the node when writing
  void to_str(std::ostream& out, size_t indent) const override;

 private:
  VariableStatement(const VariableStatement&) = delete;

  std::unique_ptr<Variable> variable_;
};

}  // namespace ast
}  // namespace tint

#endif  // SRC_AST_VARIABLE_STATEMENT_H_
