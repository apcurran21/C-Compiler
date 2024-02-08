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
    Graph* color_graph (Graph *graph);

    /*
    Repeatedly takes out nodes from the graph and return them in a stack
    */
    std::vector<Node*> depopulate(Graph *graph);

    /*
    Parses an L2 interference graph file into a graph memory representation
    */
    Graph* parse_graph (char *filename);


}