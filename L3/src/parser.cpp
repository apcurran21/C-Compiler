#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/analyze.hpp>
#include <tao/pegtl/contrib/raw_string.hpp>

#include "parser.h"

namespace pegtl = TAO_PEGTL_NAMESPACE;

using namespace pegtl;
using namespace std;

namespace L3 {

  /*
  Debug flag.
  */
  const int debug = 0;

  /*
  Stack for storing parsed tokens.
  */
  std::vector<Item*> parsed_items;
}