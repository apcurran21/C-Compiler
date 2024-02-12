#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/analyze.hpp>
#include <tao/pegtl/contrib/raw_string.hpp>

#include "graph_coloring.h"

namespace pegtl = TAO_PEGTL_NAMESPACE;

using namespace pegtl;
using namespace std;

namespace L2 {

    // list of general purpose registors for convenience
    // manually sorted according to the slides
    // should probably put this in L2 later
    std::set<std::string> gp_registers{
        "r10",
        "r11",
        "r8",
        "r9",
        "rax",
        "rcx",
        "rdi",
        "rdx",
        "rsi"
        "r12",
        "r13",
        "r14",
        "r15",
        "rbp",
        "rbx",
    };

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
        Graph* orig_graph = graph->clone();

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
        */
        return repopulate(graph, orig_graph, node_stack);

    }


    /*
    -We'll track the general ordering of the nodes based on their degree in a priority queue data structure. This will be used in tandem
    with an unordered map which maps Nodes to their positions in the std::priority_queue vector. This allows us to access neighbors
    that aren't at the top of the queue meaning we can update their degrees and position in the queue (this might be tricky, in order
    for a node's position to be updated, does it need to be popped and then reinserted into the queue?)
    -It might make sense to keep two priority queues, one for nodes with degree < num registers and one for degree >= num registers.
    -Alternatively, it could be nice to just repeatedly pop from the priority queue and into a regular queue until we see a node with
    degree < num registers. If the priority queue empties before we find a node with a small enough degree, then we have already 
    conveniently stored the large-degree nodes with the correct ordering. 
    */
    std::vector<Node*> depopulate(Graph *g, Graph *orig_g) {
      std::list<Node*> small_degree_lst;
      std::list<Node*> big_degree_lst;
      std::vector<Node*> stack;

      // place the vector of nodes into list format before sorting
      for (auto& node: g->getNodes()) {
        // we want to leave all the gp register nodes in the graph
        if (dynamic_cast<Register*>(node->var)) {}
        // otherwise we put the current node into the corresponding list depending on its number of neighbors
        else if (node->getDegree() < gp_registers.size()) {
          small_degree_lst.push_back(node);
        } else {
          big_degree_lst.push_back(node);
        }
      }

      while ((!small_degree_lst.empty()) && (big_degree_lst.empty())) {
        small_degree_lst.sort(compare_nodes);
        big_degree_lst.sort(compare_nodes);

        // get the node with the most edges
        Node* curr_node;
        if (!small_degree_lst.empty()) {
          curr_node = small_degree_lst.front();
          small_degree_lst.pop_front();
        } else {
          curr_node = big_degree_lst.front();
          big_degree_lst.pop_front();
        }

        // remove the edges between the current node and its neighbors
        for (auto node: small_degree_lst) {
          g->removeEdge(curr_node, node);
        }

        // remove the current node from the graph's list of nodes
        // ie we need it so that we can initialize our "already in the graph" set
        g->nodes.erase(curr_node->var);

        stack.push_back(curr_node);
      }

      // return the stack of nodes, which are now ordered correctly according to step 1 of the slides coloring alg
      return stack;
    }

    /*
    We need to compare the current state of the graph g with the initial state so that we know which edges to add back and when
    This function is for coloring each node as it comb
    */
    Graph* repopulate(Graph* g, Graph* orig_g, std::vector<Node*> node_stack) {
      // each node in the stack needs to be colored and added back into the stack
      for (auto& node : node_stack) {

        // get a list of this current node's set of neighbors that are currently in the graph
        std::vector<Node*> current_neighbors(orig_g->graph[node].size() + g->getNodes().size());
        std::vector<Node*> current_g_nodes(orig_g->graph[node].begin(), orig_g->graph[node].end());

        // get the the neighbors of the current node which are currently in the graph
        std::set_union(
          current_g_nodes.begin(),
          current_g_nodes.end(),
          g->getNodes().begin(),
          g->getNodes().end(),
          current_neighbors.begin()
        );

        // using the above vector, create a set of the current node's neighbors' colors
        std::set<std::string> neighbors_colors = get_colors(current_neighbors);

        // color the current node with the earliest one that doesn't conflict with the colors of the current node's neighbors
        for (auto color : gp_registers) {
          if (neighbors_colors.find(color) == neighbors_colors.end()) {
            node->color = color;
          }
        }

        // spill the variable if it wasn't able to be colored
        if (node->color.empty() && (g->spilled_vars.find(node->var) == g->spilled_vars.end())) {
          g->spilled_vars.insert(node->var);
        }

        // add the node back into the graph (if it wasn't able to be colored, then it still has an empty string and we spill)
        add_back_into_graph(node, current_neighbors, g);
      }

      // currently just return g - still need to check for the special case where nothing gets colored
      return g;
    }


  void add_back_into_graph(Node* node, std::vector<Node*> neighbors, Graph* g) {
    g->addNode(node);
    for (auto neighbor : neighbors) {
      g->addEdge(node, neighbor);
    }
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