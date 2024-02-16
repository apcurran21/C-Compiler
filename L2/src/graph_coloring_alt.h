#pragma once

#include "L2.h"
#include "interference_graph.h"

namespace L2 {

    /*
    Get the best order of nodes as layed out in the slides
    */
    std::vector<Node*> get_node_order(Graph* graph);

    /*
    Color variable nodes in the order received from the above function
    */
    std::map<Variable*, std::string>  color_graph(Graph* graph);


    /*
    Comparison function for sorting
    */
    bool cmp(Node* a, Node* b);

    
    /*
    Do the initial step of coloring register nodes with their own colors
    */
    void color_registers(Graph *g);
}