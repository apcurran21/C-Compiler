#pragma once

#include <L2.h>

namespace L2 {

    /*
    Utility class that stores Variable instances, and lets clients
    "query" its database of variables.
    - If the variable doesn't exist, it allocates to heap and returns pointer.
    - If the variable exists, it returns a pointer to this instance
    */
    class VariableAllocator {
        public:
            VariableAllocator();
            Variable* allocate_variable(std::string var_name);
        private:
            std::unordered_map<std::string, Variable*> variable_database;
    };

}