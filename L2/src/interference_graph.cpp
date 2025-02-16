#include "L2.h"
#include "interference_graph.h"

namespace L2{
  Node::Node(Variable *var) : var(var), degree(0), color("") {
  }

  u_int64_t Node::getDegree(void) const {
    return degree;
  }

  Variable* Node::get(void) const {
    return this->var;
  }

  void Node::addDegree(int64_t delta) {
    degree += delta;
  }

  void Graph::addNode(Node *node) {
    // Check if the node already exists in the graph
    if (nodes.find(node->get()) != nodes.end()) {
        return;
    }

    // If the node doesn't exist, add it to the graph with no connections initially.
    graph[node] = std::set<Node*>();
    nodes[node->get()] = node; // Associate the Variable with the node here

    // Update the graph size
    size++;
}


  void Graph::removeNode(Node *node) {
    /*
    Iterate over all other nodes in the graph to handle if the given node is a neighbor to any of them.
    */
    std::vector<Node*> nodes_vec = getNodes();
    for (auto& other_node : nodes_vec) {
      auto it = graph.find(other_node);
      if (it != graph.end()) {
        /*
        go about erasing the current node from the other node's neighbors set
        */
        if (it->second.erase(node)) {
          /*
          the current node and the other node were neighbors, so we need to remove their edge.
          */
          it->first->addDegree(-1);
          node->addDegree(-1);
        }
      } else {
        if (debug) std::cerr << "something is probably wrong, couldn't find a node returned by getNodes() in the graph.\n";
      }
      /*
      This isn't strictly necessary since we will end up just removing the current node entirely from the graph,
      but we can also update its neighbors dictionary for debugging. Do this later.
      */
     
      // ...
    }

    /*
    Remove the node itself.
    - Should we also free the node's memory? we probably could, since the original copy of the
    node still lays outside of the depopulate function.
    */
    graph.erase(node);
    nodes.erase(node->get());
    size--;
  }

  void Graph::removeNodeByName(const std::string& varName) {
      // Find the node corresponding to varName
      for (auto& pair : nodes) {
          if (pair.first->name == varName) { // Assuming Variable has a 'name' field
              removeNode(pair.second); // removeNode is your existing method to remove the node
              break; // Exit after finding and removing the node to avoid iterator invalidation
          }
      }
  }

  void Graph::addEdge(Node *src, Node *dst) {
    // Check for null pointers before using them
    if (!src || !dst) {
        std::cerr << "Error: null pointer passed to addEdge" << std::endl;
        return; // Optionally, throw an exception or handle the error as appropriate
    }

    if (graph[src].find(dst) == graph[src].end()) {
      // Now it's safe to use src and dst
      graph[src].insert(dst);
      graph[dst].insert(src);

      // Check that the nodes exist before calling member functions
      if (src) {
          src->addDegree(1);
      }
      if (dst) {
          dst->addDegree(1);
      }
    }

  }

  void Graph::removeEdge(Node *src, Node *dst) {
    // assumes that an edge between src and dst exists, but check for null ptrs
    if (!src || !dst) {
      std::cerr << "Error: null pointer passed to addEdge" << std::endl;
      return; // Optionally, throw an exception or handle the error as appropriate
    }

    // remove the dst node from the src's node set of neighbors and vice versa
    graph[src].erase(dst);
    graph[dst].erase(src);

    // update the respective degrees
    src->addDegree(-1);
    dst->addDegree(-1);
  }

  bool Graph::exists(Variable *var) {
    // Check if a node for the variable exists in the graph.
    return nodes.find(var) != nodes.end();
  }

  std::vector<Node *> Graph::getNodes(void) const {
    // Return a vector of all the nodes in the graph.
    std::vector<Node *> nodeVec;
    for (const auto &pair : graph) {
      nodeVec.push_back(pair.first);
    }
    return nodeVec;
  }

  std::vector<Node *> Graph::getVarNodes(void) const {
    /*
    Return a vector of all non-register nodes in the graph.
    */
    std::vector<Node *> nodeVec;
    for (const auto &pair : nodes) {
      auto reg_ptr = dynamic_cast<Register*>(pair.first);
      if (!reg_ptr) {
        nodeVec.push_back(pair.second);
      }
    }
    return nodeVec;
  }

  Graph * Graph::clone(void) const {
    // Create a new graph instance.
    auto newGraph = new Graph();

    /*
    Make sure to transfer over all the original graph's spill variable set
    */
    newGraph->spill_vars = spill_vars;

    std::map<const Node*, Node*> origToNewNodeMap;

    for (const auto &nodePair : this->nodes) {
      Variable *var = nodePair.first;
      const Node *origNode = nodePair.second;
      // Create a new node with the same variable.
      Node *newNode = new Node(var);
      // You may want to copy the color or other attributes of Node here.
      newNode->color = origNode->color;
      // Add the new node to the new graph.
      newGraph->addNode(newNode);
      // Store it in the map.
      origToNewNodeMap[origNode] = newNode;
    }

    // Copy edges.
    for (const auto &edgePair : this->graph) {
      const Node *origNode = edgePair.first;
      for (const Node *connectedNode : edgePair.second) {
        // Find the corresponding new nodes.
        Node *newNode = origToNewNodeMap[origNode];
        Node *newConnectedNode = origToNewNodeMap[connectedNode];
        // Add the edge between the new nodes in the new graph.
        newGraph->addEdge(newNode, newConnectedNode);
      }
    }

    return newGraph;
  };

