// #include <variable_allocator.h>
#include "variable_allocator.h"

namespace L2 {

    VariableAllocator::VariableAllocator() {}

    Variable* VariableAllocator::allocate_variable(std::string var_name) {
        auto loc = variable_database.find(var_name);

        if (loc != variable_database.end()) {
            // Variable was already allocated!
            return variable_database[var_name];
        }
        else {
            // Variable was not allocated, need to create
            auto new_var = new Variable(var_name);
            return new_var;     // new_var is a pointer 
        }
    }


}