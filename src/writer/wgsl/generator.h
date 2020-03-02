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

#ifndef SRC_WRITER_WGSL_GENERATOR_H_
#define SRC_WRITER_WGSL_GENERATOR_H_

#include <string>

#include "src/writer/writer.h"

namespace tint {
namespace writer {
namespace wgsl {

/// Class to generate WGSL source from a WGSL module
class Generator : public writer::Writer {
 public:
  /// Constructor
  /// @param module the module to convert
  explicit Generator(ast::Module module);
  ~Generator() override;

  /// Generates the result data
  /// @returns true on successful generation; false otherwise
  bool Generate() override;

  /// @returns the result data
  const std::string& result() const { return result_; }

 private:
  std::string result_;
};

}  // namespace wgsl
}  // namespace writer
}  // namespace tint

#endif  // SRC_WRITER_WGSL_GENERATOR_H_
