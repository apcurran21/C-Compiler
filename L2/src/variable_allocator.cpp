// #include <variable_allocator.h>
#include "variable_allocator.h"

namespace L2 {

    VariableAllocator::VariableAllocator() {}

    VariableAllocator::~VariableAllocator() {}

    Variable* VariableAllocator::allocate_variable(std::string name, VariableType type) {
        auto loc = variable_database.find(name);

        if (loc != variable_database.end()) {
            // Variable was already allocated!
            return variable_database[name];
        }
        else {
            // Variable was not allocated, need to create
            switch (type) {
                case var:
                    auto new_var = new Variable(name);
                    variable_database[name] = new_var;
                    return new_var;
                    break;
                case reg:
                    auto new_reg = new Register(name);
                    variable_database[name] = new_reg;
                    return new_reg;
                    break;
            }
        }
    }
    
}