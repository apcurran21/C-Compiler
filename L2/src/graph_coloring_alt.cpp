#include "graph_coloring_alt.h"

namespace L2 {

    // list of general purpose registors for convenience,
    // manually sorted according to the slides
    std::vector<std::string> gp_registers_alt{
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
    The main graph coloring function. Returns a vector of nodes that weren't colored (ie need spilling).
    */
    std::vector<Node*> color_graph_alt(Program &p, Graph* graph, Function* fptr) {
        /*
        Create a copy of the graph to manipulate.
        */
        Graph* graph_copy = graph->clone();

        /*
        Initialize a set for nodes not colored.
        */
        std::vector<Node*> uncolored_nodes;

        /*
        Precolor the register nodes.
        */
        color_registers_alt(graph_copy);

        /*
        Order the nodes based on degree.
        */
        std::vector<Node*> node_stack = get_node_order_alt(graph_copy);

        /*
        Assign register colors to nodes.
        */
        while (!node_stack.empty()) {
            /*
            Get the best node.
            */
            Node* curr_node = node_stack.back();
            node_stack.pop_back();

            /*
            Check if already colored, skip if so.
            */
            if (!curr_node->color.empty()) {
                continue;
            }
            // auto it1 = result_map.find(curr_node->var);
            // if (it != result_map.end()) {
            //     continue;
            // }

            /*
            Here, node has not been colored. We look for the best color we are allowed to assign it.
            */
            for (auto color : gp_registers_alt) {

                bool found = false;

                /*
                Iterate the current node's neighbors to check their colors.
                */
                for (auto neighbor : graph->graph[curr_node]) {
                    /*
                    Check if the neighbor has been colored.
                    */
                    if (neighbor->color.empty()) {
                        /*
                        The current neighbor has not been colored, we continue.
                        */
                    }
                    // auto it2 = result_map.find(neighbor->var);
                    // if (it2 == result_map.end()) {
                    //     /*
                    //     The current neighbor has not been colored, we continue.
                    //     */
                    // }

                    /*
                    Here the current neighbor has been colored. We check if it is a different color than the current node.
                    - it should be safe to use brackets here.
                    */
                    // std::string neighbor_color = result_map[neighbor->var];
                    std::string neighbor_color = neighbor->color;
                    if (neighbor_color == color) {
                        /*
                        The neighbor shares this color, so we can't use it for the current node.
                        */
                       found = true;
                       break;
                    } 
                }

                /*
                Check if the current color can be used for the current node.
                */
                if (!found) {
                    /*
                    This means we can color this node with this color
                    */
                    graph->nodes[curr_node->var]->color = color;
                    break;
                }
            }

            /*
            No color was able to be given to the node, so make sure we mark it for spilling (if not already seen).
            */
            // auto it3 = result_map.find(curr_node->var);
            // if (it3 == result_map.end()) {
            //     uncolored_nodes.push_back(curr_node->var);
            // }
            if (curr_node->color.empty()) {
                uncolored_nodes.push_back(curr_node);
            }
        }

        /*
        Having gone through and colored each possible node, we return the ones that had to be spilled.
        */
       return uncolored_nodes;
    }


    /*
    Helper for getting nodes out of the graph based on coloring order
    */
    std::vector<Node*> get_node_order_alt(Graph* graph) {
        /*
        Initialize our return stack to hold the variable ordering.
        */
        std::vector<Node*> stack;
        
        /*
        Iterate until the graph is emptied.
        */
        while (graph->size > 0) {

            /*
            Step 1 of heuristic 1 - remove nodes with degree strictly less than number of colors, decreasing order 
            */
            while (graph->size > 0) {

                std::vector<Node*> curr_nodes = graph->getNodes();

                std::sort(curr_nodes.begin(), curr_nodes.end(), cmp_alt);

                /*
                Step 2 of heuristic 2 - remove nodes with degree greater than or equal to the current node.
                */
                Node* best_node = nullptr;
                for (auto node : curr_nodes) {
                    if (node->degree >= gp_registers_alt.size()) {
                        break;
                    }
                    best_node = node;
                }
                if (best_node == nullptr) {
                    break;
                }

                /*
                Remove this best node.
                */
                stack.push_back(best_node);
                graph->removeNode(best_node);
            }
        }

        /*
        Return the populated stack
        */
        return stack;
    }


    /*
    Helper for the std::sort functions
    - returns true if the left object is strictly less than the right
    */
    bool cmp_alt(Node* a, Node* b) {
        return a->degree < b->degree;
    }


    void color_registers_alt(Graph *g) {
        for (auto node : g->nodes) {
            Register* reg_ptr = dynamic_cast<Register*>(node.first);
            if (reg_ptr) {
                g->nodes[node.first]->color = reg_ptr->name;
            }
        }
    }
    
    /*
    Do the initial step of coloring register nodes with their own colors
    */
    // old implementation returns 'result_map'
    // std::map<Variable*, std::string> color_registers(Graph *g) {
    //     std::map<Variable*, std::string> var_to_color;
    //     for (auto node : g->nodes) {
    //         Register* reg_ptr = dynamic_cast<Register*>(node.first);
    //         if (reg_ptr) {
    //             var_to_color[node.first] = reg_ptr->name;
    //         }
    //     }
    //     return var_to_color;
    // }


}