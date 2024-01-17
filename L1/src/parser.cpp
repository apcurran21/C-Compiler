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

// print debugging global var (1 for printing, 0 for not)
int debug = 1;


namespace pegtl = TAO_PEGTL_NAMESPACE;

using namespace pegtl;

namespace L1 {

  /* 
   * Tokens parsed
   */ 
  std::vector<Item *> parsed_items;

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

  //////////////////////////////////////////////////////////
  /* 
   * Keywords.
   */
  #pragma region Keywords
  
  // simone's original keywords
  struct str_return : TAO_PEGTL_STRING( "return" ) {};
  struct str_arrow : TAO_PEGTL_STRING( "<-" ) {};

  // miscellaneous instruction keywords
  struct str_mem : TAO_PEGTL_STRING( "mem" ) {};
  struct str_pluseq : TAO_PEGTL_STRING( "+=" ) {};
  struct str_minuseq : TAO_PEGTL_STRING( "-=" ) {};
  struct str_multeq : TAO_PEGTL_STRING( "*=" ) {};
  struct str_ampeq : TAO_PEGTL_STRING( "&=" ) {};
  struct str_less : TAO_PEGTL_STRING( "<" ) {};
  struct str_lesseq : TAO_PEGTL_STRING( "<=" ) {};
  struct str_cjump : TAO_PEGTL_STRING( "cjump" ) {};
  struct str_goto : TAO_PEGTL_STRING( "goto" ) {};
  struct str_call : TAO_PEGTL_STRING( "call" ) {};
  struct str_print : TAO_PEGTL_STRING( "print" ) {};
  struct str_input : TAO_PEGTL_STRING( "input" ) {};
  struct str_allocate : TAO_PEGTL_STRING( "allocate" ) {};
  struct str_tuperr : TAO_PEGTL_STRING( "tuple-error" ) {};
  struct str_tenserr : TAO_PEGTL_STRING( "tensor-error" ) {};
  struct str_at : TAO_PEGTL_STRING( "@" ) {};
  struct str_inc : TAO_PEGTL_STRING( "++" ) {};
  struct str_dec : TAO_PEGTL_STRING( "--" ) {};
  struct str_E : TAO_PEGTL_STRING( "--" ) {};

  
  // register keywords
  // a 
  struct str_rdi : TAO_PEGTL_STRING( "rdi" ) {};
  struct str_rdx : TAO_PEGTL_STRING( "rdx" ) {};
  struct str_rsi : TAO_PEGTL_STRING( "rsi" ) {};
  struct str_r8 : TAO_PEGTL_STRING( "r8" ) {};
  struct str_r9 : TAO_PEGTL_STRING( "r9" ) {};
  // w 
  struct str_rax : TAO_PEGTL_STRING( "rax" ) {};
  struct str_rbx : TAO_PEGTL_STRING( "rbx" ) {};
  struct str_rbp : TAO_PEGTL_STRING( "rbp" ) {};
  struct str_r10 : TAO_PEGTL_STRING( "r10" ) {};
  struct str_r11 : TAO_PEGTL_STRING( "r11" ) {};
  struct str_r12 : TAO_PEGTL_STRING( "r12" ) {};
  struct str_r13 : TAO_PEGTL_STRING( "r13" ) {};
  struct str_r14 : TAO_PEGTL_STRING( "r14" ) {};
  struct str_r15 : TAO_PEGTL_STRING( "r15" ) {};
  //sx 
  struct str_rcx : TAO_PEGTL_STRING( "rcx" ) {};
  //rsp struct 
  struct str_rsp : TAO_PEGTL_STRING( "rsp" ) {};

  #pragma endregion

  /*
   * General Rules
   */ 
  #pragma region General Rules

  struct label_rule:
    pegtl::seq<
      pegtl::one<':'>,
      name
    > {};

  struct I_rule:
    pegtl::seq<
      str_at,
      name
    > {};

