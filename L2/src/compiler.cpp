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

#include <parser.h>
#include "liveness_analysis.h"
// #include <function_parser.h>
// #include <spill_parser.h>


void print_help (char *progName){
  std::cerr << "Usage: " << progName << " [-v] [-g 0|1] [-O 0|1|2] [-s] [-l] [-i] SOURCE" << std::endl;
  return ;
}

int main(
  int argc, 
  char **argv
  ){
  auto enable_code_generator = true;
  auto spill_only = false;
  auto interference_only = false;
  auto liveness_only = true;
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
  while ((opt = getopt(argc, argv, "vg:O:sli")) != -1) {
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
    std::cerr << "Parsing a function file ..." << std::endl;
    p = L2::parse_function_file(argv[optind]);
  } else if (interference_only){

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
   * Special cases.
   */
  if (spill_only){

    /*
     * Spill.
     */
    //TODO

    /*
     * Dump the L2 code.
     */
    //TODO

    return 0;
  }

  /*
   * Liveness test.
   */
  if (liveness_only){
    L2::liveness_analysis(&p);
    return 0;
  }

  /*
   * Interference graph test.
   */
  if (interference_only){
    //TODO
    return 0;
  }

  /*
   * Generate the target code.
   */
  if (enable_code_generator){
    //TODO
  }

  return 0;
}
