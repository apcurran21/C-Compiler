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

  /*
  Keywords
  */
  struct str_load : TAO_PEGTL_STRING( "load" ) {};
  struct str_store : TAO_PEGTL_STRING( "store" ) {};
  struct str_return : TAO_PEGTL_STRING( "return" ) {};
  struct str_define : TAO_PEGTL_STRING( "define" ) {};
  struct str_branch : TAO_PEGTL_STRING( "br" ) {};
  struct str_call : TAO_PEGTL_STRING( "call" ) {};
  struct str_print : TAO_PEGTL_STRING( "print" ) {};
  struct str_allocate : TAO_PEGTL_STRING( "allocate" ) {};
  struct str_input : TAO_PEGTL_STRING( "input" ) {};
  struct str_tuperr : TAO_PEGTL_STRING( "tuple-error" ) {};
  struct str_tenserr : TAO_PEGTL_STRING( "tensor-error" ) {};
  /*
  Symbols
  */
  struct str_arrow : TAO_PEGTL_STRING( "<-" ) {};
  struct str_less : TAO_PEGTL_STRING( "<" ) {};
  struct str_lesseq : TAO_PEGTL_STRING( "<=" ) {};
  struct str_eq : TAO_PEGTL_STRING( "=" ) {};
  struct str_greatereq : TAO_PEGTL_STRING( ">=" ) {};
  struct str_greater : TAO_PEGTL_STRING( ">" ) {};
  struct str_plus : TAO_PEGTL_STRING( "+" ) {};
  struct str_minus : TAO_PEGTL_STRING( "-" ) {};
  struct str_mult : TAO_PEGTL_STRING( "*" ) {};
  struct str_and : TAO_PEGTL_STRING( "&" ) {};
  struct str_shiftl : TAO_PEGTL_STRING( "<<" ) {};
  struct str_shiftr : TAO_PEGTL_STRING( ">>" ) {};
  struct

  /*
  Item Rules
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

  struct number_rule:
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

  struct label_rule:
    pegtl::seq<
      pegtl::one<':'>,
      name
    > {};

  /*
  Special rules for separating out "@name" use cases.
  */
  // the base pattern
  struct name_rule:
    pegtl::seq<
      pegtl::one< '@' >,
      name
    > {};
  
  struct defined_function_name_rule:
    name_rule {};

  struct I_rule:
    name_rule {};

  /*
  Special rules for serparating out "%var" use cases.
  */
  // the base pattern
  struct variable_name_rule:
    pegtl::seq<
      pegtl::one< '%' >,
      name
    > {};

  /*
  Should match to the parameters in the function definition.
  */
  struct defined_var_rule:
    variable_name_rule {};

  /*
  Should match to the arguments in a function call.
  */
  struct arg_rule:
    t_rule {};
  
  /*
  Should match to all other variable instances in the program.
  */
  struct var_rule:
    variable_name_rule {};

  /*
  Item Group rules
  */
  struct s_rule:
    pegtl::sor<
      t_rule,
      label_rule,
      I_rule
    > {};

  struct t_rule:
    pegtl::sor<
      var_rule,
      number_rule
    > {};
  
  struct u_rule:
    pegtl::sor<
      var_rule,
      I_rule
    > {};

  struct vars_rule:
    pegtl::sor<
      pegtl::opt< defined_var_rule >,
      pegtl::star<
        pegtl::seq<
          pegtl::one< "," >,
          spaces,
          defined_var_rule
        >
      >
    > {};

  struct args_rule:
    pegtl::sor<
      pegtl::opt< arg_rule >,
      pegtl::star<
        pegtl::seq<
          pegtl::one< "," >,
          spaces,
          arg_rule
        >
      >
    > {};

  struct callee_rule:
    pegtl::sor<
      u_rule,
      str_print,
      str_allocate,
      str_input,
      str_tuperr,
      str_tenserr
    > {};

  /*
  Whitespace Rules
  */
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

  /*
  Operator / Comparison Rules
  */
  struct cmp_rule:
    pegtl::sor<
      str_less,
      str_lesseq,
      str_eq,
      str_greatereq,
      str_greater
    > {};

  struct op_rule:
    pegtl::sor<
      str_plus,
      str_minus,
      str_mult,
      str_and,
      str_shiftl,
      str_shiftr
    > {};

  /*
  Instruction Rules
  */
  struct Instruction_assignment_rule:
    // var <- s
    pegtl::seq<
      variable_rule,
      spaces,
      str_arrow,
      spaces,
      s_rule
    > {};

  struct Instruction_operation_rule:
    // var <- t op t
    pegtl::seq<
      variable_rule,
      spaces,
      str_arrow,
      spaces,
      t_rule,
      spaces,
      op_rule,
      spaces,
      t_rule
    > {};

  struct Instruction_comparison_rule:
    // var <- t cmp t
    pegtl::seq<
      variable_rule,
      spaces,
      str_arrow,
      spaces,
      t_rule,
      spaces,
      cmp_rule,
      spaces,
      t_rule
    > {};

  struct Instruction_load_rule:
    // var <- load var
    pegtl::seq<
      variable_rule,
      spaces,
      str_arrow,
      spaces,
      str_load,
      spaces,
      variable_rule
    > {};

  struct Instruction_store_rule:
    // store var <- s
    pegtl::seq<
      str_store,
      spaces,
      variable_rule,
      spaces,
      str_arrow,
      spaces,
      s_rule
    > {};

  struct Instruction_return_rule:
    // return
    pegtl::seq<
      str_return
    > {};

  struct Instruction_return_val_rule:
    // return t
    pegtl::seq<
      str_return,
      spaces,
      t_rule
    > {};

  struct Instruction_label_rule:
    // label
    pegtl::seq<
      label_rule
    > {};

  struct Instruction_branch_label_rule:
    // br label
    pegtl::seq<
      str_branch,
      spaces,
      label_rule
    > {};

  struct Instruction_branch_label_conditional_rule:
    // br t label
    pegtl::seq<
      str_branch,
      spaces,
      t_rule,
      spaces,
      label_rule
    > {};

  // small simplification for utility
  struct call_function_rule:
    // call callee ( args )
    pegtl::seq<
      str_call,
      spaces,
      callee_rule,
      spaces,
      pegtl::one< "(" >,
      spaces,
      args_rule,
      spaces,
      pegtl::one< ")" >
    > {};

  struct Instruction_call_function_rule:
    // call callee ( args )
    pegtl::seq<
      call_function_rule
    > {};

  struct Instruction_call_function_assignment_rule:
    // var <- call callee ( args )
    pegtl::seq<
      variable_rule,
      spaces,
      str_arrow,
      spaces,
      call_function_rule
    > {};

  struct Instruction_rule:
    pegtl::sor<
      pegtl::seq< pegtl::at<Instruction_assignment_rule>, Instruction_assignment_rule >,
      pegtl::seq< pegtl::at<Instruction_operation_rule>, Instruction_operation_rule >,
      pegtl::seq< pegtl::at<Instruction_comparison_rule>, Instruction_comparison_rule >,
      pegtl::seq< pegtl::at<Instruction_load_rule>, Instruction_load_rule >,
      pegtl::seq< pegtl::at<Instruction_store_rule>, Instruction_store_rule>,
      pegtl::seq< pegtl::at<Instruction_return_val_rule>, Instruction_return_val_rule>,
      pegtl::seq< pegtl::at<Instruction_return_rule>, Instruction_return_rule>,
      pegtl::seq< pegtl::at<Instruction_label_rule>, Instruction_label_rule>,
      pegtl::seq< pegtl::at<Instruction_branch_label_rule>, Instruction_branch_label_rule>,
      pegtl::seq< pegtl::at<Instruction_branch_label_conditional_rule>, Instruction_branch_label_conditional_rule>,
      pegtl::seq< pegtl::at<Instruction_call_function_rule>, Instruction_call_function_rule>,
      pegtl::seq< pegtl::at<Instruction_call_function_assignment_rule>, Instruction_call_function_assignment_rule>,
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
  Function / Program Rules
  */
  struct Function_rule:
    pegtl::seq<
      seps_with_comments,
      str_define,
      spaces,
      defined_function_name_rule,
      spaces,
      pegtl::one< "(" >,
      spaces,
      variable_rule,
      spaces,
      pegtl::one< ")" >,
      spaces,
      pegtl::one< "{" >,
      seps_with_comments,
      Instructions_rule,
      seps_with_comments,
      pegtl::one< "}" >
    > {};

  struct Functions_rule:
    pegtl::plus<
      seps_with_comments,
      Function_rule,
      seps_with_comments
    > {};

  /*
  What is the entry point rule here?? is it always @main?
  */

  /*
  Item Actions
  */
  template< typename Rule >
  struct action : pegtl::nothing< Rule > {};

  template<> struct action < number_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized a number rule.\n";

      int val = std::stoi(in.string);
      Number* num = new Number(val);
      parsed_items.push_back(num);
    }
  };

  template<> struct action < label_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      if (debug) std::cerr << "Recognized a label rule.\n";

      Symbol* lab = new Symbol(in.string);
      parsed_items.push_back(lab);
    }
  };

  template<> struct action < I_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      if (debug) std::cerr << "Recognized an I rule.\n";

      Symbol* fname = new Symbol(in.string);
      parsed_items.push_back(fname);
    }
  };

  template<> struct action < var_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      if (debug) std::cerr << "Recognized a var rule.\n";

      Symbol* var = new Symbol(in.string);
      parsed_items.push_back(var);
    }
  };

  template<> struct action < op_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      if (debug) std::cerr << "Recognized a operation rule.\n";

      Symbol* op = new Symbol(in.string);
      parsed_items.push_back(op);
    }
  };

  template<> struct action < cmp_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      if (debug) std::cerr << "Recognized a comparison rule.\n";

      Symbol* cmp = new Symbol(in.string);
      parsed_items.push_back(cmp);
    }
  };
  

  /*
  Instruction Actions
  */
  template<> struct action < Instruction_assignment_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      // var <- s
      if (debug) std::cerr << "Recognized an Instruction_assignment rule.\n";

      auto currentF = p.getLastFunction();
      auto s = parsed_items.back();
      parsed_items.pop_back();
      auto var = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Instruction_assignment(var, s);

    }
  };

  template<> struct action < Instruction_operation_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      // var <- t1 op t2
      if (debug) std::cerr << "Recognized an Instruction_operation rule.\n";

      auto currentF = p.getLastFunction();
      auto t2 = parsed_items.back();
      parsed_items.pop_back();
      auto op = parsed_items.back();
      parsed_items.pop_back();
      auto t1 = parsed_items.back();
      parsed_items.pop_back();
      auto var = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Instruction_operation(var, t1, op, t2);
      currentF.addInstruction(i);
    }
  };

  template<> struct action < Instruction_comparison_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      // var <- t1 cmp t2
      if (debug) std::cerr << "Recognized an Instruction_comparison rule.\n";

      auto currentF = p.getLastFunction();
      auto t2 = parsed_items.back();
      parsed_items.pop_back();
      auto cmp = parsed_items.back();
      parsed_items.pop_back();
      auto t1 = parsed_items.back();
      parsed_items.pop_back();
      auto var = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Instruction_comparison(var, t1, cmp, t2);
      currentF.addInstruction(i);
    }
  };

  template<> struct action < Instruction_load_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      // var1 <- load var2
      if (debug) std::cerr << "Recognized an Instruction_load rule.\n";

      auto currentF = p.getLastFunction();
      auto var2 = parsed_items.back();
      parsed_items.pop_back();
      auto var1 = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Instruction_load(var1, var2);
      currentF.addInstruction(i);
    }
  };

  template<> struct action < Instruction_store_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      // store var <- s
      if (debug) std::cerr << "Recognized an Instruction_store rule.\n";

      auto currentF = p.getLastFunction();
      auto s = parsed_items.back();
      parsed_items.pop_back();
      auto var = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Instruction_store(var, s);
      currentF.addInstruction(i);
    }
  };

  template<> struct action < Instruction_return_val_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      // return t
      if (debug) std::cerr << "Recognized an Instruction_store rule.\n";

      auto currentF = p.getLastFunction();
      auto t = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Instruction_return_value(t);
      currentF.addInstruction(i);
    }
  };

  template<> struct action < Instruction_return_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      // return
      if (debug) std::cerr << "Recognized an Instruction_return rule.\n";

      auto currentF = p.getLastFunction();
      auto i = new Instruction_return();
      currentF.addInstruction(i);
    }
  };

  template<> struct action < Instruction_label_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      // label
      if (debug) std::cerr << "Recognized an Instruction_label rule.\n";

      auto currentF = p.getLastFunction();
      auto label = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Instruction_label(label);
      currentF.addInstruction(i);
    }
  };

  template<> struct action < Instruction_branch_label_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      // br label
      if (debug) std::cerr << "Recognized an Instruction_branch_label rule.\n";

      auto currentF = p.getLastFunction();
      auto label = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Instruction_branch_label(label);
      currentF.addInstruction(i);
    }
  };

  template<> struct action < Instruction_branch_label_conditional_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      // br t label
      if (debug) std::cerr << "Recognized an Instruction_branch_label_conditional rule.\n";

      auto currentF = p.getLastFunction();
      auto label = parsed_items.back();
      parsed_items.pop_back();
      auto t = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Instruction_branch_label_conditional(t, label);
      currentF.addInstruction(i);
    }
  };

  template<> struct action < Instruction_call_function_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p ) {
      // call callee ( args )
      if (debug) std::cerr << "Recognized an Instruction_call_function rule.\n";

      auto currentF = p.getLastFunction();
      auto label = parsed_items.back();
      parsed_items.pop_back();
      auto t = parsed_items.back();
      parsed_items.pop_back();
      auto i = new Instruction_branch_label_conditional(t, label);
      currentF.addInstruction(i);
    }
  };



  
  /*
  Function / Program Actions
  */
  template<> struct action < function_name_rule > {
    template< typename Input>
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized an arg rule" << std::endl;
      
      auto currentF = p.getLastFunction();
      auto 
    }
  };



  template<> struct action < function_name_rule > {
    template< typename Input>
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized a function_name rule" << std::endl;
        auto new_function = new Function();
        new_function.setFunctionName(in.string());
        p.addFunction(new_function);
    }
  };





  /*
  Grammar Rules
  */
  struct full_grammar :
    pegtl::must<
      Functions_rule
    > {};


  /*
  Program Parser
  */
  Program parse_file (char *fileName) {
    /* 
    Check the grammar for some possible issues.
    */
    if (pegtl::analyze< full_grammar >() != 0){
      std::cerr << "There are problems with the grammar" << std::endl;
      exit(1);
    }

    /*
    Parse if valid grammar.
    */
    file_input< > fileInput(fileName);
    Program p;
    parse< full_grammar, action >(fileInput, p);

    return p;


  }
}
