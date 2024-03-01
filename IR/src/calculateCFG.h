#pragma once
#include <set>
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <tuple>
#include "IR.h"
namespace IR {

    extern int const debug;
    
    class calculateCFG : ProgramVisitor {
    public:
        void forProgram(Program *p);
        void forFunction(Function *f);
        void forBlock(Block *b); // Add a method for handling Block objects
    };
    
}