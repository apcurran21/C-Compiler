/*
 * SUGGESTION FROM THE CC TEAM:
 * double check the order of actions that are fired.
 * You can do this in (at least) two ways:
 * 1) by using gdb adding breakpoints to actions
 * 2) by adding printing statements in each action
 *
 * For 2), we suggest writing the code to make it straightforward to enable/disable all of them 
 * (e.g., assuming shouldIPrint is a global variable
 *    if (shouldIPrint) std::cerr << "MY OUTPUT" << std::endl;
 * )
 */
#include <sched.h>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <iterator>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <stdint.h>
#include <assert.h>

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/analyze.hpp>
#include <tao/pegtl/contrib/raw_string.hpp>

#include <L1.h>
#include <parser.h>

namespace pegtl = TAO_PEGTL_NAMESPACE;

using namespace pegtl;

namespace L1 {

  /* 
   * Grammar rules from now on.
   */
  struct name:
    pegtl::seq<
      pegtl::plus< 
        pegtl::sor<
          pegtl::alpha,
          pegtl::one< '_' >
        >
      >,
      pegtl::star<
        pegtl::sor<
          pegtl::alpha,
          pegtl::one< '_' >,
          pegtl::digit
        >
      >
    > {};

  struct label:
    pegtl::seq<
      pegtl::one<':'>,
      name
    > {};

  struct function_name_rule:
    pegtl::seq<
      pegtl::one<'@'>,
      name
    > {};

  struct number:
    pegtl::seq<
      pegtl::opt<
        pegtl::sor<
          pegtl::one< '-' >,
          pegtl::one< '+' >
        >
      >,
      pegtl::plus< 
        pegtl::digit
      >
    >{};

  struct function_name:
    label {};

  struct argument_number:
    number {};

  struct local_number:
    number {} ;

  struct comment: 
    pegtl::disable< 
      TAO_PEGTL_STRING( "//" ), 
      pegtl::until< pegtl::eolf > 
    > {};

  /*
   * Separators.
   */
  struct spaces:
    pegtl::star< 
      pegtl::sor<
        pegtl::one< ' ' >,
        pegtl::one< '\t'>
      >
    > { };

  struct seps : 
    pegtl::star<
      pegtl::seq<
        spaces,
        pegtl::eol
      >
    > { };
  struct seps_with_comments : 
    pegtl::star< 
      pegtl::seq<
        spaces,
        pegtl::sor<
          pegtl::eol,
          comment
        >
      >
    > { };

  struct Function_rule:
    pegtl::seq<
      pegtl::seq<spaces, pegtl::one< '(' >>,
      seps_with_comments,
      pegtl::seq<spaces, function_name_rule>,
      seps_with_comments,
      pegtl::seq<spaces, argument_number>,
      seps_with_comments,
      pegtl::seq<spaces, local_number>,
      seps_with_comments,
      pegtl::seq<spaces, pegtl::one< ')' >>
    > {};

  struct Functions_rule:
    pegtl::plus<
      seps_with_comments,
      Function_rule,
      seps_with_comments
    > {};

  struct entry_point_rule:
    pegtl::seq<
      seps_with_comments,
      pegtl::seq<spaces, pegtl::one< '(' >>,
      seps_with_comments,
      function_name_rule,
      seps_with_comments,
      Functions_rule,
      seps_with_comments,
      pegtl::seq<spaces, pegtl::one< ')' >>,
      seps
    > { };

  struct grammar : 
    pegtl::must< 
      entry_point_rule
    > {};

  /* 
   * Actions attached to grammar rules.
   */
  template< typename Rule >
  struct action : pegtl::nothing< Rule > {};

  template<> struct action < function_name_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      if (p.entryPointLabel.empty()){
        p.entryPointLabel = in.string();
      } else {
        auto newF = new Function();
        newF->name = in.string();
        p.functions.push_back(newF);
      }
    }
  };

  template<> struct action < argument_number > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      auto currentF = p.functions.back();
      currentF->arguments = std::stoll(in.string());
    }
  };

  template<> struct action < local_number > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      auto currentF = p.functions.back();
      currentF->locals = std::stoll(in.string());
    }
  };

  Program parse_file (char *fileName){

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