  // register rules
  struct register_rdi_rule: str_rdi {};
  struct register_rax_rule: str_rax {};
  struct register_rbx_rule: str_rbx {};
  struct register_rbp_rule: str_rbp {};
  struct register_rdx_rule: str_rdx {};
  struct register_rcx_rule: str_rcx {};
  struct register_rsi_rule: str_rsi {}; 
  struct register_r8_rule: str_r8 {};
  struct register_r9_rule: str_r9 {};
  struct register_r10_rule: str_r10 {};
  struct register_r11_rule: str_r11 {};
  struct register_r12_rule: str_r12 {};
  struct register_r13_rule: str_r13 {};
  struct register_r14_rule: str_r14 {};
  struct register_r15_rule: str_r15 {};
  struct register_rsp_rule: str_rsp {};

  //we need to add struct for all of them

  struct str_mem_rule: str_mem {};

  /* BEGINNING OF REGISTER RULES  */
  struct sx_register_rule:
    pegtl::seq<
      register_rcx_rule
    > { };

  struct a_register_rule:
    pegtl::sor<
      register_rdi_rule,
      register_rsi_rule,
      register_rdx_rule,
      sx_register_rule,
      register_r8_rule,
      register_r9_rule
    >{};
  
  struct w_register_rule:
    pegtl::sor<
      a_register_rule,
      register_rax_rule,
      register_rbx_rule,
      register_rbp_rule,
      register_r10_rule,
      register_r11_rule,
      register_r12_rule,
      register_r13_rule,
      register_r14_rule,
      register_r15_rule
    >{};

  struct x_register_rule:
    pegtl::sor<
      w_register_rule,
      register_rsp_rule
    >{};

  struct u_rule:
    pegtl::sor<
      w_register_rule,
      I_rule
    >{};

  struct N_rule:
    pegtl::sor<
      pegtl::seq<
        pegtl::opt<
          pegtl::sor<
            pegtl::one< '-' >,
            pegtl::one< '+' >
          >
        >,
        pegtl::one< '1', '2', '3', '4', '5', '6', '7', '8', '9' >, 
        pegtl::star< 
          pegtl::digit
        >
      >,
      pegtl::one< '0' >
    >{};

  struct t_rule:
    pegtl::sor<
      x_register_rule,
      N_rule
    >{};

  struct s_rule:
    pegtl::sor<
      t_rule,
      label_rule,
      I_rule
    >{};
  
  //THIS IS WHAT THE PROFESSOR GAVE IT IS USELESS
  struct register_rule:
    pegtl::sor<
      register_rdi_rule,
      register_rax_rule,
      register_rbx_rule,
      register_rbp_rule,
      register_rdx_rule,
      register_rcx_rule,
      register_rsi_rule,
      register_r8_rule,
      register_r9_rule,
      register_r10_rule,
      register_r11_rule,
      register_r12_rule,
      register_r13_rule,
      register_r14_rule,
      register_r15_rule
    > {};
  
  //This might not be the best implementation GENERALLY however this should work with L1 
  struct M_rule:
    pegtl::sor<
        pegtl::string<'0'>,
        pegtl::string<'8'>,
        pegtl::string<'1', '6'>,
        pegtl::string<'2', '4'>,
        pegtl::string<'3', '2'>,
        pegtl::string<'4', '0'>,
        pegtl::string<'4', '8'>,
        pegtl::string<'5', '6'>,
        pegtl::string<'6', '4'>,
        pegtl::string<'7', '2'>,
        pegtl::string<'8', '0'>,
        pegtl::string<'8', '8'>,
        pegtl::string<'9', '6'>,
        pegtl::string<'1', '0', '4'>,
        pegtl::string<'1', '1', '2'>,
        pegtl::string<'1', '2', '0'>,
        pegtl::string<'1', '2', '8'>,
        pegtl::string<'1', '3', '6'>,
        pegtl::string<'1', '4', '4'>,
        pegtl::string<'1', '5', '2'>,
        pegtl::string<'1', '6', '0'>,
        pegtl::string<'1', '6', '8'>,
        pegtl::string<'1', '7', '6'>,
        pegtl::string<'1', '8', '4'>,
        pegtl::string<'1', '9', '2'>,
        pegtl::string<'2', '0', '0'>,
        pegtl::string<'2', '0', '8'>,
        pegtl::string<'2', '1', '6'>,
        pegtl::string<'2', '2', '4'>,
        pegtl::string<'2', '3', '2'>,
        pegtl::string<'2', '4', '0'>,
        pegtl::string<'2', '4', '8'>,
        pegtl::string<'2', '5', '6'>
    >
  {};

