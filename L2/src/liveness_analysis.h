#pragma once

#include <L2.h>

namespace L2{

  void liveness_analysis(Program p);

  // probably don't need this actually
  class LiveAnalysisVisitor : public Visitor {
    void visit();
  };

}
