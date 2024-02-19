#include "graph_coloring.h"

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
    // Graph* color_graph(Graph *graph) {
    std::tuple<bool, std::vector<Node*>> color_graph(Program &p, Graph *graph, Function *fptr) {
        /*
        Clone the initial graph in case we need to spill all variables
        */
        Graph* graph_copy = graph->clone();

        /*
        Predefine the colors of all register nodes
        */
        color_registers(graph_copy);

        /*
        Call to some depopulate function which implements step 1 of the coloring algorithm:
        -Repeatedly select a node, remove it from the graph, and put on top of a stack
        -Should this function create a new stack and return it, or can we initialize it 
            outside of the function, pass a pointer as an arg, modify the memory, then return void?
        */
        std::vector<Node*> node_stack = depopulate(graph_copy);

        /*
        Call to some rebuild function which implements step 2 of the coloring algorithm
        -Select a color on each node as it comes back into the graph, making sure no adjacent
            nodes have the same color.
        */
        return repopulate(graph, graph_copy, node_stack);
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
    std::vector<Node*> depopulate(Graph *graph) {
      /*
      Initialize our return stack to hold the variable ordering.
      */
      std::vector<Node*> stack;

      /*
      Iterate until we've removed all non-register nodes.
      */
      while (graph->getSize() > 0) {

        /*
        Get and sort a list of the current variable nodes in the graph in non-decreasing order 
        */
        std::vector<Node*> curr_nodes = graph->getVarNodes();
        std::sort(curr_nodes.begin(), curr_nodes.end(), cmp);

        /*
        Initialize a best-so-far variable and check for the largest degree node less than N.
        */
        Node* best_node = nullptr;
        /*
        Iterate left to right (ie in the order of increasing degree)
        */
        for (auto node : curr_nodes) {
            if (node->degree >= gp_registers.size()) {
                /*
                If we encounter a node with degree greater than or equal to the number of colors,
                then stop searching the list of nodes since we know the far right will be the best.
                */
                break;
            }
            best_node = node;
        }
        if (best_node == nullptr) {
          /*
          Then there weren't any small degree nodes. Far right now holds the best.
          */
          best_node = curr_nodes.back();
        }
        stack.push_back(best_node);
        graph->removeNode(best_node);
      }

      /*
      return the stack of nodes, which are now ordered correctly according to step 1 of the slides coloring alg
      */
      return stack;
    }

    /*
    We need to compare the current state of the graph g with the initial state so that we know which edges to add back and when
    This function is for coloring each node as it comb
    */
    std::tuple<bool, std::vector<Node*>> repopulate(Graph* g, Graph* g_copy, std::vector<Node*> node_stack) {
      bool big_fail = false;
      std::vector<Node*> uncolored_nodes;
      
      bool failed_to_color = false;
      /*
      We need to try to color each node and add it back into the graph.
      - Would a while loop with pop_back() be safer here?
      */
      for (auto node : node_stack) {

        /*
        Get a set of the current node's neighbors from the original cloned state
        */
        std::set<Node*> full_neighbor_set;
        auto curr_node_in_original_graph_iterator = g_copy->nodes.find(node->var);
        if (curr_node_in_original_graph_iterator != g_copy->nodes.end()) {
          Node* n = curr_node_in_original_graph_iterator->second;
          auto full_neighbor_set_iterator = g_copy->graph.find(n);
          if (full_neighbor_set_iterator != g_copy->graph.end()) {
              full_neighbor_set = full_neighbor_set_iterator->second;
          } else {
              if (debug) std::cerr << "Couldn't find this node in the original graph.\n";
          }
        } else {
            if (debug) std::cerr << "Couldn't find this variable in any of the original graph's nodes.\n";
        }

        /*
        Get a vector of the current node's original neighbors which exist in the current state of the graph.
        */
        std::vector<Node*> neighbors_in_curr_graph;
        for (auto n : full_neighbor_set) {
            auto curr_graph_node_iterator = g_copy->nodes.find(n->var);
            if (curr_graph_node_iterator != g_copy->nodes.end()) {
                neighbors_in_curr_graph.push_back(curr_graph_node_iterator->second);
            }
        }

        /*
        Using the above vector, create a set of the colors belonging to the neighbors of the current node, 
        in the current state of the graph.
        */
        std::set<std::string> neighbors_colors = get_colors(neighbors_in_curr_graph);

        /*
        Color the current node with the earliest one that doesn't conflict with the colors of its neighbors.
        */
        for (auto color : gp_registers) {
          if (neighbors_colors.find(color) == neighbors_colors.end()) {
            node->color = color;
            break;
          }
        }

        /*
        Checking for spill conditions: if the current node's color field is still empty, then coloring failed.
        */
        if (node->color.empty()) {
          failed_to_color = true;
          /*
          Check if the current node is one of our spill variables
          */
          if (g->spill_vars.find(node->var) == g->spill_vars.end()) {
            /*
            If it isn't found in this map, we are allowed to spill it.
            */
            uncolored_nodes.push_back(node);
          }

          /*
          This check should have the same behavior as the one above. 
          */
          auto node_name = node->var->name;
          if (node_name[0]=='%' && node_name[1]=='S'){
              continue;
          }

          /*
          However if it is, we just add it into the graph without a color and hope another variable is able to be spilled so we can recalculate liveness.
          - ie do nothing here
          */
        }

        /*
        Add the node back into the graph (if it wasn't able to be colored, then it still has an empty string and we spill)
        */
        add_back_into_graph(node, neighbors_in_curr_graph, g);
      }
      /*
      We know we failed the big condition and have to spill everything if:
      - we know coloring failed, but no variables are eligible to be spilled
      */
      if (failed_to_color && (uncolored_nodes.size() == 0)) {
        big_fail = true;
      }

      return std::make_tuple(big_fail, uncolored_nodes);
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