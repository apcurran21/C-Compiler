#pragma once

#include <string>
#include "L2.h" 

namespace L2 {
    /**
     * Performs spilling for a variable in an L2 program.
     * 
     * @param p The L2 program to perform spilling in.
     * @param spilledVar The variable to be spilled.
     */
    // bool spillForL2(Program &p, Variable* spilledVar);
    std::set<std::string> spillForL2(Function* f, Variable* spilledVar, int spill_count);
}
