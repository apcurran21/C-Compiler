#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/analyze.hpp>
#include <tao/pegtl/contrib/raw_string.hpp>

#include "graph_coloring.h"

namespace pegtl = TAO_PEGTL_NAMESPACE;

using namespace pegtl;
using namespace std;

namespace L2 {

    /*
    The main graph coloring function.
    Inputs:
        Graph* (pointer to the interference graph we are trying to color)
    Outputs:
        Graph* (pointer to the now colored graph, null pointer if unsuccessful)
    */
    Graph* color_graph(Graph *graph) {
        
        /*
        Clone the initial graph in case we need to spill all variables
        */
        Graph* orig_clone = graph->clone();

        /*
        Call to some depopulate function which implements step 1 of the coloring algorithm:
        -Repeatedly select a node, remove it from the graph, and put on top of a stack
        -Should this function create a new stack and return it, or can we initialize it 
            outside of the function, pass a pointer as an arg, modify the memory, then return void?
        */
        
        std::vector<Node*> node_stack = depopulate(graph);

        /*
        Call to some rebuild function which implements step 2 of the coloring algorithm
        -Select a color on each node as it comes back into the graph, making sure no adjacent
            nodes have the same color.
        -
        */

    }


    std::vector<Node*> depopulate(Graph *g) {

    }





  /*
  Parsing utilities, structs, actions for interference graph files
  */
  std::vector<Register*> parsed_items;

  struct str_percent : TAO_PEGTL_STRING("%") {};

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

  struct node_name:
    pegtl::seq<
      pegtl::opt<str_percent>,
      pegtl::plus<
        pegtl::alnum
      >
    > {};

  struct nodes_line:
    pegtl::seq<
      node_name,
      pegtl::star<
        pegtl::seq<
          pegtl::space,
          node_name
        >
      >
    > {};

  struct nodes_lines:
    pegtl::seq<
      seps,
      pegtl::plus<nodes_line>,
      seps
    > {};

  template< typename Rule >
  struct action : pegtl::nothing< Rule > {};

  // template<> struct action < node_name > {
  //   template< typename Input >
  //   static void apply( const Input & in, Graph & g) {
  //     if (debug) std::cerr << "Recognized a node_name rule" << std::endl;

  //     auto var_ptr = 
  //   }
  // }






}