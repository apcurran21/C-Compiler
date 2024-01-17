#pragma once

#include <vector>
#include <string>

namespace L1 {

  class Function{
    public:
      std::string name;
      int64_t arguments;
      int64_t locals;
  };

  class Program{
    public:
      std::string entryPointLabel;
      std::vector<Function *> functions;
  };

}
