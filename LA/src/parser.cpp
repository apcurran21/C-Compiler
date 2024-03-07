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














}