  struct F_rule:
    pegtl::one<'1','3','4'>
    {};
  
  struct E_rule:
    pegtl::one<'1','2','4','8'>
    {};

  //May conflict with the SOP rule
  struct cmp_rule:
    pegtl::sor<
      pegtl::one<'<'>,
      pegtl::string<'<','='>,
      pegtl::one<'='>
    > {};

  struct sop_rule:
    pegtl::sor<
      pegtl::string<'<','<','='>,
      pegtl::string<'>','>','='>
    >{};

  struct aop_rule:
    pegtl::sor<
      str_pluseq,
      str_minuseq,
      str_multeq,
      str_ampeq
    >{};
  
  struct function_name:
    label_rule {};

  struct argument_number:
    N_rule {};

  struct local_number:
    N_rule {} ;

  struct comment: 
    pegtl::disable< 
      TAO_PEGTL_STRING( "//" ), 
      pegtl::until< pegtl::eolf > 
    > {};

  #pragma endregion Registers, Names, Numbers, etc.

  /*
   * Separators.
   */
  #pragma region Separators

  struct spaces :
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
  
  #pragma endregion spaces, seps, seps_with_comments

  /*
  * Instructions.
  */
  #pragma region Instruction Rules

  /* Isaac/Andy new rules 
  */

  struct Inst_loadmem_rule:
  // w <- mem x M
    pegtl::seq<
      w_register_rule,
      spaces,
      str_arrow,
      spaces,
      str_mem_rule,
      spaces,
      x_register_rule,
      spaces,
      M_rule
    > {};

  struct Inst_storemem_rule:
  // mem x M <- s
    pegtl::seq<
      str_mem_rule,
      spaces,
      x_register_rule,
      spaces,
      M_rule,
      spaces,
      str_arrow,
      spaces,
      s_rule
    > { };

  struct Inst_arith_rule:
  // w aop t
    pegtl::seq<
      w_register_rule,
      spaces,
      aop_rule,
      spaces,
      t_rule
    > { };

  struct Inst_shift_reg_rule:
  // w sop sx
    pegtl::seq<
      w_register_rule,
      spaces,
      sop_rule,
      spaces,
      sx_register_rule
    > { };

  struct Inst_shift_num_rule:
  // w sop N
    pegtl::seq<
      w_register_rule,
      spaces,
      sop_rule,
      spaces,
      N_rule
    > { };

  struct Inst_mem_plus_rule:
  // mem x M += t
    pegtl::seq<
      str_mem_rule,
      spaces,
      x_register_rule,
      spaces,
      M_rule,
      spaces,
      str_pluseq,
      spaces,
      t_rule
    > { };

  struct Inst_mem_minus_rule:
  // mem x M -= t
    pegtl::seq<
      str_mem_rule,
      spaces,
      x_register_rule,
      spaces,
      M_rule,
      spaces,
      str_minuseq,
      spaces,
      t_rule
    > { };

  struct Inst_plus_mem_rule:
  // w += mem x M
    pegtl::seq<
      w_register_rule,
      spaces,
      str_pluseq,
      spaces,
      str_mem_rule,
      spaces,
      x_register_rule,
      spaces,
      M_rule
    > { };

  struct Inst_minus_mem_rule:
  // w -= mem x M
    pegtl::seq<
      w_register_rule,
      spaces,
      str_minuseq,
      spaces,
      str_mem_rule,
      spaces,
      x_register_rule,
      spaces,
      M_rule
    > { };

  struct Inst_cmp_assign_rule:  // andy start
  // w <- t cmp t
    pegtl::seq<
      w_register_rule,
      spaces,
      str_arrow,
      spaces,
      t_rule,
      spaces,
      cmp_rule,
      spaces,
      t_rule
    > { };

  struct Inst_cjump_rule:
  // cjump t cmp t label
    pegtl::seq<
      str_cjump,
      spaces,
      t_rule,
      spaces,
      cmp_rule,
      spaces,
      t_rule,
      spaces,
      label_rule
    > { };

  struct Inst_label_rule:
  // label
    pegtl::seq<
      label_rule
    > { };

