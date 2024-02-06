#pragma once

#include <L2.h>

namespace L2{

  In_Out_Store liveness_analysis(Program *p);

  // probably don't need this actually
  class LiveAnalysisVisitor : public Visitor {
    void visit();
  };

}
