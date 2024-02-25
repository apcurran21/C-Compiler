#pragma once

#include <L2.h>

namespace L2{

  // LivenessResult liveness_analysis(Program *p, bool print);
  // Curr_F_Liveness liveness_analysis(Program *p, int function_index, Gen_Kill_Store gen_kill_sets, In_Out_Store in_out_sets, bool print);
  // Curr_F_Liveness liveness_analysis(Function* fptr, bool print);
    Curr_F_Liveness liveness_analysis(Function* fptr);

  /*
  
  */
  void print_liveness(Function* fptr, Curr_F_Liveness liveness_results);

}
