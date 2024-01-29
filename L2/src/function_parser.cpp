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
  Parsed items stack
  */
  std::vector<Item*> parsed_items;

  /*
  Keywords
  */
  struct str_return : TAO_PEGTL_STRING( "return" ) {};
  struct str_arrow : TAO_PEGTL_STRING( "<-" ) {};
  struct str_mem : TAO_PEGTL_STRING( "mem" ) {};
  struct str_pluseq : TAO_PEGTL_STRING( "+=" ) {};
  struct str_minuseq : TAO_PEGTL_STRING( "-=" ) {};
  struct str_multeq : TAO_PEGTL_STRING( "*=" ) {};
  struct str_ampeq : TAO_PEGTL_STRING( "&=" ) {};
  struct str_shiftl : TAO_PEGTL_STRING( "<<=" ) {};
  struct str_shiftr : TAO_PEGTL_STRING( ">>=" ) {};
  struct str_less : TAO_PEGTL_STRING( "<" ) {};
  struct str_lesseq : TAO_PEGTL_STRING( "<=" ) {};
  struct str_eq : TAO_PEGTL_STRING( "=") {};
  struct str_cjump : TAO_PEGTL_STRING( "cjump" ) {};
  struct str_goto : TAO_PEGTL_STRING( "goto" ) {};
  struct str_call : TAO_PEGTL_STRING( "call" ) {};
  struct str_print : TAO_PEGTL_STRING( "print" ) {};
  struct str_input : TAO_PEGTL_STRING( "input" ) {};
  struct str_allocate : TAO_PEGTL_STRING( "allocate" ) {};
  struct str_tuperr : TAO_PEGTL_STRING( "tuple-error" ) {};
  struct str_tenserr : TAO_PEGTL_STRING( "tensor-error" ) {};
  struct str_stackarg : TAO_PEGTL_STRING("stack-arg"){};
  struct str_at : TAO_PEGTL_STRING( "@" ) {};
  struct str_percent : TAO_PEGTL_STRING( "%" ) {};
  struct str_inc : TAO_PEGTL_STRING( "++" ) {};
  struct str_dec : TAO_PEGTL_STRING( "--" ) {};
  struct str_E : TAO_PEGTL_STRING( "--" ) {};
  struct str_rdi : TAO_PEGTL_STRING( "rdi" ) {};
  struct str_rdx : TAO_PEGTL_STRING( "rdx" ) {};
  struct str_rsi : TAO_PEGTL_STRING( "rsi" ) {};
  struct str_r8 : TAO_PEGTL_STRING( "r8" ) {};
  struct str_r9 : TAO_PEGTL_STRING( "r9" ) {};
  struct str_rax : TAO_PEGTL_STRING( "rax" ) {};
  struct str_rbx : TAO_PEGTL_STRING( "rbx" ) {};
  struct str_rbp : TAO_PEGTL_STRING( "rbp" ) {};
  struct str_r10 : TAO_PEGTL_STRING( "r10" ) {};
  struct str_r11 : TAO_PEGTL_STRING( "r11" ) {};
  struct str_r12 : TAO_PEGTL_STRING( "r12" ) {};
  struct str_r13 : TAO_PEGTL_STRING( "r13" ) {};
  struct str_r14 : TAO_PEGTL_STRING( "r14" ) {};
  struct str_r15 : TAO_PEGTL_STRING( "r15" ) {};
  struct str_rcx : TAO_PEGTL_STRING( "rcx" ) {};
  struct str_rsp : TAO_PEGTL_STRING( "rsp" ) {};


  /*
  Grammar rules
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

  struct comment: 
    pegtl::disable< 
      TAO_PEGTL_STRING( "//" ), 
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

  struct label_rule:
    pegtl::seq<
      pegtl::one<':'>,
      name
    > {};

  struct at_name_rule:
    pegtl::seq<
      str_at,
      name
    > {};

  struct variable_rule:
    pegtl::seq<
      str_percent,
      name
    > {};

  struct function_name_rule:
    at_name_rule {};

  struct I_rule:
    at_name_rule {};

  struct register_rule:
    pegtl::sor<
      str_rdi,
      str_rdx,
      str_rsi,
      str_r8,
      str_r9,
      str_rax,
      str_rbx,
      str_rbp,
      str_r10,
      str_r11,
      str_r12,
      str_r13,
      str_r14,
      str_r15,
      str_rcx,
      str_rsp
    > {};

  struct cmp_rule:
    pegtl::sor<
      str_lesseq,
      str_less,
      str_eq
    > {};

  struct sop_rule:
    pegtl::sor<
      str_shiftl,
      str_shiftr
    > {};

  struct aop_rule:
    pegtl::sor<
      str_pluseq,
      str_minuseq,
      str_multeq,
      str_ampeq
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

  struct argument_number:
    number {};


  /*
  Instruction Rules!
  */
  struct Instruction_assignment_rule:
    // w <- s
    pegtl::seq<
      register_rule,
      spaces,
      str_arrow,
      spaces,
      pegtl::sor<
        register_rule,
        number,
        label_rule,
        I_rule
      >
    > {};

  struct Inst_loadmem_rule:
    // w <- mem x M
    pegtl::seq<
      register_rule,
      spaces,
      str_arrow,
      spaces,
      str_mem,
      spaces,
      register_rule,
      spaces,
      number
    > {};

  struct Inst_storemem_rule:
    // mem x M <- s
    pegtl::seq<
      str_mem,
      spaces,
      register_rule,
      spaces,
      number,
      spaces,
      str_arrow,
      spaces,
      pegtl::sor<
        register_rule,
        number,
        label_rule,
        I_rule
      >
    > { };

  struct Inst_stackarg_rule:
    // w <- stack-arg M
    pegtl::seq<
      register_rule,
      str_arrow,
      str_stackarg,
      number
    > {};

  struct Inst_aop_rule:
    // w aop t
    pegtl::seq<
      register_rule,
      spaces,
      aop_rule,
      spaces,
      pegtl::sor<
        register_rule,
        number
      >
    > {};

  struct Inst_sop_sx_rule:
    // w sop sx
    pegtl::seq<
      register_rule,
      spaces,
      sop_rule,
      spaces,
      pegtl::sor<
        register_rule,
        variable_rule
      >
    > {};

  struct Inst_sop_N_rule:
    // w sop N
    pegtl::seq<
      register_rule,
      spaces,
      sop_rule,
      spaces,
      number
    > {};

  struct Inst_mem_plus_rule:
    // mem x M += t
    pegtl::seq<
      str_mem,
      spaces,
      register_rule,
      spaces,
      number,
      spaces,
      str_pluseq,
      spaces,
      pegtl::sor<
        register_rule,
        number
      >
    > {};

  struct Inst_mem_minus_rule:
    // mem x M -= t
    pegtl::seq<
      str_mem,
      spaces,
      register_rule,
      spaces,
      number,
      spaces,
      str_minuseq,
      spaces,
      pegtl::sor<
        register_rule,
        number
      >
    > {};

  struct Inst_plus_mem_rule:
    // w += mem x M
    pegtl::seq<
      register_rule,
      spaces,
      str_pluseq,
      spaces,
      str_mem,
      spaces,
      register_rule,
      spaces,
      number
    > {};

  struct Inst_minus_mem_rule:
    // w -= mem x M
    pegtl::seq<
      register_rule,
      spaces,
      str_minuseq,
      spaces,
      str_mem,
      spaces,
      register_rule,
      spaces,
      number
    > {};

  struct Inst_cmp_assign_rule:
    // w <- t cmp t
    pegtl::seq<
      register_rule,
      spaces,
      str_arrow,
      spaces,
      pegtl::sor<
        register_rule,
        number
      >,
      spaces,
      cmp_rule,
      spaces,
      pegtl::sor<
        register_rule,
        number
      >
    > {};

  struct Inst_cjump_rule:
    // cjump t cmp t label
    pegtl::seq<
      str_cjump,
      spaces,
      pegtl::sor<
        register_rule,
        number
      >,
      spaces,
      cmp_rule,
      spaces,
      pegtl::sor<
        register_rule,
        number
      >,
      spaces,
      label_rule
    > {};

  struct Inst_label_rule:
    // label
    label_rule {};

  struct Inst_goto_rule:
    // goto label
    pegtl::seq<
      str_goto,
      spaces,
      label_rule
    > {};

  struct Inst_return_rule:
    // return
    str_return {};

  struct call_uN_rule:
    // call u N
    pegtl::seq<
      str_call,
      spaces,
      pegtl::sor<
        register_rule,
        I_rule
      >,
      spaces,
      number
    > {};

  struct call_print_rule:
    // call print 1
    pegtl::seq<
      str_call,
      spaces,
      str_print,
      spaces,
      number
    > {};

  struct call_input_rule:
    // call input 0
    pegtl::seq<
      str_call,
      spaces,
      str_input,
      spaces,
      number
    > {};

  struct call_allocate_rule:
    // call allocate 2
    pegtl::seq<
      str_call,
      spaces,
      str_allocate,
      spaces,
      number
    > {};

  struct call_tuperr_rule:
    // call tuple-error 3
    pegtl::seq<
      str_call,
      spaces,
      str_tuperr,
      spaces,
      number
    > {};

  struct call_tenserr_rule:
    // call tensor-error F
    pegtl::seq<
      str_call,
      spaces,
      str_tenserr,
      spaces,
      number
    > {};

  struct Inst_inc_rule:
  // w ++
    pegtl::seq<
      register_rule,
      spaces,
      str_inc
    > {};

  struct Inst_dec_rule:
  // w --
    pegtl::seq<
      register_rule,
      spaces,
      str_dec
    > {};

  struct Inst_atreg_rule:
  // w @ w w E
    pegtl::seq<
      register_rule,
      spaces,
      str_at,
      spaces,
      register_rule,
      spaces,
      register_rule,
      spaces,
      number
    > {};

  struct Instruction_rule:
    pegtl::sor<
      pegtl::seq< pegtl::at<Instruction_assignment_rule>, Instruction_assignment_rule >,
      pegtl::seq< pegtl::at<Inst_loadmem_rule>, Inst_loadmem_rule >,
      pegtl::seq< pegtl::at<Inst_storemem_rule>, Inst_storemem_rule >,
      pegtl::seq< pegtl::at<Inst_stackarg_rule>, Inst_stackarg_rule >,
      pegtl::seq< pegtl::at<Inst_aop_rule>, Inst_aop_rule >,
      pegtl::seq< pegtl::at<Inst_sop_sx_rule>, Inst_sop_sx_rule >,
      pegtl::seq< pegtl::at<Inst_sop_N_rule>, Inst_sop_N_rule >,
      pegtl::seq< pegtl::at<Inst_mem_plus_rule>, Inst_mem_plus_rule >,
      pegtl::seq< pegtl::at<Inst_mem_minus_rule>, Inst_mem_minus_rule >,
      pegtl::seq< pegtl::at<Inst_plus_mem_rule>, Inst_plus_mem_rule >,
      pegtl::seq< pegtl::at<Inst_minus_mem_rule>, Inst_minus_mem_rule >,
      pegtl::seq< pegtl::at<Inst_cmp_assign_rule>, Inst_cmp_assign_rule >,
      pegtl::seq< pegtl::at<Inst_cjump_rule>, Inst_cjump_rule >,
      pegtl::seq< pegtl::at<Inst_label_rule>, Inst_label_rule >,
      pegtl::seq< pegtl::at<Inst_goto_rule>, Inst_goto_rule >,
      pegtl::seq< pegtl::at<Inst_return_rule>, Inst_return_rule >,
      pegtl::seq< pegtl::at<call_uN_rule>, call_uN_rule >,
      pegtl::seq< pegtl::at<call_print_rule>, call_print_rule >,
      pegtl::seq< pegtl::at<call_input_rule>, call_input_rule >,
      pegtl::seq< pegtl::at<call_allocate_rule>, call_allocate_rule >,
      pegtl::seq< pegtl::at<call_tuperr_rule>, call_tuperr_rule >,
      pegtl::seq< pegtl::at<call_tenserr_rule>, call_tenserr_rule >,
      pegtl::seq< pegtl::at<Inst_inc_rule>, Inst_inc_rule >,
      pegtl::seq< pegtl::at<Inst_dec_rule>, Inst_dec_rule >,
      pegtl::seq< pegtl::at<Inst_atreg_rule>, Inst_atreg_rule >,
      pegtl::seq< pegtl::at<comment>, comment>
    > {};

  struct Instructions_rule:
    pegtl::plus<
      pegtl::seq<
        seps,
        pegtl::bol,
        spaces,
        Instruction_rule,
        seps
      >
    > {};


  /*
  Function Rules!
  */
  struct Function_rule:
    pegtl::seq<
      seps_with_comments,
      pegtl::seq<spaces, pegtl::one< '(' >>,
      seps_with_comments,
      pegtl::seq<spaces, function_name_rule>,
      seps_with_comments,
      pegtl::seq<spaces, argument_number>,
      seps_with_comments,
      Instructions_rule,
      seps_with_comments,
      pegtl::seq<spaces, pegtl::one< ')' >>
    > {};

  
  /*
  Function Actions!
  */
  template<> struct action < function_name_rule > {
    template< typename Input>
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized a function_name rule" << std::endl;

      // HEY!!! we should probably do something like initializing a new VariableAllocator or something.

      auto newF = new Function();
      newF->name = in.string();
      p.functions.push_back(newF);
    }
  };


  /*
  Instruction Actions!
  */
  template< typename Rule >
  struct action : pegtl::nothing< Rule > {};







  /*
  Final Grammar Rule!
  */
  struct grammar :
    pegtl::must<
      Function_rule
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