  struct Inst_goto_rule:
  // goto label
    pegtl::seq<
      str_goto,
      spaces,
      label_rule
    > { };

  struct Inst_return_rule:
  // return
    pegtl::seq<
      str_return
    > { };

  // TODO:: make a decision about the series of call instructions and add them here
  struct call_uN_rule:
    pegtl::seq<
      str_call,
      spaces,
      u_rule,
      spaces,
      N_rule
    > {};
  struct call_print_rule:
    pegtl::seq<
      str_call,
      spaces,
      str_print,
      spaces,
      pegtl::one<1>
    > {};
  struct call_input_rule:
    pegtl::seq<
      str_call,
      spaces,
      str_input,
      spaces,
      pegtl::one<0>
    > {};
  struct call_allocate_rule:
    pegtl::seq<
      str_call,
      spaces,
      str_allocate,
      spaces,
      pegtl::one<2>
    > {};
  struct call_tuperr_rule:
    pegtl::seq<
      str_call,
      spaces,
      str_tuperr,
      spaces,
      pegtl::one<3>
    > {};
  struct call_tenserr_rule:
    pegtl::seq<
      str_call,
      spaces,
      str_tenserr,
      spaces,
      pegtl::one<'F'>
    > {};

  struct Inst_inc_rule:
  // w ++
    pegtl::seq<
      w_register_rule,
      spaces,
      str_inc
    > {};

  struct Inst_dec_rule:
  // w --
    pegtl::seq<
      w_register_rule,
      spaces,
      str_dec
    > {};

  struct Inst_atreg_rule:
  // w @ w w E
    pegtl::seq<
      w_register_rule,
      spaces,
      w_register_rule,
      spaces,
      w_register_rule,
      spaces,
      E_rule
    > { };

  /*
  * Simone's originals
  */

  struct Instruction_return_rule:
    pegtl::seq<
      str_return
    > { };

  
  struct Instruction_assignment_rule:
    pegtl::seq<
      w_register_rule,
      spaces,
      str_arrow,
      spaces,
      s_rule
    > { };

  struct Instruction_rule:
    pegtl::sor<
      // our defined rules
      pegtl::seq< pegtl::at<Inst_loadmem_rule>, Inst_loadmem_rule >,
      pegtl::seq< pegtl::at<Inst_storemem_rule>, Inst_storemem_rule >,
      pegtl::seq< pegtl::at<Inst_arith_rule>, Inst_arith_rule >,
      pegtl::seq< pegtl::at<Inst_shift_reg_rule>, Inst_shift_reg_rule >,
      pegtl::seq< pegtl::at<Inst_shift_num_rule>, Inst_shift_num_rule >,
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
      // simone's defined rules
      pegtl::seq< pegtl::at<Instruction_assignment_rule>, Instruction_assignment_rule         >,
      pegtl::seq< pegtl::at<Instruction_return_rule>, Instruction_return_rule             >,
      pegtl::seq< pegtl::at<comment>, comment>
    > { };

  struct Instructions_rule:
    pegtl::plus<
      pegtl::seq<
        seps,
        pegtl::bol,
        spaces,
        Instruction_rule,
        seps
      >
    > { };

  #pragma endregion Instruction_return_rule, Instruction_assignment_rule, Instruction_rule, Instruction_rules, Inst_loadmem_rule


  /*
  * Functions.
  */
  #pragma region Function Rules

  struct Function_rule:
    pegtl::seq<
      pegtl::seq<spaces, pegtl::one< '(' >>,
      seps_with_comments,
      pegtl::seq<spaces, I_rule>,
      seps_with_comments,
      pegtl::seq<spaces, argument_number>,
      seps_with_comments,
      pegtl::seq<spaces, local_number>,
      seps_with_comments,
      Instructions_rule,
      seps_with_comments,
      pegtl::seq<spaces, pegtl::one< ')' >>
    > {};

  struct Functions_rule:
    pegtl::plus<
      seps_with_comments,
      Function_rule,
      seps_with_comments
    > {};

  #pragma endregion Function_rule, Functions_rule

  struct entry_point_rule:
    pegtl::seq<
      seps_with_comments,
      pegtl::seq<spaces, pegtl::one< '(' >>,
      seps_with_comments,
      I_rule,
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


