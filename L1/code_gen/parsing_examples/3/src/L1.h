#pragma once

#include <vector>
#include <string>

namespace L1 {

  class Function{
    public:
      std::string name;
  };

  class Program{
    public:
      std::string entryPointLabel;
      std::vector<Function *> functions;
  };

}
