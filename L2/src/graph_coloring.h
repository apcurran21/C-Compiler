#pragma once

#include "L2.h"
#include "interference_graph.h"

namespace L2 {

    /*
    The main graph coloring function.
    Inputs:
        Graph* (pointer to the interference graph we are trying to color)
    Outputs:
        Graph* (pointer to the now colored graph, null pointer if unsuccessful)
    */
    // ColorResult color_graph(Graph *graph);
    // Graph* color_graph(Graph *graph);

    /*
    This function returns a bool indicating whether it failed to color any, and the vector of nodes it failed to color.
    */
    std::tuple<bool, std::vector<Node*>> color_graph(Graph *graph, Graph *graph_copy, Function *fptr);

    /*
    Do the initial step of coloring register nodes with their own colors
    */
    void color_registers(Graph *g);

    /*
    Repeatedly takes out nodes from the graph and return them in a stack
    */
    std::vector<Node*> depopulate(Graph *graph);

    /*
    Chooses colors and places nodes back into the graph
    */
    std::tuple<bool, std::vector<Node*>> repopulate(Graph *graph, Graph *graph_copy, std::vector<Node*> node_stack);

    /*
    Places edges between a given node and its neighbors described in the vector arg 
    */
    void add_back_into_graph(Node* node, std::vector<Node*> neighbors, Graph* g);

    /*
    Parses an L2 interference graph file into a graph memory representation
    */
    Graph* parse_graph (char *filename);
    
    /*
    comparison function for sorting
    */
    bool cmp(Node* a, Node* b);
}