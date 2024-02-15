#pragma once

#include <L2.h>

namespace L2{

  // void generate_code(Program p, Graph color_graph);
  void generate_code(Program p, std::map<Function*, Graph*> all_graphs);

}
