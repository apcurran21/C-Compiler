#pragma once

#include <iostream>
#include <fstream>

#include "IR.h"

namespace IR {

    Program parse_file (char *filename);
    
}