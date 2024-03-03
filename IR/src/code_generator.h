#pragma once

#include "IR.h"
#include "calculateArray.h"

namespace IR{

  // void generate_code(Program p, Graph color_graph);
  // void generate_code(Program p, std::map<Function*, Graph*> all_graphs);
  void generate_code(Program& p);

}
