#pragma once

#include <L2.h>

namespace L2{

  LivenessResult liveness_analysis(Program *p, bool print);

  // probably don't need this actually
  class LiveAnalysisVisitor : public Visitor {
    void visit();
  };

}
