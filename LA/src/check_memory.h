#pragma once

#include "LA.h"

namespace LA {

    void check_program(Program& p);

    Function* check_function(Function *f); 

    std::vector<Instruction*> create_index_check(Function* f, Instruction* i, bool isTuple, int64_t index);

    std::vector<Instruction*> create_indices_check(Function* f, Instruction* i);

    std::vector<Instruction*> create_allocation_check(Instruction* i);


}