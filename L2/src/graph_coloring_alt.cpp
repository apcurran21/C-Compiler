#include "graph_coloring_alt.h"

namespace L2 {

    // list of general purpose registors for convenience,
    // manually sorted according to the slides
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
    The main graph coloring function. Returns a mapping from variables to registers,
    allocated by the current function's variable allocator.
    */
    std::map<Variable*, std::string> color_graph(Graph* graph, Function* fptr) {
        /*
        Create a copy of the graph to manipulate.
        */
        Graph* graph_copy = graph->clone();

        /*
        Precolor the register nodes.
        */
        std::map<Variable*, std::string> result_map = color_registers(graph);

        /*
        Order the nodes based on degree.
        */
        std::vector<Node*> node_stack = get_node_order(graph_copy);

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
            auto it = result_map.find(curr_node->var);
            if (it != result_map.end()) {
                continue;
            }

            /*
            Here, node has not been colored. 
            */
        }

    }


    /*
    Helper for getting nodes out of the graph based on coloring order
    */
    std::vector<Node*> get_node_order(Graph* graph) {
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

                vector<Node*> curr_nodes = graph->getNodes();

                std::sort(curr_nodes.begin(), curr_nodes.end(), cmp);

                /*
                Step 2 of heuristic 2 - remove nodes with degree greater than or equal to the current node.
                */
                Node* best_node = nullptr;
                for (auto node : curr_nodes) {
                    if (node->degree >= gp_registers.size()) {
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
    bool cmp(Node* a, Node* b) {
        return a->degree < b->degree;
    }

    
    /*
    Do the initial step of coloring register nodes with their own colors
    */
    std::map<Variable*, std::string> color_registers(Graph *g) {
        std::map<Variable*, std::string> var_to_color;
        for (auto node : g->nodes) {
            Register* reg_ptr = dynamic_cast<Register*>(node.first);
            if (reg_ptr) {
                var_to_color[node.first] = reg_ptr->name;
            }
        }
        return var_to_color;
    }
}