  // int32_t Graph::size(void) const {
  //   // Return the size of the graph, i.e., the number of nodes.
  //   return graph.size();
  // }
  void add_new_var(Graph *graph,std::set<Variable*>gen_kill_sets){
    for (auto variable: gen_kill_sets){
      if (graph->exists(variable)){
        continue;
      }
      graph->addNode(new Node(variable));
    }
    return;
  }
  void add_edges_var(Graph *graph,std::set<Variable*>in_out_sets){
    for (auto var1:in_out_sets){
      for (auto var2:in_out_sets){
        if (var1 == var2){
          continue;
        }
        graph->addEdge(graph->nodes[var1],graph->nodes[var2]);
      }
    }
  }
  void Graph::printGraph() const {
    for (const auto& node_pair : graph) {
        if (node_pair.first && node_pair.first->var) {
            // Print the name of the root node
            std::cout << node_pair.first->var->print();
        }
        for (const auto& connected_node : node_pair.second) {
            if (connected_node && connected_node->var) {
                // Print the connected nodes
                std::cout << " " << connected_node->var->print();
            }
        }
        std::cout << std::endl; 
    }
  }
  // Graph* Graph::build_graph(Program &p, LivenessResult result ){
  // Graph* build_graph(Program &p, LivenessResult result){
  Graph* build_graph(Function *f, Curr_F_Liveness result) {
    auto interference_graph = new Graph();

    /*
    Add the functions current list of spill and spilled variables to the graph's corresponding field
    - spilled variables probably aren't necessary
    */
    interference_graph->spilled_vars = f->spilled_variables;
    interference_graph->spill_vars = f->spill_variables_set;

    /*
    Initialize the graph's size metric.
    */
    interference_graph->size = 0;

    std::set<Variable *> registers;
    // gp registers vector
    std::vector<std::string> gp_registers{
        "r10",
        "r11",
        "r12",
        "r13",
        "r14",
        "r15",
        "r8",
        "r9",
        "rax",
        "rbp",
        "rbx",
        "rcx",
        "rdi",
        "rdx",
        "rsi"
    };
    //add registers
    for (auto register_ID : gp_registers){
        Variable* var = f->variable_allocator.allocate_variable(register_ID, VariableType::reg);
        registers.insert(var);
        Node* node = new Node(var); // Assuming Node constructor takes a Variable*
        interference_graph->addNode(node);
    }
    for (auto i : f->instructions){
        // add_new_var(interference_graph,gen_kill_set.Gen_Set[0][i]);//hopefully this doesn't cause an error later on 
        // add_new_var(interference_graph,gen_kill_set.Kill_Set[0][i]);
        add_new_var(interference_graph, result.gen[i]);
        add_new_var(interference_graph, result.kill[i]);
    }
    //add nodes and connect variables in Kill[i] with those in OUT[i]
    for (auto i : f->instructions){
        // add_edges_var(interference_graph,in_out_sets.In_Set[0][i]);
        // add_edges_var(interference_graph,in_out_sets.Out_Set[0][i]);
        add_edges_var(interference_graph, result.in[i]);
        add_edges_var(interference_graph, result.out[i]);
        std::set<Variable *> insert_set;
        // insert_set.insert(gen_kill_set.Kill_Set[0][i].begin(),gen_kill_set.Kill_Set[0][i].end());
        // insert_set.insert(in_out_sets.Out_Set[0][i].begin(),in_out_sets.Out_Set[0][i].end());
        insert_set.insert(result.kill[i].begin(), result.kill[i].end());
        insert_set.insert(result.out[i].begin(), result.out[i].end());
        add_edges_var(interference_graph, insert_set);
    }
    add_edges_var(interference_graph, registers);
    for (auto i: f->instructions){
      auto checker = dynamic_cast<SOP_assignment*>(i);
      if (!i ||! checker){
        continue;
      }
      auto source_variable = dynamic_cast<Variable*>(checker->src);
      if (!source_variable){
        continue;
      }
      std::set<Variable*> register_insertions;
      register_insertions.insert(registers.begin(),registers.end());
      for (auto variable:registers){
        auto checking_register = dynamic_cast<Register *>(variable);
        if (checking_register->name != "rcx"){
          continue;
        }
        register_insertions.erase(checking_register);
      }
      register_insertions.insert(source_variable);
      add_edges_var(interference_graph,register_insertions);
    }
    return interference_graph;
  }

  /*
  Returns a set of the colors contained within a 
  - NOTE - what if empty strings make it into this set?? is this possible?
  - Ie it's possible for a node to have neighbors which are uncolored (ie if they
    will get spilled eventually.)
  - Actually we don't need to worry about that though since we only use this set to
    get the first of the 15 colors which isn't currently being used by one of these
    neighbors. We are never going to try and color with the empty string, so who cares
    if it's in this set right?
      - we could also just do a check on a string before adding into 'colors' if it 
        ends up mattering. 
  */
  std::set<std::string> get_colors(std::vector<Node*> nodes) {
    std::set<std::string> colors;
    for (auto node : nodes) {
      colors.insert(node->color);
    }
    return colors;
  }

  /*
  Prints each node in the graph and its assigned color for verification
  */
  void Graph::printColors() const {
    for (auto node : getNodes()) {
      std::cout << "Name = " << node->var->print() << ", Color = " << node->color << "\n";
    }
  }

  /*
  Prints the degree of each node in the graph for debugging purposes.
  */
  void Graph::printNodeDegrees() const {
    for (auto node: getNodes()) {
      std::cout << "Name = " << node->var->print() << ", Degree = " << node->degree << "\n";
    }
  }

  /*
  Get's the size of the graph without counting the general purpose registers.
  - If it returns a negative number, something went wrong.
  - Also number of gp registers is hardcoded to 15 for now, change later.
  */
  int32_t Graph::getSize() {
    int32_t adj_size = size - 15;
    if (adj_size < 0) {
      if (debug) std::cerr << "Something wrong happened to the graph's size and gp register nodes.\n";
    }
    return adj_size;
  }
}

