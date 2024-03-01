#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/analyze.hpp>
#include <tao/pegtl/contrib/raw_string.hpp>

#include "parser_alt.h"

namespace pegtl = TAO_PEGTL_NAMESPACE;

using namespace pegtl;
using namespace std;

namespace L3 {

  /*
  Debug flag.
  */
  const int debug = 1;

  /*
  Forward Declarations.
  */
  // struct var_rule;
  // struct t_rule;

  /*
  Vector of dictionaries for keeping track of the labels and their globalizations.
  */
  std::vector<std::map<std::string, std::string>> labels_map;

  /*
  Stack for storing parsed tokens.
  */
  std::vector<Item*> parsed_items;

  /*
  Stack for stored the params of a function definition.
  */
  std::vector<Item*> parsed_params;

  /*
  Stack for storing the args of a function call.
  */
  std::vector<Item*> parsed_args;

  /*
  Stack for holding the parsed function names.
  */
  std::vector<Item*> parsed_fnames;

  /*
  Hopefully a universal counter for globalizing all labels in the program.
  */
  int labelCounter = 0;

  /*
  Counter for creating globally unique return labels.
  */
  int returnCounter = 0;

  /*
  Counter for creating labels that are globally unique,
  but consistent at the function scope
  */
  int functionCounter = 0;

  /*
  Counter for tracking the parsing of a new function
  */
  int fnameCounter = 0;

