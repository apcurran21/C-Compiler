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

#include "parser.h"
#include "code_generator.h"
#include "encode.h"
#include "check_memory.h"
#include "LA.h"



void print_help (char *progName){
  std::cerr << "Usage: " << progName << " [-v] [-g 0|1] [-O 0|1|2] SOURCE" << std::endl;
  return ;
}

int main(
  int argc, 
  char **argv
  ){
  auto enable_code_generator = true;
  int32_t optLevel = 0;
  bool verbose;

  /* 
   * Check the compiler arguments.
   */
  if( argc < 2 ) {
    print_help(argv[0]);
    return 1;
  }
  int32_t opt;
  while ((opt = getopt(argc, argv, "vg:O:")) != -1) {
    switch (opt){
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
  auto p = LA::parse_file(argv[optind]);

  /*
   * Code optimizations (optional)
   */

  /* 
   * Print the source program.
   */
  if (verbose){
    std::cout << "\n\n" << std::endl;
    std::cout << "Verbose mode selected, check output to verify the parsed program.\n------------------------------\n";
    
    // p.print();

    std::cout << "Done.\n\n";
  }


  /*
  Encode the program according to our encoding scheme.
  */
  LA::encode_program(p);


  /*
  Check the program for memory/other errors.
  */
  LA::check_program(p);

  /*
  Break the program into basic blocks.
  */



  /*
   * Generate LA code.
   */
  if (enable_code_generator){
    LA::generate_code(p);
  }

  return 0;
}