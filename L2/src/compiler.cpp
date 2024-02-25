#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <iterator>
#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <assert.h>
#include <tuple>
// #include "L2/src/parser.h"
#include "parser.h"
#include "liveness_analysis.h"
#include "interference_graph.h"
#include "spill.h"
#include "graph_coloring.h"
#include "graph_coloring_alt.h"
#include "code_generator.h"
#include "spill_code_generator.h"
#include "L2.h"
#include "spill.h"

/*
Debugging
*/
int printdebug = 0;

void print_help (char *progName){
  // std::cerr << "Usage: " << progName << " [-v] [-g 0|1] [-O 0|1|2] [-s] [-l] [-i] SOURCE" << std::endl;
  std::cerr << "Usage: " << progName << " [-v] [-g 0|1] [-O 0|1|2] [-s] [-l] [-i] [-c] SOURCE" << std::endl;
  // ^ pass the argument c to run the graph coloring.
  return ;
}

int main(
  int argc, 
  char **argv
  ){
  auto enable_code_generator = true;
  auto spill_only = false;
  auto interference_only = false;
  auto liveness_only = false;
  auto run_color = false; // extra debug
  int32_t optLevel = 3;

  /* 
   * Check the compiler arguments.
   */
  auto verbose = false;
  if( argc < 2 ) {
    print_help(argv[0]);
    return 1;
  }
  int32_t opt;
  int64_t functionNumber = -1;
  while ((opt = getopt(argc, argv, "vg:O:slic")) != -1) {
    switch (opt){

      case 'l':
        liveness_only = true;
        break ;

      case 'i':
        interference_only = true;
        break ;

      case 's':
        spill_only = true;
        break ;

      case 'O':
        optLevel = strtoul(optarg, NULL, 0);
        break ;

      case 'g':
        enable_code_generator = (strtoul(optarg, NULL, 0) == 0) ? false : true ;
        break ;

      case 'v':
        verbose = true;
        break ;

      // our extra debug
      case 'c':
        run_color = true;
        break ;

      default:
        print_help(argv[0]);
        return 1;
    }
  }

  /*
   * Parse the input file.
   */
  L2::Program p;
  if (spill_only){

    /* 
     * Parse an L2 function and the spill arguments.
     */
    p = L2::parse_spill_file(argv[optind]);
 
  } else if (liveness_only){

    /*
     * Parse an L2 function.
     */
    p = L2::parse_function_file(argv[optind]);
    
  } else if (interference_only || run_color){

    /*
     * Parse an L2 function.
     */
    p = L2::parse_function_file(argv[optind]);

  } else {

    /* 
     * Parse the L2 program.
     */
    p = L2::parse_file(argv[optind]);

  }

  /*
  Special cases.
  */
  if (spill_only) {
    std::set<std::string> all_changed;
    L2::Program p_out;
    p_out.entryPointLabel = p.entryPointLabel;
    auto replacementVar = p.variables[p.variables.size() - 2];
    while (!p.functions.empty()) {
      L2::Function* fptr = p.functions.front();
      p.functions.erase(p.functions.begin());
      
      std::tuple<std::set<std::string>, L2::Function*,int> resultTuple = L2::spillForL2(p.functions[0], replacementVar, -1,0);
      auto changed = std::get<0>(resultTuple);
      auto newFunction = std::get<1>(resultTuple);
      
      all_changed.insert(changed.begin(), changed.end());
      p_out.functions.push_back(newFunction);
    }
    L2::generate_spill_code(p_out, all_changed);

    return 0;
  }

  if (liveness_only) {
    while (!p.functions.empty()) {
      L2::Function* fptr = p.functions.front();
      p.functions.erase(p.functions.begin());

      L2::Curr_F_Liveness curr_f_res = L2::liveness_analysis(fptr);
      print_liveness(fptr, curr_f_res);
    }

    return 0;
  }

  if (interference_only) {
    while (!p.functions.empty()) {
      L2::Function* fptr = p.functions.front();
      p.functions.erase(p.functions.begin());

      L2::Curr_F_Liveness curr_f_res = L2::liveness_analysis(fptr);
      L2::Graph* interference_graph = L2::build_graph(fptr, curr_f_res);
      interference_graph->printGraph();
    }
    return 0;
  }

  if (run_color) {

    return 0;
  }

  if (enable_code_generator) {
    
    /*
    Initialize the output program that will be passed to the code generator.
    */
    L2::Program p_out;
    p_out.entryPointLabel = p.entryPointLabel;

    /*
    Perform code analysis and variable allocation for each function in the original program.
    Append the results to the output program.
    */
    while (!p.functions.empty()) {
        L2::Function* fptr = p.functions.front();

        p.functions.erase(p.functions.begin());

        L2::Function* fptr_out = L2::allocate_registers(fptr);
        
        p_out.functions.push_back(fptr_out);
    }

    /*
    Generate the L1 code.
    */
    L2::generate_code(p_out);

    return 0;
  }
}
