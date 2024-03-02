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
  const int debug = 1;

  /*
  Forward declarations.
  */

  /*
  Stack for storing the parsed tokens.
  */
  std::vector<Token*> parsed_tokens;

  /*
  Stack for storing function arguments.
  */
  std::vector<Token*> parsed_args;


  /*
  Keywords.
  */
  struct str_return : TAO_PEGTL_STRING( "return" ) {};
  struct str_define : TAO_PEGTL_STRING( "define" ) {};
  struct str_branch : TAO_PEGTL_STRING( "br" ) {};
  struct str_call : TAO_PEGTL_STRING( "call" ) {};
  struct str_print : TAO_PEGTL_STRING( "print" ) {};
  struct str_allocate : TAO_PEGTL_STRING( "allocate" ) {};
  struct str_input : TAO_PEGTL_STRING( "input" ) {};
  struct str_tuperr : TAO_PEGTL_STRING( "tuple-error" ) {};
  struct str_tenserr : TAO_PEGTL_STRING( "tensor-error" ) {};
  struct str_main : TAO_PEGTL_STRING( "@main" ) {};
  struct str_new : TAO_PEGTL_STRING( "new" ) {};
  struct str_Array : TAO_PEGTL_STRING( "Array" ) {};
  struct str_Tuple : TAO_PEGTL_STRING( "Tuple" ) {};
  struct str_array : TAO_PEGTL_STRING( "array" ) {};
  struct str_tuple : TAO_PEGTL_STRING( "tuple" ) {};
  struct str_code : TAO_PEGTL_STRING( "code" ) {};
  struct str_int64 : TAO_PEGTL_STRING( "int64" ) {};
  struct str_void : TAO_PEGTL_STRING( "void" ) {};

  /*
  Terminal symbols.
  */
  struct str_arrow : TAO_PEGTL_STRING( "<-" ) {};
  struct str_comment : TAO_PEGTL_STRING( "//" ),
  struct str_bracks: TAO_PEGTL_STRING( "[]" ),
  struct str_lesseq : TAO_PEGTL_STRING( "<=" ) {};
  struct str_less : TAO_PEGTL_STRING( "<" ) {};
  struct str_eq : TAO_PEGTL_STRING( "=" ) {};
  struct str_greatereq : TAO_PEGTL_STRING( ">=" ) {};
  struct str_greater : TAO_PEGTL_STRING( ">" ) {};
  struct str_plus : TAO_PEGTL_STRING( "+" ) {};
  struct str_minus : TAO_PEGTL_STRING( "-" ) {};
  struct str_mult : TAO_PEGTL_STRING( "*" ) {};
  struct str_and : TAO_PEGTL_STRING( "&" ) {};
  struct str_shiftl : TAO_PEGTL_STRING( "<<" ) {};
  struct str_shiftr : TAO_PEGTL_STRING( ">>" ) {};
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
  struct number:
    pegtl::seq<
      pegtl::opt<
        pegtl::sor<
          str_plus,
          str_minus
        >
      >,
      pegtl::plus< 
        pegtl::digit
      >
    > {};
  struct comment: 
    pegtl::disable<
      str_comment,
      pegtl::until< pegtl::eolf > 
    > {};
  struct spaces :
    pegtl::star< 
      pegtl::sor<
        pegtl::one< ' ' >,
        pegtl::one< '\t'>
      >
    > {};
  struct seps : 
    pegtl::star<
      pegtl::seq<
        spaces,
        pegtl::eol
      >
    > {};
  struct seps_with_comments : 
    pegtl::star< 
      pegtl::seq<
        spaces,
        pegtl::sor<
          pegtl::eol,
          comment
        >
      >
    > {};


  /*
  Terminal Rules.
  */
  struct label_rule:
    pegtl::seq<
      pegtl::one< ':' >,
      name
    > {};
  struct I_rule:
    pegtl::seq<
      pegtl::one< '@' >,
      name
    > {};
  struct var_rule:
    pegtl::seq<
      pegtl::one< '%' >,
      name
    > {};
  struct N_rule:
    pegtl::seq<
      number
    > {};
  struct op_rule:
    pegtl::sor<
      str_plus,
      str_minus,
      str_mult,
      str_and,
      str_shiftl,
      str_shiftr,
      str_lesseq,
      str_less,
      srt_eq,
      str_greatereq,
      str_greater,
    > {};


  /*
  Rules
  */

  /*
  Tokens rules.
  */
  struct u_rule:
    pegtl::sor<
      var_rule,
      I_rule,
    > {};
  struct t_rule:
    pegtl::sor<
      var_rule,
      N_rule
    > {};
  struct s_rule:
    pegtl::sor<
      t_rule,
      I_rule
    > {};
  struct args_rule:
    pegtl::seq<
      pegtl::opt< t_rule >,
      spaces,
      pegtl::star<
        pegtl::one< ',' >,
        spaces,
        arg_rule
      >
    > {};
  struct callee_rule:
    pegtl::sor<
      u_rule,
      str_print,
      str_input,
      str_tuperr,
      str_tenserr
    > {};
  struct type_rule:
    pegtl::sor<
      pegtl::seq<
        str_int64,
        pegtl::star< str_bracks >
      >,
      str_tuple,
      str_code
    > {};
  struct T_rule:
    pegtl::sor<
      t_rule,
      str_void
    > {};
  // custom tokens
  struct array_access:
    // [t]
    pegtl::seq<
      pegtl::one< '[' >,
      t_rule,
      pegtl::one< ']' >
    > {};

  /*
  Instruction rules.
  */
  struct Instruction_type_declaration_rule:
    // type var
    pegtl::seq<
      spaces,
      type_rule,
      var_rule
    > {};
  struct Instruction_operation_rule:
    // var <- t1 op t2
    pegtl::seq<
      spaces,
      var_rule,
      spaces,
      str_arrow,
      spaces,
      t_rule,
      spaces,
      op_rule,
      spaces,
      t_rule
    > {};
  struct Instruction_assignment_rule:
    // var <- s
    pegtl::seq<
      spaces,
      var_rule,
      spaces,
      str_arrow,
      spaces,
      s_rule
    > {};
  struct Instruction_load:
    // var1 <- var2[t]...
    pegtl::seq<
      spaces,
      var_rule,
      spaces,
      str_arrow,
      spaces,
      var_rule,
      pegtl::plus<
        pegtl::seq<
          spaces,
          array_access
        >
      >
    > {};
  struct Instruction_store:
    // var1[t]... <- s
    pegtl::seq<
      spaces,
      pegtl::plus<
        pegtl::seq<
          spaces,
          array_access
        >
      >,
      spaces,
      str_arrow,
      spaces,
      s_rule,
    > {};
  struct Instruction_dim_length:
    // var1 <- length var2 t
    pegtl::seq<
      spaces,
      var_rule,
      spaces,
      str_arrow,
      spaces,
      str_length,
      spaces,
      var_rule,
      spaces,
      t_rule
    > {};
  struct Instruction_length:
    // var1 <- length var2
    pegtl::seq<
      spaces,
      var_rule,
      spaces,
      str_arrow,
      spaces,
      str_length,
      spaces,
      var_rule,
    > {};
  struct Instruction_call_function_rule:
    // call callee ( args? )
    pegtl::seq<
      spaces,
      str_call,
      spaces,
      callee_rule,
      spaces,
      pegtl::one< '(' >,
      spaces,
      pegtl::opt< args_rule >,
      spaces,
      pegtl::one< ')' >
    > {};
  struct Instruction_call_function_rule:
    // call callee ( args? )
    pegtl::seq<
      spaces,
      str_call,
      spaces,
      callee_rule,
      spaces,
      pegtl::one< '(' >,
      spaces,

      spaces,
      pegtl::one< ')' >
    > {};
  struct Instruction_call_function_assignment_rule:
    // var <- call callee ( args? )
    pegtl::seq<
      spaces,
      var_rule,
      spaces,
      str_arrow,
      spaces,
      str_call,
      spaces,
      callee_rule,
      spaces,
      pegtl::one< '(' >,
      spaces,
      pegtl::opt< args_rule >,
      spaces,
      pegtl::one< ')' >
    > {};
  struct Instruction_array_initialization_rule:
    // var <- new Array( args )
    pegtl::seq<
      spaces,
      var_rule,
      spaces,
      str_arrow,
      spaces,
      str_new,
      spaces,
      str_Array,
      spaces,
      pegtl::one< '(' >,
      spaces,
      args_rule
      spaces,
      pegtl::one< ')' >,
    > {};
  struct Instruction_tuple_initialization_rule:
    // var <- new Tuple( t )
    pegtl::seq<
      spaces,
      var_rule,
      spaces,
      str_arrow,
      spaces,
      str_new,
      spaces,
      str_Tuple,
      spaces,
      pegtl::one< '(' >,
      spaces,
      t_rule,
      spaces,
      pegtl::one< ')' >,
    > {};
  

  
  /*
  Terminator rules.
  */
  
  

  















}