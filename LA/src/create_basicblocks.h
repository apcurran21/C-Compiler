#pragma once

#include "LA.h"

namespace LA {
 
    /*
    Returns true or false based on it the given instruction is a terminator.
    */
    bool isTerminator(Instruction* i);

    /*
    Places all type declarations at the beginning of the function.
    */
    Function* move_declarations(Function *f);

    /*
    Creates a basic block structure within a given function.
    */
    Function* create_structure(Function *f);

    /*
    The big function, converts the program into IR compatible basic blocks.
    */
    void create_basicblocks(Program& p);













}