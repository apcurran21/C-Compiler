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
  auto p = L3::parse_file(argv[optind]);

  /*
   * Code optimizations (optional)
   */

  /* 
   * Print the source program.
   */
  if (verbose){
    std::cout << "\n\n" << std::endl;
    std::cout << "Verbose mode selected, check output to verify the parsed program.\n------------------------------\n";
    
    p.print();

    std::cout << "Done.\n\n";
  }

  /*
   * Generate x86_64 assembly.
   */
    if (enable_code_generator){
      std::ofstream outputFile;

      L3::buildTree(p,outputFile); //this should now be an output file 
      
      L3::Program tileL3;
      tileL3 = L3::tileTree("buildTreeOutput.L3");

      L3::globalLabelLocalizations(tileL3)
      L3::generate_code(tileL3,outputFile);

      L3::generate_code(p);
  }
  return 0;
}