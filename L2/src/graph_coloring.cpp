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
    std::vector<std::string> gp_registers{
        "r10",
        "r11",
        "r8",
        "r9",
        "rax",
        "rcx",
        "rdi",
        "rdx",
        "rsi",
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
        Predefine the colors of all register nodes
        */
        color_registers(graph);

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
        Graph* result_graph = repopulate(graph, orig_graph, node_stack);
        
        // ColorResult result = {result_graph, result_graph}
        return result_graph;

    }

    /*
    Small helper function to go through the nodes in the graph which are actual registers and set thier color fields. 
    */
    void color_registers(Graph *g) {
      for (auto node : g->nodes) {
        // dynamic cast on the node to check if its variable field contains a Register instance instead of base Variable
        Register* reg_ptr = dynamic_cast<Register*>(node.first);
        if (reg_ptr) {
          // if it is a register, we color the node with its own defined color
          node.second->color = reg_ptr->name;
        }
      }
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
    std::vector<Node*> depopulate(Graph *g) {
      std::vector<Node*> small_degree_vec;
      std::vector<Node*> big_degree_vec;
      std::vector<Node*> stack;

      // place the vector of nodes into list format before sorting
      for (auto& node: g->getNodes()) {
        // we want to leave all the gp register nodes in the graph
        if (dynamic_cast<Register*>(node->var)) {}
        // otherwise we put the current node into the corresponding list depending on its number of neighbors
        else if (node->getDegree() < gp_registers.size()) {
          small_degree_vec.push_back(node);
        } else {
          big_degree_vec.push_back(node);
        }
      }

      while ((!small_degree_vec.empty()) || (!big_degree_vec.empty())) {
        // small_degree_vec.sort(compare_nodes);
        // big_degree_vec.sort(compare_nodes);
        std::sort(small_degree_vec.begin(), small_degree_vec.end(), cmp);
        std::sort(big_degree_vec.begin(), big_degree_vec.end(), cmp);

        // get the node with the most edges
        Node* curr_node;
        if (!small_degree_vec.empty()) {
          curr_node = small_degree_vec.back();
          small_degree_vec.pop_back();
        } else {
          curr_node = big_degree_vec.back();
          big_degree_vec.pop_back();
        }

        // remove the edges between the current node and its neighbors
        auto it = g->graph.find(curr_node);
        if (it != g->graph.end()) {
          std::set<Node*> curr_node_neighbors = it->second;
          for (auto neighbor: curr_node_neighbors) {
            g->removeEdge(curr_node, neighbor);
          }
        } else {
          if (debug) std::cout << "node not found in the graph" << std::endl;
        }

        // remove the current node from the graph
        g->graph.erase(curr_node);

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
      for (auto node : node_stack) {

        int max_number_nodes = 0;
        auto it1 = orig_g->nodes.find(node->var);
        if (it1 != orig_g->nodes.end()) {
          auto it2 = orig_g->graph.find(it1->second);
          if (it2 != orig_g->graph.end()) {
              // Key exists, access the size of the set associated with the key
              max_number_nodes = (std::min(it2->second.size(), g->getNodes().size()));
          } else {
            if (debug) std::cout << "the orig_g version of the current node wasn't found in the graph." << std::endl;
          }
        } else {
          if (debug) std::cout << "the current node's variable wasn't found in orig_g's variable-to-node mapping. Terminating." << std::endl;
          std::terminate();
        }

        /*
        Note for debugging - since we terminate if the variable pointer key isn't found in orig_g's , we're safe to use it1 here
        */
        
        // allocate an empty array to hold the current node's neighors in the current state of the graph
        // std::vector<Node*> node_current_neighbors(max_number_nodes);

        // get the original version of the current node
        auto it_curr_node_orig_g = orig_g->nodes.find(it1->first);
        // ^ just assume everything succeeds at this stage of debugging and use the iterator without checking for .end()

        // get a set of the current node's neighbors from the original cloned state
        auto it_curr_node_neighbors_orig_g = orig_g->graph.find(it_curr_node_orig_g->second);

        /*
        NOTE!!! lowkey this stage could just be our "set intersection" step
        the call to find() will fail whenever we try to lookup an orig_g node key in the current graph state g nodes map. 
        so in this case we just continue, since we only want to include nodes in curr_node_neighbors_g if they exist in 
        both the it_curr_node_neighbors_orig_g (orig_g versions of the current node's cloned/original neighbors) set and 
        the set of g version nodes that are included in the state of the current graph
        */

        

        // convert each node in the neighbor set to the current graph version and place into a new set
        std::vector<Node*> node_current_neighbors;
        // std::set<Node*> curr_node_neighbors_g;
        for (auto n : it_curr_node_neighbors_orig_g->second) {
          auto it_node = g->nodes.find(n->var);
          if (it_node != g->nodes.end()) {
            node_current_neighbors.push_back(it_node->second);
            // curr_node_neighbors_g.insert(it_node->second);
          }
          // it's okay to end up here - it only means that the node n isn't in the current state of the graph yet (ie still in the stack)
          // if (debug) std::cerr << "could not find the equivalent g equivalent for the current neighbor." << std::endl;
        }

        // // perform the operations using the current graph state version of the node pointers
        // auto it3 = std::set_intersection(
        //   curr_node_neighbors_g.begin(),
        //   curr_node_neighbors_g.end(),
        //   g->getNodes().begin(),
        //   g->getNodes().end(),
        //   node_current_neighbors.begin()
        // );
        // node_current_neighbors.resize(it3 - node_current_neighbors.begin());

        // using the above vector, create a set of the colors belonging to the neighbors of the current node, in the current graph
        std::set<std::string> neighbors_colors = get_colors(node_current_neighbors);

        // color the current node with the earliest one that doesn't conflict with the colors of the current node's neighbors
        for (auto color : gp_registers) {
          if (neighbors_colors.find(color) == neighbors_colors.end()) {
            node->color = color;
            break;
          }
        }

        // spill the variable if it wasn't able to be colored
        if (node->color.empty() && (g->spilled_vars.find(node->var) == g->spilled_vars.end())) {
          g->spilled_vars.insert(node->var);
        }

        // add the node back into the graph (if it wasn't able to be colored, then it still has an empty string and we spill)
        add_back_into_graph(node, node_current_neighbors, g);
      }

      return g;
    }


  void add_back_into_graph(Node* node, std::vector<Node*> neighbors, Graph* g) {
    g->addNode(node);
    for (auto neighbor : neighbors) {
      g->addEdge(node, neighbor);
    }
  }

  bool cmp(Node* a, Node* b) {
    return a->degree < b->degree;
  }

}