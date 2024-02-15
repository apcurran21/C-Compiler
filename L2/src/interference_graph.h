#pragma once 

#include <map>
#include <set>
#include <string>

// #include <L2.h>
// #include <graph_coloring.h>

namespace L2{

    // Forward declarations
    class Program;
    struct LivenessResult;

    // Declare a r
    class Node{
        public:
            Node (Variable *var);
            u_int64_t getDegree(void) const;
            Variable* get(void) const;
            void addDegree(int64_t delta);
            Variable *var; 
            int64_t degree;
            std::string color;
    };
    // Generic class declarations for nodes and graph
    class Graph{
        public:
            std::map<Node *,std::set<Node *>> graph;
            std::map<Variable *, Node *> nodes;
            std::set<Variable *> spilled_vars;
            void addNode(Node *node);
            void removeNode(Node *node);
            void addEdge(Node *src, Node *dst);
            void removeEdge(Node *src, Node *dst);
            bool exists(Variable *var);
            std::vector<Node *> getNodes(void) const;
            Graph * clone(void) const; //If we ever need to make a clone
            int32_t size(void) const;
            Graph * build_graph(Program &p, LivenessResult result);
            void printGraph() const;
            void printColors() const;
    };

    std::set<std::string> get_colors(std::vector<Node*> nodes);

}