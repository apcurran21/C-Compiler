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
  Stack for storing the parsed items.
  */
  std::vector<Item*> parsed_items;


  /*
  Keywords.
  */
  struct str_length : TAO_PEGTL_STRING( "length" ) {};
  struct str_return : TAO_PEGTL_STRING( "return" ) {};
  struct str_branch : TAO_PEGTL_STRING( "br" ) {};
  struct str_new : TAO_PEGTL_STRING( "new" ) {};
  struct str_Array : TAO_PEGTL_STRING( "Array" ) {};
  struct str_Tuple : TAO_PEGTL_STRING( "Tuple" ) {};
  struct str_tuple : TAO_PEGTL_STRING( "tuple" ) {};
  struct str_code : TAO_PEGTL_STRING( "code" ) {};
  struct str_int64 : TAO_PEGTL_STRING( "int64" ) {};
  struct str_void : TAO_PEGTL_STRING( "void" ) {};
  /*
  Terminal symbols.
  */
  struct str_arrow : TAO_PEGTL_STRING( "<-" ) {};
  struct str_comment : TAO_PEGTL_STRING( "//" ) {};
  struct str_bracks: TAO_PEGTL_STRING( "[]" ) {};
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
  struct spaces:
    pegtl::star< 
      pegtl::sor<
        pegtl::one< ' ' >,
        pegtl::one< '\t'>
      >
    > {};
  struct seps: 
    pegtl::star<
      pegtl::seq<
        spaces,
        pegtl::eol
      >
    > {};
  struct seps_with_comments: 
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
  struct name_rule:
    pegtl::seq<
      name
    > {};
  struct N_rule:
    pegtl::seq<
      number
    > {};
  struct label_rule:
    pegtl::seq<
      pegtl::one< ':' >,
      name
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
      str_eq,
      str_greatereq,
      str_greater
    > {};

  /*
  Tokens rules.
  */
  struct t_rule:
    pegtl::sor<
      name_rule,
      N_rule
    > {};
  struct type_keywords_rule:
    pegtl::sor<
      str_int64,
      str_tuple,
      str_code,
      str_void
    > {};
  struct type_rule:
    pegtl::seq<
      type_keywords_rule,
      pegtl::star< str_bracks >
    > {};
  struct defined_fname:
    pegtl::seq<
      name_rule
    > {};
  struct array_access:
    // [t]
    pegtl::seq<
      pegtl::one< '[' >,
      // arg_rule,
      t_rule,
      pegtl::one< ']' >
    > {};
  struct full_array_access_rule:
    pegtl::plus<
      pegtl::seq<
        spaces,
        array_access
      >
    > {};
  struct args_rule:
    pegtl::seq<
      pegtl::opt< t_rule >,
      spaces,
      pegtl::star<
        pegtl::one< ',' >,
        spaces,
        t_rule
      >
    > {};
  
  /*
  Instruction rules.
  */
  struct Instruction_type_declaration_rule:
    // type name
    pegtl::seq<
      spaces,
      type_rule,
      spaces,
      name_rule
    > {};
  struct Instruction_assignment_rule:
    // name <- t
    pegtl::seq<
      spaces,
      name_rule,
      spaces,
      str_arrow,
      spaces,
      t_rule
    > {};
  struct Instruction_operation_rule:
    // name <- t1 op t2
    pegtl::seq<
      spaces,
      name_rule,
      spaces,
      str_arrow,
      spaces,
      t_rule,
      spaces,
      op_rule,
      spaces,
      t_rule
    > {};
  struct Instruction_label_rule:
    // label
    pegtl::seq<
      spaces,
      label_rule
    > {};
  struct Instruction_branch_label_rule:
    // br label
    pegtl::seq<
      spaces,
      str_branch,
      spaces,
      label_rule
    > {};
  struct Instruction_branch_label_conditional_rule:
    // br t label1 label2
    pegtl::seq<
      spaces,
      str_branch,
      spaces,
      t_rule,
      spaces,
      label_rule,
      spaces,
      label_rule
    > {};
  struct Instruction_return_rule:
    // return
    pegtl::seq<
      spaces,
      str_return
    > {};
  struct Instruction_return_val_rule:
    // return t
    pegtl::seq<
      spaces,
      str_return,
      spaces,
      t_rule
    > {};
  struct Instruction_load_rule:
    // name1 <- name2[t]...
    pegtl::seq<
      spaces,
      name_rule,
      spaces,
      str_arrow,
      spaces,
      name_rule,
      spaces,
      full_array_access_rule
    > {};
  struct Instruction_store_rule:
    // name1[t]... <- t
    pegtl::seq<
      spaces,
      full_array_access_rule,
      spaces,
      str_arrow,
      spaces,
      t_rule
    > {};
  struct Instruction_dim_length_rule:
    // name1 <- length name2 t
    pegtl::seq<
      spaces,
      name_rule,
      spaces,
      str_arrow,
      spaces,
      str_length,
      spaces,
      name_rule,
      spaces,
      t_rule
    > {};
  struct Instruction_length_rule:
    // name1 <- length name2
    pegtl::seq<
      spaces,
      name_rule,
      spaces,
      str_arrow,
      spaces,
      str_length,
      spaces,
      name_rule
    > {};
  struct Instruction_call_function_rule:
    // name ( args? )
    pegtl::seq<
      spaces,
      name_rule,
      spaces,
      pegtl::one< '(' >,
      spaces,
      pegtl::opt< args_rule >,
      spaces,
      pegtl::one< ')' >
    > {};
  struct Instruction_call_function_assignment_rule:
    // name1 <- name2 ( args? )
    pegtl::seq<
      spaces,
      name_rule,
      spaces,
      str_arrow,
      spaces,
      name_rule,
      spaces,
      pegtl::one< '(' >,
      spaces,
      pegtl::opt< args_rule >,
      spaces,
      pegtl::one< ')' >
    > {};
  struct Instruction_array_initialization_rule:
    // name <- new Array( args )
    pegtl::seq<
      spaces,
      name_rule,
      spaces,
      str_arrow,
      spaces,
      str_new,
      spaces,
      str_Array,
      spaces,
      pegtl::one< '(' >,
      spaces,
      args_rule,
      spaces,
      pegtl::one< ')' >
    > {};
  struct Instruction_tuple_initialization_rule:
    // name <- new Tuple( t )
    pegtl::seq<
      spaces,
      name_rule,
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
      pegtl::one< ')' >
    > {};
  struct Instruction_rule:
    pegtl::sor<
      pegtl::seq< pegtl::at< Instruction_type_declaration_rule >, Instruction_type_declaration_rule >,
      pegtl::seq< pegtl::at< Instruction_dim_length_rule >, Instruction_dim_length_rule >,
      pegtl::seq< pegtl::at< Instruction_length_rule >, Instruction_length_rule >,
      pegtl::seq< pegtl::at< Instruction_call_function_assignment_rule >, Instruction_call_function_assignment_rule >,
      pegtl::seq< pegtl::at< Instruction_call_function_rule >, Instruction_call_function_rule >,
      pegtl::seq< pegtl::at< Instruction_array_initialization_rule >, Instruction_array_initialization_rule >,
      pegtl::seq< pegtl::at< Instruction_tuple_initialization_rule >, Instruction_tuple_initialization_rule >,
      pegtl::seq< pegtl::at< Instruction_store_rule >, Instruction_store_rule >,
      pegtl::seq< pegtl::at< Instruction_load_rule >, Instruction_load_rule >,
      pegtl::seq< pegtl::at< Instruction_operation_rule >, Instruction_operation_rule >,
      pegtl::seq< pegtl::at< Instruction_assignment_rule >, Instruction_assignment_rule >,
      pegtl::seq< pegtl::at< Instruction_branch_label_conditional_rule >, Instruction_branch_label_conditional_rule >,
      pegtl::seq< pegtl::at< Instruction_branch_label_rule >, Instruction_branch_label_rule >,
      pegtl::seq< pegtl::at< Instruction_return_val_rule >, Instruction_return_val_rule >,
      pegtl::seq< pegtl::at< Instruction_return_rule >, Instruction_return_rule >,
      pegtl::seq< pegtl::at< Instruction_label_rule >, Instruction_label_rule >
    > {};
  struct Instructions_rule:
    pegtl::star<
      pegtl::seq<
        seps_with_comments,
        // pegtl::bol,
        spaces,
        Instruction_rule,
        seps_with_comments
      >
    > {};

  
  /*
  Function rules.
  */
  struct Function_header_rule:
    pegtl::seq<
      spaces,
      type_rule,
      spaces,
      defined_fname,
      spaces,
      pegtl::one< '(' >,
      spaces,
      pegtl::seq<
        pegtl::opt<
          pegtl::seq<
            type_rule,
            spaces,
            name_rule
          >
        >,
        spaces,
        pegtl::star<
          pegtl::seq<
            pegtl::one< ',' >,
            spaces,
            name_rule
          >
        >
      >,
      spaces,
      pegtl::one< ')' >
    > {};
  struct Function_rule:
    pegtl::seq<
      Function_header_rule,
      seps,
      spaces,
      pegtl::one< '{' >,
      Instructions_rule,
      spaces,
      pegtl::one< '}' >
    > {};
  struct Functions_rule:
    pegtl::plus<
      pegtl::seq<
        seps_with_comments,
        Function_rule,
        seps_with_comments
      >
    > {};


  /*
  Program rules.
  */
  struct entry_point_rule:
    pegtl::seq<
      Functions_rule
    > {};

  /*
  Grammar rules.
  */
  struct full_grammar :
    pegtl::must<
      entry_point_rule
    > {};


  /*
  Actions.
  */
  template< typename Rule >
  struct action : pegtl::nothing< Rule > {};

  /*
  Debug actions.
  */


  /*
  Terminal actions.
  */
  // template<> struct action < str_bracks > {
  //   template< typename Input >
  //   static void apply( const Input & in, Program & p) {
  //     if (debug) std::cerr << "Recognized a str_bracks rule\n";

  //     TypeEnum bracks = stringToType(in.string());  // stringToType() will error if string not in the dict.
  //     auto type = new Type(bracks);
  //     parsed_items.push_back(type);
  //   }
  // };
  // ^ redundant with type_keywords_rule

  template<> struct action < type_keywords_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized a type_keywords rule\n";

      TypeEnum type_keyword = stringToType(in.string());
      auto type = new Type(type_keyword);
      parsed_items.push_back(type);
    }
  };

  template<> struct action < label_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized a label rule\n";
      auto label = new Label(in.string());
      parsed_items.push_back(label);
    }
  };

  template<> struct action < name_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized a name rule\n";

      auto name = new Name(in.string());
      parsed_items.push_back(name);
      // if (debug) std::cerr << "pushed new Name onto, parsed_items now has size " << parsed_items.size() << "\n";
      UniqueNameTracker::updateLongestName(in.string());
    }
  };

  template<> struct action < N_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized an N rule\n";

      auto number = new Number(std::stoll(in.string()));
      parsed_items.push_back(number);
    }
  };

  template<> struct action < op_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized an op rule\n";

      OperationEnum op = stringToOperation(in.string());
      auto operation_instance = new Operation(op);
      parsed_items.push_back(operation_instance);
    }
  };

  template<> struct action < type_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized a type rule\n";

      auto type_temp = parsed_items.front();
      parsed_items.erase(parsed_items.begin());
      if (debug) std::cerr << "made it past grabbing the type " << type_temp->print() << "\n";
      if (debug) std::cerr << "parsed_items now has size " << parsed_items.size() << "\n";

      int64_t dims = 0;
      while (!parsed_items.empty()) {
        parsed_items.pop_back();
        dims++;
      }

      auto type = dynamic_cast<Type*>(type_temp);
      if (!type) {
        if (debug) std::cerr << "Program is incorrect, " << type->print() << " should be of Type type.\n";
      }

      type->set_dims(dims);
      parsed_items.push_back(type);
      if (debug) std::cerr << "pushed onto, parsed_items now has size " << parsed_items.size() << "\n";
    }
  };

  template<> struct action < defined_fname > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized a defined_fname rule\n";

      auto fname = parsed_items.back();
      parsed_items.pop_back();
      auto type = parsed_items.back();
      parsed_items.pop_back();

      if (debug) std::cerr << "grabbed the type and fname, parsed_items now has size " << parsed_items.size() << "\n";
      if (debug) std::cerr << "p.functions has size " << p.getSize() << "\n";

      auto function = new Function(fname, type);
      p.addFunction(function);

      if (debug) std::cerr << "created a function and added it, p.functions now has size " << p.getSize() << "\n";
    }
  };


  /*
  Instruction actions.
  */
  template<> struct action < Instruction_type_declaration_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // type name
      if (debug) std::cerr << "Recognized an Instruction_type_declaration rule\n";

      auto f = p.getLastFunction();
      auto name = popAndGrabBack(parsed_items);
      // name->isVariable = true;
      auto type = popAndGrabBack(parsed_items);

      auto i = new Instruction_type_declaration(type, name);
      f->addInstruction(i);
    }
  };

  template<> struct action < Instruction_dim_length_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // name1 <- length name2 t
      if (debug) std::cerr << "Recognized an Instruction_dim_length rule\n";

      auto f = p.getLastFunction();
      auto t = popAndGrabBack(parsed_items);
      auto name2 = popAndGrabBack(parsed_items);
      auto name1 = popAndGrabBack(parsed_items);

      auto i = new Instruction_length(name1, name2);
      i->setIndex(t);
      f->addInstruction(i);
    }
  };

  template<> struct action < Instruction_length_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // name1 <- length name2
      if (debug) std::cerr << "Recognized an Instruction_length rule\n";

      auto f = p.getLastFunction();
      auto name2 = popAndGrabBack(parsed_items);
      auto name1 = popAndGrabBack(parsed_items);

      // we can determine if name2 is a tuple later by checking if t is a nullptr
      auto i = new Instruction_length(name1, name2);
      f->addInstruction(i);
    }
  };

  template<> struct action < Instruction_call_function_assignment_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // name1 <- name2 ( args? )
      if (debug) std::cerr << "Recognized an Instruction_call_function_assignment rule\n";

      auto f = p.getLastFunction();
      auto name1 = popAndGrabFront(parsed_items);
      auto name2 = popAndGrabFront(parsed_items);

      auto i = new Instruction_call_function_assignment(name1, name2);

      while (!parsed_items.empty()) {
        auto arg = popAndGrabFront(parsed_items);
        i->addArg(arg);
      }

      f->addInstruction(i);
    }
  };

  template<> struct action < Instruction_call_function_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // name1 ( args? )
      if (debug) std::cerr << "Recognized an Instruction_call_function rule\n";

      auto f = p.getLastFunction();
      auto name1 = popAndGrabFront(parsed_items);

      auto i = new Instruction_call_function(name1);

      while (!parsed_items.empty()) {
        auto arg = popAndGrabFront(parsed_items);
        i->addArg(arg);
      }

      f->addInstruction(i);
    }
  };

  template<> struct action < Instruction_array_initialization_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // name <- new Array( args )
      if (debug) std::cerr << "Recognized an Instruction_array_initialization rule\n";

      auto f = p.getLastFunction();
      auto name = popAndGrabFront(parsed_items);

      auto i = new Instruction_initialization(name, CollectionEnum::Array);

      while (!parsed_items.empty()) {
        auto arg = popAndGrabFront(parsed_items);
        i->addArg(arg);
      }

      f->addInstruction(i);
    }
  };

  template<> struct action < Instruction_tuple_initialization_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // name <- new Tuple( t )
      if (debug) std::cerr << "Recognized an Instruction_tuple_initialization rule\n";

      auto f = p.getLastFunction();
      auto name = popAndGrabFront(parsed_items);

      auto i = new Instruction_initialization(name, CollectionEnum::Tuple);

      while (!parsed_items.empty()) {
        auto arg = popAndGrabFront(parsed_items);
        i->addArg(arg);
      }

      f->addInstruction(i);
    }
  };

  template<> struct action < Instruction_store_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // name([t])+... <- t
      if (debug) std::cerr << "Recognized an Instruction_store rule\n";

      auto f = p.getLastFunction();
      auto t = popAndGrabBack(parsed_items);
      auto name = popAndGrabFront(parsed_items);

      auto i = new Instruction_store(name, t);

      while (!parsed_items.empty()) {
        auto arg = popAndGrabFront(parsed_items);
        i->addArg(arg);
      }

      f->addInstruction(i);
    }
  };

  template<> struct action < Instruction_load_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // name1 <- name2([t])+...
      if (debug) std::cerr << "Recognized an Instruction_load rule\n";

      auto f = p.getLastFunction();
      auto name1 = popAndGrabFront(parsed_items);
      auto name2 = popAndGrabFront(parsed_items);

      auto i = new Instruction_load(name1, name2);

      while (!parsed_items.empty()) {
        auto arg = popAndGrabFront(parsed_items);
        i->addArg(arg);
      }

      f->addInstruction(i);
    }
  };

  template<> struct action < Instruction_operation_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // name <- t1 op t2
      if (debug) std::cerr << "Recognized an Instruction_operation_rule rule\n";

      auto f = p.getLastFunction();
      auto t2 = popAndGrabBack(parsed_items);
      auto op = popAndGrabBack(parsed_items);
      auto t1 = popAndGrabBack(parsed_items);
      auto name = popAndGrabBack(parsed_items);
      auto i = new Instruction_operation(name, t1, op, t2);
      f->addInstruction(i);
    }
  };

  template<> struct action < Instruction_branch_label_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // br label1
      if (debug) std::cerr << "Recognized an Instruction_branch_label rule\n";

      auto f = p.getLastFunction();
      auto label1 = popAndGrabBack(parsed_items);
      auto i = new Instruction_branch_single(label1);
      f->addInstruction(i);
    }
  };


  template<> struct action < Instruction_branch_label_conditional_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // br t label1 label2
      if (debug) std::cerr << "Recognized an Instruction_branch_label_conditional rule\n";

      auto f = p.getLastFunction();
      auto label2 = popAndGrabBack(parsed_items);
      auto label1 = popAndGrabBack(parsed_items);
      auto t = popAndGrabBack(parsed_items);
      auto i = new Instruction_branch_double(t, label1, label2);
      f->addInstruction(i);
    }
  };

  template<> struct action < Instruction_return_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // return
      if (debug) std::cerr << "Recognized an Instruction_return rule\n";

      auto f = p.getLastFunction();
      auto i = new Instruction_return();
      f->addInstruction(i);
    }
  };

  template<> struct action < Instruction_return_val_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      // return t
      if (debug) std::cerr << "Recognized an Instruction_return_val rule\n";

      auto f = p.getLastFunction();
      auto t = popAndGrabBack(parsed_items);
      auto i = new Instruction_return_value(t);
      f->addInstruction(i);
    }
  };


  /*
  Function actions.
  */
  template<> struct action < Function_header_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized a Function_header rule\n";

      auto f = p.getLastFunction();

      if (debug) std::cerr << "made it past grabbing the current function\n";

      if (debug) std::cerr << "parsed_items has size " << parsed_items.size() << " before the while loop\n";

      while (!parsed_items.empty()) {
        auto type = popAndGrabFront(parsed_items);
        if (debug) std::cerr << "made it past grabbing the type " << type->print() << "\n";
        auto name = popAndGrabFront(parsed_items);
        if (debug) std::cerr << "made it past grabbing the var " << name->print() << "\n";
        auto param = new Parameter(type, name);
        f->addParameter(param);
      }

    }
  };


  /*
  Program actions.
  */
  template<> struct action < entry_point_rule > {
    template< typename Input >
    static void apply( const Input & in, Program & p) {
      if (debug) std::cerr << "Recognized an entry_point rule, finished parsing the LA program!\n";
    }
  };


  /*
  Main parser function.
  */
  Program parse_file (char *filename) {
    /* 
    Check the grammar for some possible issues.
    */
    if (pegtl::analyze< full_grammar >() != 0){
      std::cerr << "There are problems with the grammar\n";
      exit(1);
    }
    std::cerr << "No problems with the grammar.\n";

    /*
     * Parse.
     */
    file_input< > fileInput(filename);
    Program p;
    parse< full_grammar, action >(fileInput, p);

    return p;
  }

}
