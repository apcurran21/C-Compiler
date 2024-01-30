#pragma once

#include <unordered_map>
#include <string>
// #include "L2.h"

namespace L2 {

    /*
    Forward declaration of Variable and Register classes help avoid cyclic dependencies.
    */
    class Variable;
    class Register;

    /*
    Utility class that stores Variable instances, and lets clients
    "query" its database of variables.
    - If the variable doesn't exist, it allocates to heap and returns pointer.
    - If the variable exists, it returns a pointer to this instance
    */

    // define an enum so that we can tell if we're allocating a Register or Var
    enum VariableType {
        var,
        reg
    };

    class VariableAllocator {
        public:
            VariableAllocator();
            ~VariableAllocator();
            Variable* allocate_variable(std::string name, VariableType type);
        private:
            std::unordered_map<std::string, Variable*> variable_database;
    };

}