  // HELPER FUNCTION TO GET REGISTER ID
  RegisterID stringToRegisterID(const std::string& str) {
    if (str == "rdi") return RegisterID::rdi;
    if (str == "rsi") return RegisterID::rsi;
    if (str == "rdx") return RegisterID::rdx;
    if (str == "rcx") return RegisterID::rcx;
    if (str == "r8")  return RegisterID::r8;
    if (str == "r9")  return RegisterID::r9;
    if (str == "rax") return RegisterID::rax;
    if (str == "rbx") return RegisterID::rbx;
    if (str == "rbp") return RegisterID::rbp;
    if (str == "r10") return RegisterID::r10;
    if (str == "r11") return RegisterID::r11;
    if (str == "r12") return RegisterID::r12;
    if (str == "r13") return RegisterID::r13;
    if (str == "r14") return RegisterID::r14;
    if (str == "r15") return RegisterID::r15;
    if (str == "rsp") return RegisterID::rsp;

    throw std::runtime_error("Unknown register name: " + str);
  }

  template< typename Rule >
  struct action : pegtl::nothing< Rule > {};

  /*
  * Rules for debugging
    - Eg a strategy is to set an action for the entry point rule,
      which will trigger at the end of a successful program
  */
  template<> struct action < entry_point_rule> {
    template< typename Input >
    static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized a complete entry point rule, done !" << std::endl;

      // set a breakpoint here to examine the structure of the program at the end of parsing
    }
  };

  /* Simone's Original actions*/

  template<> struct action < I_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      if (p.entryPointLabel.empty()){
        p.entryPointLabel = in.string(); //This matches it with whatever our entry point function name is (in string gives u the string matched by the rule)
      } else {
        auto newF = new Function();
        newF->name = in.string();
        p.functions.push_back(newF);
        // bugfix, see explanation below
        parsed_items.pop_back();
      }

      // note that there will be an '@' token on the parsed stack, need to remove
      // NOTE - not necessarily, in the very first line of a program (ie the beginning of the entry point rule),
      //   then this will be popping from an empty vector which is undefined behavior
    }
  }; 

  template<> struct action < label_rule > { //Don't we handle basically exactly like I_rule?
    template< typename Input >
	  static void apply( const Input & in, Program & p){
        if (debug) std::cerr << "Recognized a label" << std::endl;

        auto label = new String(in.string());
        parsed_items.push_back(label);
      }
  };

  template<> struct action < argument_number > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized an arg number" << std::endl;

      // since argument number gets matched as N first, its token gets put on the stack
      // ie we should remove here
      parsed_items.pop_back();

      auto currentF = p.functions.back();
      currentF->arguments = std::stoll(in.string());
    }
  };

  template<> struct action < local_number > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized a local numbers" << std::endl;

      // same deal as the argument number case
      parsed_items.pop_back();

      auto currentF = p.functions.back();
      currentF->locals = std::stoll(in.string());
    }
  };

  template<> struct action < str_return > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized a return string" << std::endl;

      auto currentF = p.functions.back();
      auto i = new Instruction_ret();
      currentF->instructions.push_back(i);
    }
  };
  template<> struct action < str_mem_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized a mem string" << std::endl;
    }
  };

  template<> struct action < w_register_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      auto str = in.string();
      if (str != "rdi" && str != "rsi" && str != "rdx" && str != "r8" && str != "r9"){
        if (debug) std::cerr << "Recognized an 'w' register: " << in.string() << std::endl;
        RegisterID regId = stringToRegisterID(str);
        auto r = new Register(regId);
        parsed_items.push_back(r);
      } 
    }
  };
  template<> struct action < a_register_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p){
      auto str = in.string();
      if (str != "rcx"){
        if (debug) std::cerr << "Recognized an 'a' register: " << in.string() << std::endl;
        RegisterID regId = stringToRegisterID(str);
        auto r = new Register(regId);
        parsed_items.push_back(r);
      } 
    }
  };
  template<> struct action < sx_register_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized an 'sx' register: " << in.string() << std::endl;
      auto r = new Register(RegisterID::rcx);
      parsed_items.push_back(r);
    }
  };
  template<> struct action < x_register_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p){
      auto str = in.string();
      if (str != "rax" && str != "rbx" && str != "rbp" && str != "r10" && str != "r11" && str != "r12" && str != "r13" && str != "r14" && str != "r15" && str != "rdi" && str != "rsi" && str != "rdx" && str != "r8" && str != "r9" && str != "rcx"){
        if (debug) std::cerr << "Recognized an 'x' register: " << in.string() << std::endl;     
        RegisterID regId = stringToRegisterID(str);
        auto r = new Register(regId);
        parsed_items.push_back(r);
      }
    }
  };
  template<> struct action < N_rule > {
    // N rule 
    template< typename Input >
    static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized an number N: " << in.string() << std::endl;

      auto r = new Integer(std::stoi(in.string()));//No error handling needed; we know N will be a number
      parsed_items.push_back(r);
    }
  };

  template<> struct action < str_goto > {
    // goto 
    template< typename Input >
    static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized a 'goto' string: " << in.string() << std::endl;

      auto r = new String(in.string());
      parsed_items.push_back(r);
    }
  };
  template<> struct action <E_rule> {
    // E rule 
    template< typename Input >
    static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized an 'E' number: " << in.string() << std::endl;

      auto r = new Integer(std::stoi(in.string()));
      parsed_items.push_back(r);
    }
  };
  template<> struct action <F_rule> {
    // F Rule 
    template< typename Input >
    static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized an 'F' number: " << in.string() << std::endl;

      auto r = new Integer(std::stoi(in.string()));
      parsed_items.push_back(r);
    }
  };
  template<> struct action <M_rule> {
    // M rule
    template< typename Input >
    static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized an 'M' number:  " << in.string() << std::endl;
      auto r = new Integer(std::stoi(in.string()));
      parsed_items.push_back(r);
    }
  };
  template<> struct action < aop_rule > {
    // AOP Rule
    template< typename Input >
    static void apply( const Input & in, Program & p){
      auto r = new String(in.string());
      parsed_items.push_back(r);
    }
  };
  template<> struct action < sop_rule > {
    // SOP Rule
    template< typename Input >
    static void apply( const Input & in, Program & p){
      auto r = new String(in.string());
      parsed_items.push_back(r);
    }
  };
  template<> struct action < cmp_rule > {
    // CMP Rule
    template< typename Input >
    static void apply( const Input & in, Program & p){
      auto r = new String(in.string());
      parsed_items.push_back(r);
    }
  };
  template<> struct action < str_call > {
    // call action
    template< typename Input >
    static void apply( const Input & in, Program & p){
      auto r = new String(in.string());
      parsed_items.push_back(r);
    }
  };
  template<> struct action < str_print > {
    // print action
    template< typename Input >
    static void apply( const Input & in, Program & p){
      auto r = new String(in.string());
      parsed_items.push_back(r);
    }
  };
  template<> struct action < str_inc > {
    // ++ 
    template< typename Input >
    static void apply( const Input & in, Program & p){
      auto r = new String(in.string());
      parsed_items.push_back(r);
    }
  };
  template<> struct action < str_dec > {
    // --
    template< typename Input >
    static void apply( const Input & in, Program & p){
      auto r = new String(in.string());
      parsed_items.push_back(r);
    }
  };
  template<> struct action < str_at > {
    //@ 
    template< typename Input >
    static void apply( const Input & in, Program & p){
      auto r = new String(in.string());
      parsed_items.push_back(r);
    }
  };