  /*
  Utility for storing the calling convention.
  */
  std::vector<std::string> argRegisters = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};


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
  struct str_main : TAO_PEGTL_STRING( "@main" ) {};

  /*
  Symbols
  */
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

  struct str_arrow : TAO_PEGTL_STRING( "<-" ) {};
  
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

  struct label_rule:
    pegtl::seq<
      pegtl::one<':'>,
      name
    > {};

  /*
  Special rules for separating out different "@name" use cases.
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
  Special rules for serparating out  the different "%var" use cases.
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
    pegtl::sor<
      variable_name_rule,
      number
    > {};
    // t_rule {};

  /*
  Should match to all other variable instances in the program.
  */
  struct var_rule:
    variable_name_rule {};

  struct number_rule:
    number {};

  struct t_rule:
    pegtl::sor<
      var_rule,
      number_rule
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

  struct Instruction_operation_rule:
    // var <- t op t
    pegtl::seq<
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

  struct Instruction_comparison_rule:
    // var <- t cmp t
    pegtl::seq<
      var_rule,
      spaces,
      str_arrow,
      spaces,
      t_rule,
      spaces,
      cmp_rule,
      spaces,
      t_rule
    > {};


  /*
  Item Group rules
  */
  struct stdlib_rule:
    pegtl::sor<
      str_print,
      str_allocate,
      str_input,
      str_tuperr,
      str_tenserr
    > {};

  struct s_rule:
    pegtl::sor<
      t_rule,
      // var_rule,
      // number_rule,
      label_rule,
      I_rule
    > {};

  struct u_rule:
    pegtl::sor<
      var_rule,
      I_rule
    > {};

  struct vars_rule:
    pegtl::seq<
      pegtl::opt< defined_var_rule >,
      pegtl::star<
        pegtl::seq<
          pegtl::one< ',' >,
          spaces,
          defined_var_rule
        >
      >
    > {};

  struct args_rule:
    pegtl::seq<
      pegtl::opt< arg_rule >,
      spaces,
      pegtl::star<
        pegtl::seq<
          pegtl::one< ',' >,
          spaces,
          arg_rule
        >
      >
    > {};

  struct callee_rule:
    pegtl::sor<
      u_rule,
      stdlib_rule
    > {};


  /*
  Some instruction rules
  */

  struct Instruction_load_rule:
    // var <- load var
    pegtl::seq<
      var_rule,
      spaces,
      str_arrow,
      spaces,
      str_load,
      spaces,
      var_rule
    > {};

  struct Instruction_store_rule:
    // store var <- s
    pegtl::seq<
      str_store,
      spaces,
      var_rule,
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
      pegtl::one< '(' >,
      spaces,
      args_rule,
      spaces,
      pegtl::one< ')' >
    > {};

  struct Instruction_call_function_rule:
    // call callee ( args )
    pegtl::seq<
      call_function_rule
    > {};

  struct Instruction_call_function_assignment_rule:
    // var <- call callee ( args )
    pegtl::seq<
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
      args_rule,
      spaces,
      pegtl::one< ')' >
    > {};

  struct Instruction_assignment_rule:
    // var <- s
    pegtl::seq<
      var_rule,
      spaces,
      str_arrow,
      spaces,
      s_rule
    > {};

  struct Instruction_rule:
    pegtl::sor<
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
      pegtl::seq< pegtl::at<Instruction_assignment_rule>, Instruction_assignment_rule >,
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
  struct Main_function_rule:
    pegtl::seq<
      spaces,
      str_define,
      spaces,
      str_main,
      spaces,
      pegtl::one< '(' >,
      spaces,
      vars_rule,
      spaces,
      pegtl::one< ')' >,
      spaces,
      pegtl::one< '{' >,
      seps_with_comments,
      Instructions_rule,
      seps_with_comments,
      pegtl::one< '}' >
    > {};

  struct Function_rule:
    pegtl::seq<
      seps_with_comments,
      str_define,
      spaces,
      defined_function_name_rule,
      spaces,
      pegtl::one< '(' >,
      spaces,
      vars_rule,
      spaces,
      pegtl::one< ')' >,
      spaces,
      pegtl::one< '{' >,
      seps_with_comments,
      Instructions_rule,
      seps_with_comments,
      pegtl::one< '}' >
    > {};

  struct Functions_rule:
    pegtl::star<
      seps_with_comments,
      Function_rule,
      seps_with_comments
    > {};

  /*
  What is the entry point rule here?? is it always @main?
  */
  struct entry_point_rule:
    pegtl::seq<
      seps_with_comments,
      Main_function_rule,
      Functions_rule
    > {};


  template< typename Rule >
  struct action : pegtl::nothing< Rule > {};

  /*
  Debug Actions
  */

  template<> struct action < variable_name_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out) {
      if (debug) std::cerr << "Recognized a variable_name rule.\n";
    }
  };

  template<> struct action < Functions_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out) {
      if (debug) std::cerr << "Recognized a Functions rule.\n";
    }
  };


  template<> struct action < str_main > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out) {
      if (debug) std::cerr << "Recognized an str_main keyword rule.\n";

      Symbol* fname = new Symbol(in.string());
      parsed_fnames.push_back(fname);

      /*
      Push back an empty dictionary on the vector in preparation for the rest of the function.
      */
      labels_map.emplace_back();

      out << "(" << in.string() << "\n";
      out << "(" << in.string() << "\n";
    }
  };


  template<> struct action < Main_function_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out) {
      if (debug) std::cerr << "Recognized a Main_function rule.\n";

      out << ")\n\n";
    }
  };


  template<> struct action < entry_point_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out) {
      if (debug) std::cerr << "Recognized an entry_point rule, successflly parsed the L3 program!\n";
    
      out << ")\n";
    }
  };


  template<> struct action < str_arrow > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out) {
      if (debug) std::cerr << "Recognized an str_arrow rule.\n";
    }
  };

  template<> struct action < t_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out) {
      if (debug) std::cerr << "Recognized a t_rule rule.\n";
    }
  };

  template<> struct action < s_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out) {
      if (debug) std::cerr << "Recognized an s_rule rule.\n";
    }
  };

  /*
  Item Actions
  */
  template<> struct action < number_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out) {
      if (debug) std::cerr << "Recognized a number rule.\n";

      int val = std::stoi(in.string());
      Number* num = new Number(val);
      parsed_items.push_back(num);
    }
  };

  template<> struct action < label_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      if (debug) std::cerr << "Recognized a label rule.\n";

      /*
      Globalize the label before ever putting it into the parsed_items stack.
      */

      if (debug) std::cerr << "labels_map has size " << labels_map.size() << ", fnameCounter is " << fnameCounter << "\n";;

      std::string global_label;
      auto it = labels_map[fnameCounter].find(in.string());
      if (it != labels_map[fnameCounter].end()) {
        if (debug) std::cerr << "the label was already in labels map\n";
        /* if the key exists in the map we already globalized it */
        global_label = it->second;
        if (debug) std::cerr << "global_label from the map is " << global_label << "\n";
      } else {
        if (debug) std::cerr << "the label was not in the labels_map\n";
        /* we need to globalize the label */
        global_label = in.string() + "_global_" + std::to_string(labelCounter);
        if (debug) std::cerr << "adding the new value " << global_label << " for key " << in.string() << "\n";
        labels_map[fnameCounter][in.string()] = global_label;
      }
      labelCounter++;

      Symbol* lab = new Symbol(global_label);
      parsed_items.push_back(lab);
    }
  };

  
  template<> struct action < stdlib_rule > {
    template< typename Input>
    static void apply( const Input & in, std::ofstream & out) {
      if (debug) std::cerr << "Recognized an stdlib rule" << std::endl;
      
      Symbol* callee = new Symbol(in.string());
      parsed_items.push_back(callee);
    }
  };

  template<> struct action < I_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      if (debug) std::cerr << "Recognized an I rule.\n";

      Symbol* fname = new Symbol(in.string());
      parsed_items.push_back(fname);
    }
  };

  template<> struct action < defined_var_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      if (debug) std::cerr << "Recognized a defined_var rule.\n";

      Symbol* var = new Symbol(in.string());
      parsed_params.push_back(var);
    }
  };

  template<> struct action < arg_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      if (debug) std::cerr << "Recognized an arg_var rule.\n";

      Symbol* var = new Symbol(in.string());
      parsed_args.push_back(var);
    }
  };


  template<> struct action < var_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      if (debug) std::cerr << "Recognized a var rule.\n";

      Symbol* var = new Symbol(in.string());
      parsed_items.push_back(var);
    }
  };

  template<> struct action < op_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      if (debug) std::cerr << "Recognized a operation rule.\n";

      OperationType type = stringToOperation(in.string());
      Operation* op = new Operation(type);
      parsed_items.push_back(op);
    }
  };

  template<> struct action < cmp_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      if (debug) std::cerr << "Recognized a comparison rule.\n";

      ComparisonType type = stringToComparison(in.string());
      Comparison* cmp = new Comparison(type);
      parsed_items.push_back(cmp);
    }
  };
  

  /*
  Instruction Actions
  */
  template<> struct action < Instruction_assignment_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      // var <- s
      if (debug) std::cerr << "Recognized an Instruction_assignment rule.\n";

      auto s = parsed_items.back();
      parsed_items.pop_back();
      auto var = parsed_items.back();
      parsed_items.pop_back();

      out << var->print() << " <- " << s->print() << "\n";
    }
  };

  template<> struct action < Instruction_operation_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      // var <- t1 op t2
      if (debug) std::cerr << "Recognized an Instruction_operation rule.\n";

      auto t2 = parsed_items.back();
      parsed_items.pop_back();
      auto op = parsed_items.back();
      parsed_items.pop_back();
      auto t1 = parsed_items.back();
      parsed_items.pop_back();
      auto var = parsed_items.back();
      parsed_items.pop_back();

      /*
      test411 case, can't use and define the same variable from the rhs if op is noncommutative
      */
      if (var->print() == t2->print()) {
        if (debug) std::cerr << "found that var equals t2\n";
        if (op->print() == "-" || op->print() == "<<" || op->print() == ">>") {
          auto function_scope = parsed_fnames.back();
          std::string clean_fname = removeAtSymbol(function_scope->print());
          std::string temp_var = "%" + clean_fname + std::to_string(returnCounter);
          returnCounter++;

          out << temp_var << " <- " << t1->print() << "\n";
          out << temp_var << " " << op->print() << "= " << t2->print() << "\n";
          out << var->print() << " <- " << temp_var << "\n";
        }
      } else {
        out << var->print() << " <- " << t1->print() << "\n";
        out << var->print() << " " << op->print() <<"= " << t2->print() << "\n";
      }
    }
  };

  template<> struct action < Instruction_comparison_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      // var <- t1 cmp t2
      if (debug) std::cerr << "Recognized an Instruction_comparison rule.\n";

      auto t2 = parsed_items.back();
      parsed_items.pop_back();
      auto cmp = parsed_items.back();
      parsed_items.pop_back();
      auto t1 = parsed_items.back();
      parsed_items.pop_back();
      auto var = parsed_items.back();
      parsed_items.pop_back();
      
      out << var->print() << " <- ";

      ComparisonType cmp_type = stringToComparison(cmp->print());
      switch (cmp_type) {
        case ComparisonType::less:
            out << t1->print() << " < " << t2->print() << "\n";
            break;
        case ComparisonType::lesseq:
            out << t1->print() << " <= " << t2->print() << "\n";
            break;
        case ComparisonType::eq:
            out << t1->print() << " = " << t2->print() << "\n";
            break;
        case ComparisonType::greatereq:
            out << t2->print() << " < " << t1->print() << "\n";
            break;
        case ComparisonType::greater:
            out << t2->print() << " <= " << t1->print() << "\n";
            break;
      }
    }
  };

  template<> struct action < Instruction_load_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      // var1 <- load var2
      if (debug) std::cerr << "Recognized an Instruction_load rule.\n";

      auto var2 = parsed_items.back();
      parsed_items.pop_back();
      auto var1 = parsed_items.back();
      parsed_items.pop_back();

      out << var1->print() << " <- mem " << var2->print() << " 0\n";
    }
  };

  template<> struct action < Instruction_store_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      // store var <- s
      if (debug) std::cerr << "Recognized an Instruction_store rule.\n";

      auto s = parsed_items.back();
      parsed_items.pop_back();
      auto var = parsed_items.back();
      parsed_items.pop_back();

      out << "mem " << var->print() << " 0 <- " << s->print() << "\n";
    }
  };

  template<> struct action < Instruction_return_val_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      // return t
      if (debug) std::cerr << "Recognized an Instruction_store rule.\n";

      auto t = parsed_items.back();
      parsed_items.pop_back();
      
      out << "rax <- " << t->print() << "\n";
      out << "return\n";
    }
  };

  template<> struct action < Instruction_return_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      // return
      if (debug) std::cerr << "Recognized an Instruction_return rule.\n";

      out << "return\n";
    }
  };

  template<> struct action < Instruction_label_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      // label
      if (debug) std::cerr << "Recognized an Instruction_label rule.\n";

      if (debug) std::cerr << "parsed items has size " << parsed_items.size() << "\n";

      auto label = parsed_items.back();
      parsed_items.pop_back();

      out << label->print() << "\n";

      // if (debug) std::cerr << "labels_map has size " << labels_map.size() << ", fnameCounter is " << fnameCounter << "\n";;

      // std::string global_label;
      // auto it = labels_map[fnameCounter].find(label->print());
      // if (it != labels_map[fnameCounter].end()) {
      //   if (debug) std::cerr << "the label was already in labels map\n";
      //   /* if the key exists in the map we already globalized it */
      //   global_label = it->second;
      // } else {
      //   if (debug) std::cerr << "the label was not in the labels_map\n";
      //   /* we need to globalize the label */
      //   global_label = label->print() + "_global_" + std::to_string(labelCounter);
      //   if (debug) std::cerr << "adding the new value " << global_label << " for key " << label->print() << "\n";
      //   labels_map[fnameCounter][label->print()] = global_label;
      // }
      // labelCounter++;
      // out << global_label << "\n";
    }
  };

  template<> struct action < Instruction_branch_label_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      // br label
      if (debug) std::cerr << "Recognized an Instruction_branch_label rule.\n";

      if (debug) std::cerr << "parsed items has size " << parsed_items.size() << "\n";

      auto label = parsed_items.back();
      parsed_items.pop_back();

      out << "cjump 0 = 0 " << label->print() << "\n";

      // if (debug) std::cerr << "labels_map has size " << labels_map.size() << "\n";

      // std::string global_label;
      // auto it = labels_map[fnameCounter].find(label->print());
      // if (it != labels_map[fnameCounter].end()) {
      //   /* if the key exists in the map we already globalized it */
      //   if (debug) std::cerr << "the label was already in labels map\n";
      //   global_label = it->second;
      // } else {
      //   if (debug) std::cerr << "the label was not in the labels_map\n";
      //   /* we need to globalize the label */
      //   global_label = label->print() + "_global_" + std::to_string(labelCounter);
      //   if (debug) std::cerr << "adding the new value " << global_label << " for key " << label->print() << "\n";
      //   labels_map[fnameCounter][label->print()] = global_label;
      // }
      // labelCounter++;
      // out << "cjump 0 = 0 " << global_label << "\n";
    }
  };

  template<> struct action < Instruction_branch_label_conditional_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      // br t label
      if (debug) std::cerr << "Recognized an Instruction_branch_label_conditional rule.\n";


      auto label = parsed_items.back();
      parsed_items.pop_back();
      auto t = parsed_items.back();
      parsed_items.pop_back();

      out << "cjump 0 < " << t->print() << " " << label->print() << "\n";
    }
  };

  template<> struct action < Instruction_call_function_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      // call callee ( args )
      if (debug) std::cerr << "Recognized an Instruction_call_function rule.\n";

      if (debug) std::cerr << "examining parsed_items, length is " << parsed_items.size() << "\n";
      auto callee = parsed_items.back();
      parsed_items.pop_back();
      
      auto function_scope = parsed_fnames.back();

      /*
      We'll use the label globalization strategy originally in Simone's slides,
      since he said we won't be tested on it even if the old version was false. 
      */
      std::string clean_fname = removeAtSymbol(function_scope->print());
      std::string clean_callee = removeAtSymbol(callee->print());

      /* hacky way of checking if this is a stdlib function call */
      auto isStdlib = (!callee->print().empty() && callee->print()[0] == '@') && (callee->print().size() == clean_callee.size());

      if (debug) std::cerr << "clean_callee= " << clean_callee << " : size= " << clean_callee.size() << ", callee= " << callee->print() << " : size= " << callee->print().size() << "\n";

      std::string return_label;
      if (!isStdlib) {
        return_label = ":ret_" + clean_fname + "_global_" + std::to_string(labelCounter);
        out << "mem rsp -8 <- " << return_label << "\n";
        labelCounter++;
      }

      /* Grab the function arguments and info */
      int count = 0;
      int numArgs = parsed_args.size();
      while (!parsed_args.empty()) {
        auto arg = parsed_args.front();
        parsed_args.erase(parsed_args.begin());

        /* Try to use one of the six argument registers, otherwise use stack */
        if (count < 6) {
          out << argRegisters[count] << " <- " << arg->print() << "\n";
        } else {
          out << "mem rsp " << (40 - (8 * numArgs)) << "\n";
        }

        count++;
      }

      out << "call " << callee->print() << " " << numArgs << "\n";
      
      if (!isStdlib) out << return_label << "\n";
    }
  };

  template<> struct action < Instruction_call_function_assignment_rule > {
    template< typename Input >
    static void apply( const Input & in, std::ofstream & out ) {
      // var <- call callee ( args )
      if (debug) std::cerr << "Recognized an Instruction_call_function_assignment rule.\n";

      auto callee = parsed_items.back();
      parsed_items.pop_back();
      auto var = parsed_items.back();
      parsed_items.pop_back();

      auto function_scope = parsed_fnames.back();
      std::string clean_fname = removeAtSymbol(function_scope->print());
      std::string clean_callee = removeAtSymbol(callee->print());

      /* hacky way of checking if this is a stdlib function call */
      auto isStdlib = (!callee->print().empty() && callee->print()[0] == '@') && (callee->print().size() == clean_callee.size());

      if (debug) std::cerr << "clean_callee= " << clean_callee << " : size= " << clean_callee.size() << ", callee= " << callee->print() << " : size= " << callee->print().size() << "\n";

      std::string return_label;
      if (!isStdlib) {
        return_label = ":ret_" + clean_fname + "_global_" + std::to_string(labelCounter);
        out << "mem rsp -8 <- " << return_label << "\n";
        labelCounter++;
      }

      int count = 0;
      int numArgs = parsed_args.size();
      while (!parsed_args.empty()) {
        // auto arg = parsed_args.back();
        // parsed_args.pop_back();
        auto arg = parsed_args.front();
        parsed_args.erase(parsed_args.begin());

        if (count < 6) {
          out << argRegisters[count] << " <- " << arg->print() << "\n";
        } else {
          out << "mem rsp " << (40 - (8 * numArgs)) << "\n";
        }

        count++;
      }

      out << "call " << callee->print() << " " << numArgs << "\n";
      if (!isStdlib) out << return_label << "\n";
      out << var->print() << " <- rax\n";
    }
  };
  
  /*
  Function / Program Actions
  */
  template<> struct action < defined_function_name_rule > {
    template< typename Input>
    static void apply( const Input & in, std::ofstream & out) {
      if (debug) std::cerr << "Recognized an defined_function_name rule" << std::endl;
      
      Symbol* fname = new Symbol(in.string());
      parsed_fnames.push_back(fname);
      fnameCounter++;

      /*
      Push back an empty dictionary on the vector in preparation for the rest of the function.
      */
      labels_map.emplace_back();

      out << "(" << in.string() << "\n";
    }
  };

  template<> struct action < vars_rule > {
    template< typename Input>
    static void apply( const Input & in, std::ofstream & out) {
      if (debug) std::cerr << "Recognized a vars rule" << std::endl;

      int numArgs = parsed_params.size();

      std::cout << numArgs << "\n";

      out << numArgs << "\n";

      int count = 0;
      while (!parsed_params.empty()) {
        auto arg = parsed_params.front();
        parsed_params.erase(parsed_params.begin());

        /* arguments 1-6 are in registers, otherwise on the stack*/
        if (count < 6) {
          out << arg->print() << " <- " << argRegisters[count] << "\n";
        } else {
          out << arg->print() << " <- " << (8 * (numArgs - 1 - count)) << "\n";
        }

        count++;
      }

    }
  };


  template<> struct action < Function_rule > {
    template< typename Input>
    static void apply( const Input & in, std::ofstream & out) {
      if (debug) std::cerr << "Recognized a function rule" << std::endl;
      
      out << ")\n\n ";
    }
  };

  /*
  Grammar Rules
  */
  struct full_grammar :
    pegtl::must<
      entry_point_rule
    > {};


  /*
  Program Parser
  */
  void parse_file_alt (char *fileName) {
    /* 
    Check the grammar for some possible issues.
    */
    if (pegtl::analyze< full_grammar >() != 0){
      std::cerr << "There are problems with the grammar" << std::endl;
      exit(1);
    }

    /*
    Continue the parse if valid grammar. Get the input file.
    */
    file_input< > fileInput(fileName);

    /* 
     * Open the output file.
     */ 
    std::ofstream outputFile;
    outputFile.open("prog.L2");

    /*
    Parse out of the input and generate code into the output.
    */
    parse< full_grammar, action >(fileInput, outputFile);

  }

}
