#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/analyze.hpp>
#include <tao/pegtl/contrib/raw_string.hpp>

#include "function_parser.h"

namespace pegtl = TAO_PEGTL_NAMESPACE;

using namespace pegtl;
using namespace std;


namespace L2 {

/*
    Need to define some subset of the grammar here:

    Notes:
        I don't even know why the spiller needs a parser.
        Is it to parse in the In/Out sets from std::cout?
*/


/*
    Temp grammar
*/

  struct grammar : 
    pegtl::must<

    > {};

  template< typename Rule >
  struct action : pegtl::nothing< Rule > {};




Program parse_spill_file(char * fileName) {
    /* 
     * Check the grammar for some possible issues.
    */
    if (pegtl::analyze< grammar >() != 0){
      std::cerr << "There are problems with the grammar" << std::endl;
      exit(1);
    }

    /*
     * Parse.
    */
    file_input< > fileInput(fileName);
    Program p;
    parse< grammar, action >(fileInput, p);

    return p;
}

}