///////////////

  template<> struct action < Instruction_assignment_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){

      if (debug) std::cerr << "Recognized 'w <- s'" << std::endl;
      
      /* 
       * Fetch the current function.
       */ 
      auto currentF = p.functions.back();

      /*
       * Fetch the last two tokens parsed.
       */
      auto src = parsed_items.back();
      parsed_items.pop_back();
      auto dst = parsed_items.back();
      parsed_items.pop_back();

      /* 
       * Create the instruction.
       */ 
      auto i = new Instruction_assignment(dst, src);

      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };

  /* Isaac/Andy actions*/
  template<> struct action < Inst_loadmem_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // w <- mem x M
      if (debug) std::cerr << "Recognized 'w <- mem x M'" << std::endl;

      auto currentF = p.functions.back();

      auto M = parsed_items.back();
      parsed_items.pop_back();
      auto x = parsed_items.back();
      parsed_items.pop_back();
      auto method = new String("mem");
      auto w = parsed_items.back();
      parsed_items.pop_back();
      /* 
       * Create the instruction.
       */ 
      auto i = new Memory_assignment(w, method, x, M);

      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };
  template<> struct action < Inst_goto_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // goto label
      auto currentF = p.functions.back();

      auto label = parsed_items.back();
      parsed_items.pop_back();

      auto go_to = parsed_items.back();
      parsed_items.pop_back();
      /* 
       * Create the instruction.
       */ 
      auto i = new goto_label_instruction(go_to, label);

      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_storemem_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // mem x M <- s

      if (debug) std::cerr << "Recognized 'mem x M <- s'" << std::endl;

      auto currentF = p.functions.back();

      auto s = parsed_items.back();
      parsed_items.pop_back();
      auto M = parsed_items.back();
      parsed_items.pop_back();
      auto method = new String("mem");
      auto x = parsed_items.back();
      parsed_items.pop_back();
      /* 
       * Create the instruction.
       */ 
      auto i = new Memory_assignment(x, method, s, M); // this is gonna be weird need to handle

      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_mem_plus_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // mem x M += t
      auto currentF = p.functions.back();

      auto t = parsed_items.back();
      parsed_items.pop_back();
      auto instruction = new String("+=");
      auto M = parsed_items.back();
      parsed_items.pop_back();
      auto method = new String("mem");
      auto x = parsed_items.back();
      parsed_items.pop_back();
      /* 
       * Create the instruction.
       */ 
      auto i = new Memory_arithmetic(x, method, x, instruction, M); // this is gonna be weird need to handle

      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_mem_minus_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // mem x M -= t
      auto currentF = p.functions.back();

      auto t = parsed_items.back();
      parsed_items.pop_back();
      auto instruction = new String("-=");
      auto M = parsed_items.back();
      parsed_items.pop_back();
      auto method = new String("mem");
      auto x = parsed_items.back();
      parsed_items.pop_back();
      /* 
       * Create the instruction.
       */ 
      auto i = new Memory_arithmetic(x, method, x, instruction, M); // this is gonna be weird need to handle

      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_plus_mem_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // w += mem x M
      auto currentF = p.functions.back();

      auto M = parsed_items.back();
      parsed_items.pop_back();
      auto x = parsed_items.back();
      parsed_items.pop_back();
      auto method = new String("mem");
      auto instruction = new String("+=");
      auto w = parsed_items.back();
      parsed_items.pop_back();
      /* 
       * Create the instruction.
       */ 
      auto i = new Memory_arithmetic(w, method, x, instruction, M); // this is gonna be weird need to handle

      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_minus_mem_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // w -= mem x M
      auto currentF = p.functions.back();

      auto M = parsed_items.back();
      parsed_items.pop_back();
      auto x = parsed_items.back();
      parsed_items.pop_back();
      auto method = new String("mem");
      auto instruction = new String("-=");
      auto w = parsed_items.back();
      parsed_items.pop_back();
      /* 
       * Create the instruction.
       */ 
      auto i = new Memory_arithmetic(w, method, x, instruction, M); // this is gonna be weird need to handle

      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_arith_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // w aop t
      auto currentF = p.functions.back();

      auto t = parsed_items.back();
      parsed_items.pop_back();
      auto method = parsed_items.back();
      parsed_items.pop_back();  
      auto w = parsed_items.back();
      parsed_items.pop_back();
      /* 
       * Create the instruction.
       */ 
      auto i = new AOP_assignment(method, w, t); // this is gonna be weird need to handle

      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_shift_reg_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // w sop sx
      auto currentF = p.functions.back();

      auto sx = parsed_items.back();
      parsed_items.pop_back();
      auto method = parsed_items.back();
      parsed_items.pop_back();  
      auto w = parsed_items.back();
      parsed_items.pop_back();
      /* 
       * Create the instruction.
       */ 
      auto i = new SOP_assignment(method, sx, w); // this is gonna be weird need to handle

      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_shift_num_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // w sop N
      auto currentF = p.functions.back();

      auto N = parsed_items.back();
      parsed_items.pop_back();
      auto method = parsed_items.back();
      parsed_items.pop_back();  
      auto w = parsed_items.back();
      parsed_items.pop_back();
      /* 
       * Create the instruction.
       */ 
      auto i = new SOP_assignment(method, w,N); // this is gonna be weird need to handle

      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };
  
  // matches w <- t cmp t
  // use naming convention w <- t1 cmp t2
  template<> struct action < Inst_cmp_assign_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      auto currentF = p.functions.back(); // pass by reference means that we access member with dot

      // need to fetch the last three tokens on the stack
      // NOTE - need to define actions for w, t, cmp that place them onto the parsed_items stack
      auto t2 = parsed_items.back();
      parsed_items.pop_back();
      auto cmp = parsed_items.back();
      parsed_items.pop_back();
      auto t1 = parsed_items.back();
      parsed_items.pop_back();
      auto w = parsed_items.back();
      parsed_items.pop_back();
      /* 
       * Create the instruction.
       */ 
      auto i = new cmp_Instruction(w, t1, cmp, t2);

      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_cjump_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      auto currentF = p.functions.back();

      auto label = parsed_items.back();
      p.functions.pop_back();
      auto t1 = parsed_items.back();
      parsed_items.pop_back();
      auto cmp = parsed_items.back();
      parsed_items.pop_back();
      auto t2 = parsed_items.back();
      parsed_items.pop_back();
      /* 
       * Create the instruction.
       */ 
      auto i = new cjump_cmp_Instruction(t1, cmp, t2, label);

      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_label_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      auto currentF = p.functions.back();

      auto label = parsed_items.back();
      parsed_items.pop_back();

      auto i = new label_Instruction(label);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < call_uN_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      auto currentF = p.functions.back();

      // call u N
      auto N = parsed_items.back();
      parsed_items.pop_back();
      auto u = parsed_items.back();
      parsed_items.pop_back();
      /* 
       * Create the instruction.
       */ 
      auto i = new Call_uN_Instruction(u,N);
      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };
  template<> struct action < call_print_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      auto currentF = p.functions.back();

      // call print 1 
      auto i = new Call_print_Instruction();
      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };
  template<> struct action < call_input_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      auto currentF = p.functions.back();

      // call input 0 
      auto i = new Call_input_Instruction();
      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };
  template<> struct action < call_allocate_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      auto currentF = p.functions.back();

      // call allocate 2
      auto i = new Call_allocate_Instruction();
      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };
  template<> struct action < call_tuperr_rule > {
    // call tuple-error 3
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      auto currentF = p.functions.back();

      auto i = new Call_tuple_Instruction();
      /* 
       * Add the just-created instruction to the current function.
       */ 
      currentF->instructions.push_back(i);
    }
  };
  template<> struct action < call_tenserr_rule > {
    // call tensor-error F 
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      auto currentF = p.functions.back();

      auto F = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Call_tenserr_Instruction(F);
      currentF->instructions.push_back(i);
    }
  };
  template<> struct action < Inst_inc_rule > {
    // w ++  
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      auto currentF = p.functions.back();

      auto symbol = parsed_items.back();
      parsed_items.pop_back();
      auto r = parsed_items.back();
      parsed_items.pop_back();
      auto i = new w_increment_decrement(r, symbol);
      currentF->instructions.push_back(i);
    }
  };
  template<> struct action < Inst_dec_rule > {
    // w --  
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      auto currentF = p.functions.back();
      
      auto symbol = parsed_items.back();
      parsed_items.pop_back();
      auto r = parsed_items.back();
      parsed_items.pop_back();
      auto i = new w_increment_decrement(r, symbol);
      currentF->instructions.push_back(i);
    }
  };
  template<> struct action < Inst_atreg_rule > {
    // w @ w w E   
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      auto currentF = p.functions.back();

      auto E = parsed_items.back();
      parsed_items.pop_back();
      auto w1 = parsed_items.back();
      parsed_items.pop_back();
      auto w2 = parsed_items.back();
      parsed_items.pop_back();
      auto w3 = parsed_items.back();
      parsed_items.pop_back();
      auto i = new w_atreg_assignment(w3,w2,w1,E);
      currentF->instructions.push_back(i);
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
