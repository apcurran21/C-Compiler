#include "L2.h"
#include "graph_coloring.h"

using namespace L2;

Node::Node(Variable *var) : var(var), degree(0) {
  // Initialize the Node with a variable and set the degree to 0.
}

u_int64_t Node::getDegree(void) const {
  // Return the degree of the node.
  return degree;
}

Variable* Node::get(void) const {
  // Return the variable associated with this node.
  return var;
}

void Node::addDegree(int64_t delta) {
  // Add delta to the degree of the node. This can be a positive or negative number.
  degree += delta;
}
void Graph::addNode(Node *node) {
  // Add a node to the graph with no connections initially.
  g[node] = std::set<Node *>();
  nodes[node->get()] = node;
}

void Graph::removeNode(Node *node) {
  // Remove all connections to this node.
  for (auto &pair : g) {
    pair.second.erase(node);
  }
  // Remove the node itself.
  g.erase(node);
  nodes.erase(node->get());
}

void Graph::addEdge(Node *src, Node *dst) {
  // Add an edge between src and dst nodes.
  g[src].insert(dst);
  g[dst].insert(src);
  // Increase the degree of both nodes.
  src->addDegree(1);
  dst->addDegree(1);
}

bool Graph::exists(Variable *var) {
  // Check if a node for the variable exists in the graph.
  return nodes.find(var) != nodes.end();
}

std::vector<Node*> Graph::getNodes(void) const {
  // Return a vector of all the nodes in the graph.
  std::vector<Node*> nodeVec;
  for (const auto &pair : g) {
    nodeVec.push_back(pair.first);
  }
  return nodeVec;
}

/*
Not implemented, commented out to prevent compiling errors
*/
// Graph* Graph::clone(void) const {
//   // Implement cloning if necessary. This is a non-trivial operation and requires deep copying.
  
// }

int32_t Graph::size(void) const {
  // Return the size of the graph, i.e., the number of nodes.
  return g.size();
}
