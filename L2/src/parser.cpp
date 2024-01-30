#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/analyze.hpp>
#include <tao/pegtl/contrib/raw_string.hpp>

#include "parser.h"

namespace pegtl = TAO_PEGTL_NAMESPACE;

using namespace pegtl;
using namespace std;


namespace L2 {

  const int debug = 1;

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
  General Rules!
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
      pegtl::one<'1'>
    > {};

  struct call_input_rule:
    // call input 0
    pegtl::seq<
      str_call,
      spaces,
      str_input,
      spaces,
      pegtl::one<'0'>
    > {};

  struct call_allocate_rule:
    // call allocate 2
    pegtl::seq<
      str_call,
      spaces,
      str_allocate,
      spaces,
      pegtl::one<'2'>
    > {};

  struct call_tuperr_rule:
    // call tuple-error 3
    pegtl::seq<
      str_call,
      spaces,
      str_tuperr,
      spaces,
      pegtl::one<'3'>
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
  Function and Entry Point Rules!
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
      > {};

  
  /*
  General Actions!
  */
  template< typename Rule >
  struct action : pegtl::nothing< Rule > {};

  template<> struct action < I_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized an I_rule" << std::endl;

      auto name = new Name(in.string());
      parsed_items.push_back(name);
    }
  };

  template<> struct action < variable_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized variable_rule"<< std::endl;

      // 'query' the variable database basically
      // - note we should probably split this up for debugging
      auto var = p.functions.back()->variable_allocator.allocate_variable(in.string(), VariableType::var);
      parsed_items.push_back(var);
    }
  };

  template<> struct action < label_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized a label" << std::endl;

      auto label = new Label(in.string());
      parsed_items.push_back(label);
    }
  };

  template<> struct action < register_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized a register rule" << std::endl;

      // note that if the register is already in the database, then we will receive a base Variable pointer.
      // If the register has not been seen yet, then we receive a specific Register pointer.
      // Basically, at some point we will need to dynamic cast so that we can properly code generate.
      auto r = p.functions.back()->variable_allocator.allocate_variable(in.string(), VariableType::reg);
      parsed_items.push_back(r);
    }
  };

  template<> struct action  < number > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized a number rule" << std::endl;

      auto n = new Number(std::stoll(in.string()));
      parsed_items.push_back(n);
    }
  };

  // note that the following three actions are basically identical. how can we combine?
  template<> struct action < aop_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized an aop rule" << std::endl;
      auto op = new Operator(in.string());
      parsed_items.push_back(op);
    }
  };

  template<> struct action < sop_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized an sop rule" << std::endl;
      auto op = new Operator(in.string());
      parsed_items.push_back(op);
    }
  };

  template<> struct action < cmp_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized a cmp rule" << std::endl;
      auto op = new Operator(in.string());
      parsed_items.push_back(op);
    }
  };

  template<> struct action < str_inc > {
    template< typename Input >
    static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized a str_inc rule" << std::endl;
      auto op = new Operator(in.string());
      parsed_items.push_back(op);
    }
  };

  template<> struct action < str_dec > {
    template< typename Input >
    static void apply( const Input & in, Program & p){
      if (debug) std::cerr << "Recognized an str_dec rule" << std::endl;
      auto op = new Operator(in.string());
      parsed_items.push_back(op);
    }
  };


  /*
  Instruction Actions!
  */
  template<> struct action < Instruction_assignment_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p) {
      // w <- s
      if (debug) std::cerr << "Recognized w <- s" << std::endl;

      auto currentF = p.functions.back();
      auto src = parsed_items.back();
      parsed_items.pop_back();
      auto dst = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Instruction_assignment(dst, src);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_loadmem_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // w <- mem x M
      if (debug) std::cerr << "Recognized w <- mem x M" << std::endl;

      auto currentF = p.functions.back();
      auto M = parsed_items.back();
      parsed_items.pop_back();
      auto x = parsed_items.back();
      parsed_items.pop_back();
      auto w = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Memory_assignment_load(w, x, M);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_storemem_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p) {
      // mem x M <- s
      if (debug) std::cerr << "Recognized mem x M <- s" << std::endl;

      auto currentF = p.functions.back();
      auto s = parsed_items.back();
      parsed_items.pop_back();
      auto M = parsed_items.back();
      parsed_items.pop_back();
      auto x = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Memory_assignment_store(x, s, M);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_stackarg_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p) {
      // w <- stack-arg M 
      if (debug) std::cerr << "Recognized w <- stack-arg M" << std::endl;

      auto currentF = p.functions.back();
      auto M = parsed_items.back();
      parsed_items.pop_back();
      auto w = parsed_items.back();
      parsed_items.pop_back();
      auto i = new stackarg_assignment(w, M);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_aop_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // w aop t
      if (debug) std::cerr << "Recognized w aop t" << std::endl;

      auto currentF = p.functions.back();
      auto t = parsed_items.back();
      parsed_items.pop_back();
      auto method = parsed_items.back();
      parsed_items.pop_back();  
      auto w = parsed_items.back();
      parsed_items.pop_back();
      auto i = new AOP_assignment(method, w, t);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_sop_sx_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p) {
      // w sop sx
      if (debug) std::cerr << "Recognized w sop sx" << std::endl;

      auto currentF = p.functions.back();
      auto src = parsed_items.back();
      parsed_items.pop_back();
      auto method = parsed_items.back();
      parsed_items.pop_back();  
      auto w = parsed_items.back();
      parsed_items.pop_back();
      auto i = new SOP_assignment(method, w, src);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_sop_N_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p) {
      // w sop N
      if (debug) std::cerr << "Recognized w sop N" << std::endl;

      auto currentF = p.functions.back();
      auto N = parsed_items.back();
      parsed_items.pop_back();
      auto method = parsed_items.back();
      parsed_items.pop_back();  
      auto w = parsed_items.back();
      parsed_items.pop_back();
      auto i = new SOP_assignment(method, w, N);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_mem_plus_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // mem x M += t
      if (debug) std::cerr << "Recognized mem x M += t" << std::endl;

      auto currentF = p.functions.back();
      auto t = parsed_items.back();
      parsed_items.pop_back();
      auto instruction = new Operator("+=");
      auto M = parsed_items.back();
      parsed_items.pop_back();
      auto x = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Memory_arithmetic_store(x, t, instruction, M);
      currentF->instructions.push_back(i);
    }
  };
  
  template<> struct action < Inst_mem_minus_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // mem x M -= t
      if (debug) std::cerr << "Recognized mem x M -= t" << std::endl;

      auto currentF = p.functions.back();
      auto t = parsed_items.back();
      parsed_items.pop_back();
      auto instruction = new Operator("-=");
      auto M = parsed_items.back();
      parsed_items.pop_back();
      auto x = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Memory_arithmetic_store(x, t, instruction, M);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_plus_mem_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // w += mem x M
      if (debug) std::cerr << "Recognized w += mem x M" << std::endl;

      auto currentF = p.functions.back();
      auto M = parsed_items.back();
      parsed_items.pop_back();
      auto x = parsed_items.back();
      parsed_items.pop_back();
      auto instruction = new Operator("+=");
      auto w = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Memory_arithmetic_load(w, x, instruction, M);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_minus_mem_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // w -= mem x M
      if (debug) std::cerr << "Recognized w -= mem x M" << std::endl;

      auto currentF = p.functions.back();
      auto M = parsed_items.back();
      parsed_items.pop_back();
      auto x = parsed_items.back();
      parsed_items.pop_back();
      auto instruction = new Operator("-=");
      auto w = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Memory_arithmetic_load(w, x, instruction, M);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_cmp_assign_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // w <- t2 cmp t1
      if (debug) std::cerr << "Recognized w <- t2 cmp t1" << std::endl;
      
      auto currentF = p.functions.back();
      auto t1 = parsed_items.back();
      parsed_items.pop_back();
      auto cmp = parsed_items.back();
      parsed_items.pop_back();
      auto t2 = parsed_items.back();
      parsed_items.pop_back();
      auto w = parsed_items.back();
      parsed_items.pop_back();
      auto i = new cmp_Instruction(w, t2, cmp, t1);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_cjump_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // cjump t2 cmp t1 label
      if (debug) std::cerr << "Recognized cjump t2 cmp t1 label" << std::endl;

      auto currentF = p.functions.back();
      auto label = parsed_items.back();
      parsed_items.pop_back();
      auto t1 = parsed_items.back();
      parsed_items.pop_back();
      auto cmp = parsed_items.back();
      parsed_items.pop_back();
      auto t2 = parsed_items.back();
      parsed_items.pop_back();
      auto i = new cjump_cmp_Instruction(t2, cmp, t1, label);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_label_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // label
      if (debug) std::cerr << "Recognized label" << std::endl;

      auto currentF = p.functions.back();
      auto label = parsed_items.back();
      parsed_items.pop_back();
      auto i = new label_Instruction(label);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_goto_rule > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // goto label
      if (debug) std::cerr << "Recognized goto label" << std::endl;

      auto currentF = p.functions.back();
      auto label = parsed_items.back();
      parsed_items.pop_back();
      auto i = new goto_label_instruction(label);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < str_return > {
    template< typename Input >
	  static void apply( const Input & in, Program & p){
      // return
      if (debug) std::cerr << "Recognized return" << std::endl;

      auto currentF = p.functions.back();
      auto i = new Instruction_ret();
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < call_uN_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // call u N
      if (debug) std::cerr << "Recognized call u N" << std::endl;

      auto currentF = p.functions.back();
      auto N = parsed_items.back();
      parsed_items.pop_back();
      auto u = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Call_uN_Instruction(u,N);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < call_print_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // call print 1 
      if (debug) std::cerr << "Recognized call print 1" << std::endl;

      auto currentF = p.functions.back();
      auto i = new Call_print_Instruction();
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < call_input_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // call input 0
      if (debug) std::cerr << "Recognized call input 0" << std::endl;

      auto currentF = p.functions.back();
      auto i = new Call_input_Instruction();
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < call_allocate_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // call allocate 2
      if (debug) std::cerr << "Recognized call allocate 2" << std::endl;

      auto currentF = p.functions.back();
      auto i = new Call_allocate_Instruction();
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < call_tuperr_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // call tuple-error 3
      if (debug) std::cerr << "Recognized call tuple-error 3" << std::endl;

      auto currentF = p.functions.back();
      auto i = new Call_tuple_Instruction();
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < call_tenserr_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // call tensor-error F
      if (debug) std::cerr << "Recognized call tensor-error F" << std::endl;

      auto currentF = p.functions.back();
      auto F = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Call_tenserr_Instruction(F);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_inc_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // w ++
      if (debug) std::cerr << "Recognized w ++" << std::endl;

      auto currentF = p.functions.back();
      auto op = parsed_items.back();
      parsed_items.pop_back();
      auto w = parsed_items.back();
      parsed_items.pop_back();
      auto i = new w_increment_decrement(w, op);
      currentF->instructions.push_back(i);
    }
  };
  // bruh these are identical
  template<> struct action < Inst_dec_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // w --  
      if (debug) std::cerr << "Recognized w --" << std::endl;

      auto currentF = p.functions.back();
      auto op = parsed_items.back();
      parsed_items.pop_back();
      auto w = parsed_items.back();
      parsed_items.pop_back();
      auto i = new w_increment_decrement(w, op);
      currentF->instructions.push_back(i);
    }
  };

  template<> struct action < Inst_atreg_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // w1 @ w2 w3 E
      if (debug) std::cerr << "Recognized w1 @ w2 w3 E" << std::endl;

      auto currentF = p.functions.back();
      auto E = parsed_items.back();
      parsed_items.pop_back();
      auto w3 = parsed_items.back();
      parsed_items.pop_back();
      auto w2 = parsed_items.back();
      parsed_items.pop_back();
      auto w1 = parsed_items.back();
      parsed_items.pop_back();
      auto i = new w_atreg_assignment(w1,w2,w3,E);
      currentF->instructions.push_back(i);
    }
  };


  /*
  Function Actions!
  */
  template<> struct action < function_name_rule > {
    template< typename Input>
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized a function_name rule" << std::endl;

      auto newF = new Function();
      newF->name = in.string();
      p.functions.push_back(newF);
    }
  };

  template<> struct action < argument_number > {
    template< typename Input >
	  static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized an arg number" << std::endl;

      // since argument number gets matched as N first, its token gets put on the stack
      // ie we should remove here
      // parsed_items.pop_back();

      // ^ actually idk if this gets matched as 'number' first?

      auto currentF = p.functions.back();
      currentF->arguments = std::stoll(in.string());
    }
  };

  template<> struct action < argument_number > {
    template< typename Input >
	  static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized a Function!" << std::endl;
    }
  };


  /*
  Grammar Rules!
  */
  struct full_grammar :
    pegtl::must<
      entry_point_rule
    > {};

  struct function_grammar :
    pegtl::must<
      Function_rule
    > {};

  // still need to actually implement after getting liveness
  struct spill_grammar :
    pegtl::must<
      Function_rule
    > {};


  /*
  Parsing Functions!
  */
  Program parse_file (char *fileName){

    /* 
     * Check the grammar for some possible issues.
     */
    if (pegtl::analyze< full_grammar >() != 0){
      std::cerr << "There are problems with the grammar" << std::endl;
      exit(1);
    }

    /*
     * Parse.
     */
    file_input< > fileInput(fileName);
    Program p;
    parse< full_grammar, action >(fileInput, p);

    return p;
  }

  Program parse_function_file(char * fileName) {
      /* 
      * Check the grammar for some possible issues.
      */
      if (pegtl::analyze< function_grammar >() != 0){
        std::cerr << "There are problems with the grammar" << std::endl;
        exit(1);
      }

      /*
      * Parse.
      */
      file_input< > fileInput(fileName);
      Program p;
      parse< function_grammar, action >(fileInput, p);

      return p;
  }

  Program parse_spill_file(char *fileName) {
    /* 
     * Check the grammar for some possible issues.
     */
    if (pegtl::analyze< spill_grammar >() != 0){
      std::cerr << "There are problems with the grammar" << std::endl;
      exit(1);
    }

    /*
     * Parse.
     */
    file_input< > fileInput(fileName);
    Program p;
    parse< spill_grammar, action >(fileInput, p);

    return p;
  }

}