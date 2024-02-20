// #include <variable_allocator.h>
#include "variable_allocator.h"
#include "L2.h"

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
            Variable* new_variable;
            switch (type) {
                case var:
                    new_variable = new Variable(name);
                    variable_database[name] = new_variable;
                    break;
                case reg:
                    new_variable = new Register(name);
                    variable_database[name] = new_variable;
                    break;
            }
            return new_variable;
        }
    }
    bool VariableAllocator::remove_variable(std::string name){
        return variable_database.erase(name);
    }
    
}