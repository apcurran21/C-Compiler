#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/analyze.hpp>
#include <tao/pegtl/contrib/raw_string.hpp>

#include "parser.h"

namespace pegtl = TAO_PEGTL_NAMESPACE;

using namespace pegtl;
using namespace std;


namespace LA {


  /*
  Debug flag.
  */
  const int debug = 1;

  /*
  Forward declarations.
  */

  /*
  Counters for temporary variables, etc.
  */
  int64_t counter = 0;

  /*
  Stack for storing the parsed items.
  */
  std::vector<Item*> parsed_items;










  /*
  Program rules.
  */
  struct entry_point_rule:
    pegtl::seq<
      Functions_rule
    > {};

  /*
  Grammar rules.
  */
  struct full_grammar :
    pegtl::must<
      entry_point_rule
    > {};


  /*
  Actions.
  */
  template< typename Rule >
  struct action : pegtl::nothing< Rule > {};





  /*
  Main parser function.
  */
  Program parse_file (char *filename) {
    /* 
    Check the grammar for some possible issues.
    */
    if (pegtl::analyze< full_grammar >() != 0){
      std::cerr << "There are problems with the grammar\n";
      exit(1);
    }
    std::cerr << "No problems with the grammar.\n";

    /*
     * Parse.
     */
    file_input< > fileInput(fileName);
    Program p;
    parse< full_grammar, action >(fileInput, p);

    return p;
  }

}