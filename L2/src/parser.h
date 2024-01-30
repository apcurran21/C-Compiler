#pragma once

#include <L2.h>

namespace L2{
  Program parse_file (char *fileName);
  Program parse_function_file (char *fileName);
  Program parse_spill_file (char *fileName);
}
