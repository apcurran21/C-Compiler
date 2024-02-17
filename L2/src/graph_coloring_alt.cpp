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
    -NOTE - we still need to make conversions between the cloned and original versions for each node.
    */
    std::vector<Node*> color_graph_alt(Program &p, Graph* graph, Function* fptr) {
        /*
        Create a copy of the graph to manipulate. We'll update the function to use this graph (this might cause memory leaks).
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
        Order the non-register nodes based on degree.
        -This function also removes all these non-register nodes (their respective) edges from the graph_copy.
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
            Check if already colored, skip if so. This should happen however.
            */
            if (!curr_node->color.empty()) {
                if (debug) std::cerr << "Found a colored node in the stack of uncolored nodes?\n";
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
                Iterate the current node's current neighbors to check their colors.
                - Since 
                */
                for (auto neighbor : graph->graph[curr_node]) {
                    /*
                    Check if the neighbor has a color. 
                    */
                    if (neighbor->color.empty()) {
                        /*
                        The current neighbor does not have a color. This could mean one of two things:
                        - The neighbor has been seen but could not be colored -> we will try to spill it eventually.
                        - The neighbor
                        */
                       continue;
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

                if (!found) {
                    /*
                    If the flag indicates the current color is not found, we use it for this node. 
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
                /*
                Check if the current node is a spill variable - we don't want to spill it again in this case. 
                - Current behavior is to just avoid placing it into the uncolored_nodes stack.
                - We'll probably want to come up with a slightly different method for tracking, in case the coloring 
                    alg finds that no variables can be colored other than spill variables (the bad edge case).
                    - an idea could be to also keep track of an uncolored spill variable set. if at the end of the  
                        alg, the uncolored_nodes set is empty but the uncolored_spill isn't, then we need to spill 
                        everything in the original graph.
                */
                if (fptr->spill_variables_set.find(curr_node->var) != fptr->spill_variables_set.end()) {
                    continue;
                }
                uncolored_nodes.push_back(curr_node);
            }
        }

        /*
        Having gone through and colored each possible node, we return the ones that couldn't be colored and need to be spilled.
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
        while (graph->getSize() > 0) {

            /*
            Part 1 of the node selection heuristic - find and remove nodes with degree strictly less than number of colors, decreasing order 
            */
            while (graph->getSize() > 0) {

                /*
                Get and sort a list of the current variable nodes in the graph in non-decreasing order 
                */
                std::vector<Node*> curr_nodes = graph->getVarNodes();
                std::sort(curr_nodes.begin(), curr_nodes.end(), cmp_alt);

                /*
                Initialize a best-so-far variable.
                */
                Node* best_node = nullptr;
                /*
                Iterate left to right (ie in the order of increasing degree)
                */
                for (auto node : curr_nodes) {
                    if (node->degree >= gp_registers_alt.size()) {
                        /*
                        If we encounter a node with degree greater than or equal to the number of colors,
                        then stop searching the list of nodes.
                        */
                        break;
                    }
                    best_node = node;
                }
                if (best_node == nullptr) {
                    /*
                    If the best_node is still a nullptr, this means we didn't find any nodes with degree
                    less than the number of colors. 
                    */
                    break;
                }

                /*
                If we made it here, it means we were able to find a node with degree less than the
                number of colors. Push the node onto our stack and remove from the graph.
                */
                stack.push_back(best_node);
                graph->removeNode(best_node);
            }

            /*
            By making it here, we know there aren't any more nodes with degree less than number of colors
            left in the graph. We iterate and try to remove these remaining nodes next.
            */
            while (graph->getSize() > 0) {
                /*
                Get the current variable nodes in the graph and sort them again in terms of non-decreasing degree.
                */
                std::vector<Node*> curr_nodes = graph->getVarNodes();
                std::sort(curr_nodes.begin(), curr_nodes.end(), cmp_alt);

                /*
                The largest-degree node will be at the back of 'curr_nodes' vector, so if this number is less
                than the number of colors we break execution back to part 2 of the node selection heuristic.
                */
                if (curr_nodes.back()->degree < gp_registers_alt.size()) {
                    break;
                }

                /*
                Otherwise we know that this is the node with largest degree in the graph, so we add it to
                the stack and remove from the graph according to part 2 of the node selection heuristic.
                */
                stack.push_back(curr_nodes.back());
                graph->removeNode(curr_nodes.back());
            }
        }
        /*
        Return the now fully populated stack
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