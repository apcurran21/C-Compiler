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
        - Is it possible to place the bulk of our orginal parser in here, and then
        just use this parser within the full L2 parser to recognize the individual functions?
        (eg the L2 parser would only need to recognize entry rules and functions blocks, after
        which this parser could take over on the actual functions conents)
*/


/*
    Temp grammar
*/

  struct grammar : 
    pegtl::must<

    > {};



Program parse_function_file(char * fileName) {
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