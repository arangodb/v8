// Copyright 2023 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_COMPILER_TURBOSHAFT_DEAD_CODE_ELIMINATION_PHASE_H_
#define V8_COMPILER_TURBOSHAFT_DEAD_CODE_ELIMINATION_PHASE_H_

#include "src/compiler/turboshaft/phase.h"

namespace v8::internal::compiler::turboshaft {

struct DeadCodeEliminationPhase {
  DECL_TURBOSHAFT_PHASE_CONSTANTS(DeadCodeElimination)

  void Run(Zone* temp_zone);
};

}  // namespace v8::internal::compiler::turboshaft

#endif  // V8_COMPILER_TURBOSHAFT_DEAD_CODE_ELIMINATION_PHASE_H_
