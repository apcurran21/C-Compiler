#pragma once

#include <IR.h>

namespace IR{

  // void generate_code(Program p, Graph color_graph);
  // void generate_code(Program p, std::map<Function*, Graph*> all_graphs);
  void calculate_array(Function *f, std::ofstream &outputFile, Instruction &iptr);

}
