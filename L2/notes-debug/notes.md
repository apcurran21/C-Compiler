# L2, Liveness Analysis, etc.

## Questions

## Notes
Overall, we need to make sure that the parser is consistent somehow with the singleton approach to variables that is used in liveness analysis. Worst case, we just do string compare in the liveness analysis.
* Our main parser will probably fail, in most of the instruction rules involving the phrase *mem* it expects an extra *Operator* instance to be on the *parsed_items* stack, and grabbing its value and then popping. We shouldn't mess with it now, but if we experience issues then this is the likely cause.
    * Actually nvm its all good we don't actually pull or pop from the stack for a *mem* tag
* there might be an error with how we defined the stackarg_rules and instructions in the parser.cpp file
    * NOTE - I changed the definition of the stackarg_assignment class in L2.cpp/h to get rid of the method attribute, this was unneccessary since we have a specific stackarg instruction class (no need to put the *stackarg* tag onto parsed items)
        * I also made it inherit from the base Instruction class instead of Instruction_assignment, since it wasn't doing anything and just redefining the source and destination attributes

### Gen, Kill, In, Out
* I think its best to have these each get their own classes etc because the rules about how they are defined could change later, and we don't want to have to go in and change everything in each instructions class etc in this case.
    * for instance, the calling convention in GEN/KILL may be different for future languages.
* Eventually, we should better format our file and class hierarchies so that this is all more easily extendable (we can talk about this )

### Variable allocation structure
* We define a VariableAllocator class in *L2.h*, which has the following:
    * private *allocated_vars* attribute (unordered map of strings to *Variable* pointers).
    * public *allocate()* method that takes a string (name of the variable to be allocated), checks in the *allocated_vars* map to see if a variable with this string already exists. If it does, then it just returns the associated pointer to the user. Otherwise it allocates a new variable instance to the heap using *new* and then returns this pointer to the user, making sure to update the map with this new entry.
    * public *is_defined()* method that takes a variable name, then returns whether or not a variable with this name exists in the map. This will probably only be use in debugging.
* How many instances of this allocator class will exist? Since varaibles have local scope in L2, it might make sense for each function to get its own allocator instance. Is it best for variables with the same name, but encountered/allocated in different functions, to have different instances and therefore pointers?

### Graph Coloring
During the repopulation stage of our graph, where we assign each node a color one by one, we need to have access to the following information:
* who the current node is
* what nodes are already in the graph
* who that node's neighbors are in the original copy of the graph
* who that node's neighbors are in the current state of the graph
  * especially what those neighbors colors are. 
  * NOTE that during the repopulation algorithm, the current node is not yet
    in the graph, so it doesn't actually have any neighbors
    * one way for us to know this set of neighbors (which is likely as subset of
      the current node's full set of neighbors in the original copy of the graph)
      is to take the union of the current node's set of neighbors in the original
      graph with the set of nodes that are currently in the graph.
* once we know who the current node's neighbors are in the current set of the graph,
  we can get a list of their colors in some fashion

### GDB Notes
* (*interference_graph.nodes.find(var)).first
    * this allows us to the different parts of a map given the pointer key
*  **gen_kill_set.Kill_Set[0][i].begin()
    * this allows us to get variable pointers in the interference_graph.cc:199 forloop
* \*(\*interference_graph.nodes.find(\*gen_kill_set.Kill_Set[0][i].begin())).second
    * this allows us to view the degree of the node associated with the given variable pointer

### Interference Graphs
* The degree fields for graphs are way to high, need to track down this bug first.
    * Since the output of the interference graph stage doesn't rely on this degree measurement
    we are able to pass all the test cases, which means we are just double counting neighbors somewhere.
#### Debug
* In the for loop at interference_graph.cpp:199, we notice at the first iteration:
    * i corresponds with the first '%check <- 1' instruction
    * the node corresponding with the variable '%check' has degree of 14 after reaching line 202, then has degree 28 after line 205 runs.
        * this doesn't seem right! realistically the number of potential neighbors that this node should get is 17 (15 gp registers, &c, and %arr).

**Question** do we add edges between a forbidden node/register and every other node in the graph (slide 9 constraints in interference)

### 2/13 debug notes
* segfault occurring during the call to repopulate in color_graph, likely during a union operation ... here's the backtrace:
> #0  __memmove_avx_unaligned_erms () at ../sysdeps/x86_64/multiarch/memmove-vec-unaligned-erms.S:516

> #1  0x0000000000412e84 in std::__copy_move<false, true, std::random_access_iterator_tag>::__copy_m<L2::Node*> (__first=0x4d0860, __last=0x4cf610, __result=0x4d75e0) at /opt/rh/gcc-toolset-11/root/usr/include/c++/11/bits/stl_algobase.h:431

> #2  0x0000000000412829 in std::__copy_move_a2<false, L2::Node**, L2::Node**> (__first=0x4d0860, __last=0x4cf610, __result=0x4d75e0) at /opt/rh/gcc-toolset-11/root/usr/include/c++/11/bits/stl_algobase.h:495

> #3  0x0000000000411fa3 in std::__copy_move_a1<false, L2::Node**, L2::Node**> (__first=0x4d0860, __last=0x4cf610, __result=0x4d75e0) at /opt/rh/gcc-toolset-11/root/usr/include/c++/11/bits/stl_algobase.h:522

> #4  0x000000000041125f in std::__copy_move_a<false, __gnu_cxx::__normal_iterator<L2::Node**, std::vector<L2::Node*, std::allocator<L2::Node*> > >, __gnu_cxx::__normal_iterator<L2::Node**, std::vector<L2::Node*, std::allocator<L2::Node*> > > > (__first=0x0, __last=0x0, __result=0x0) at /opt/rh/gcc-toolset-11/root/usr/include/c++/11/bits/stl_algobase.h:

> #5  0x000000000040f8f9 in std::copy<__gnu_cxx::__normal_iterator<L2::Node**, std::vector<L2::Node*, std::allocator<L2::Node*> > >, __gnu_cxx::__normal_iterator<L2::Node**, std::vector<L2::Node*, std::allocator<L2::Node*> > > > (__first=0x0, __last=0x0, __result=0x0) at /opt/rh/gcc-toolset-11/root/usr/include/c++/11/bits/stl_algobase.h:620

> #6  0x000000000040e412 in std::__set_union<__gnu_cxx::__normal_iterator<L2::Node**, std::vector<L2::Node*, std::allocator<L2::Node*> > >, __gnu_cxx::__normal_iterator<L2::Node**, std::vector<L2::Node*, std::allocator<L2::Node*> > >, __gnu_cxx::__normal_iterator<L2::Node**, std::vector<L2::Node*, std::allocator<L2::Node*> > >, __gnu_cxx::__ops::_Iter_less_iter> (__first1=non-dereferenceable iterator for std::vector, __last1=non-dereferenceable iterator for std::vector, __first2=0x0, __last2=0x0, __result=0x0, __comp=...) at /opt/rh/gcc-toolset-11/root/usr/include/c++/11/bits/stl_algo.h:5125

> #7  0x000000000040d411 in std::set_union<__gnu_cxx::__normal_iterator<L2::Node**, std::vector<L2::Node*, std::allocator<L2::Node*> > >, __gnu_cxx::__normal_iterator<L2::Node**, std::vector<L2::Node*, std::allocator<L2::Node*> > >, __gnu_cxx::__normal_iterator<L2::Node**, std::vector<L2::Node*, std::allocator<L2::Node*> > > > (__first1=non-dereferenceable iterator for std::vector, __last1=non-dereferenceable iterator for std::vector, __first2=0x0, __last2=0x0, __result=0x0) at /opt/rh/gcc-toolset-11/root/usr/include/c++/11/bits/stl_algo.h:5174

> #8  0x000000000040c01f in L2::repopulate (g=0x4da8c0, orig_g=0x4d5ac0, node_stack=std::vector of length 3, capacity 3 = {...}) at src/graph_coloring.cpp:142

> #9  0x000000000040ba2f in L2::color_graph (graph=0x4da8c0) at src/graph_coloring.cpp:62

> #10 0x00000000004075c1 in main (argc=6, argv=0x7fffffffd268) at src/compiler.cpp:161


* the '%check' variable now has no neighors in the orig_g graph, which does not seem right at all
    * the orig_graph is identical before and after the calls to depopulate, and also inside of the repopulate function immediately after beling called
    * there is an extra element in the map after the following call:
        * std::vector<Node*> node_current_neighbors(orig_g->graph[node].size() + g->getNodes().size());
        * for instance the before the call its 18, now its 19 but the set is empty

* 2/14/24 2:14pm
  * depopulate seems decent for the time being, segfaults still occurring inside of the repopulate call

* the "same" node in the current graph and the copy of the original graph will have different pointers, meaning that the current node in repopulate won't appear in the original graph's graph map (even though all the same info is there). However, we should be able to link the two versions of the same node via their variable field - since the variable allocator keeps track of a consistent pointer for that Variable instance, the contents of each node version's *var* field should be identical. So, in order to access the current node's neighbors using the orig_graph version of that node, we query the orig_graph's nodes map using the current node's var field.


>>> p orig_graph
$30 = (L2::Graph *) 0x4d5ac0
>>> p *orig_graph
$31 = {
  graph = std::map with 18 elements = {
    [0x4cd830] = std::set with 17 elements = {
      [0] = 0x4cd9a0,
      [1] = 0x4ceb50,
      [2] = 0x4d12b0,
      [3] = 0x4d1c60,
      [4] = 0x4d2580,
      [5] = 0x4d2fa0,
      [6] = 0x4d3460,
      [7] = 0x4d36a0,
      [8] = 0x4d3760,
      [9] = 0x4d5b60,
      [10] = 0x4d5c20,
      [11] = 0x4d5ce0,
      [12] = 0x4d5da0,
      [13] = 0x4d5e60,
      [14] = 0x4d5f20,
      [15] = 0x4d5fe0,
      [16] = 0x4d61f0
    },
    [0x4cd9a0] = std::set with 14 elements = {
      [0] = 0x4cd830,
      [1] = 0x4ceb50,
      [2] = 0x4d12b0,
      [3] = 0x4d1c60,
      [4] = 0x4d2fa0,
      [5] = 0x4d3460,
      [6] = 0x4d3760,
      [7] = 0x4d5b60,
      [8] = 0x4d5c20,
      [9] = 0x4d5ce0,
      [10] = 0x4d5da0,
      [11] = 0x4d5f20,
      [12] = 0x4d5fe0,
      [13] = 0x4d61f0
    },
    [0x4ceb50] = std::set with 14 elements = {
      [0] = 0x4cd830,
      [1] = 0x4cd9a0,
      [2] = 0x4d12b0,
      [3] = 0x4d1c60,
      [4] = 0x4d2fa0,
      [5] = 0x4d3460,
      [6] = 0x4d3760,
      [7] = 0x4d5b60,
      [8] = 0x4d5c20,
      [9] = 0x4d5ce0,
      [10] = 0x4d5da0,
      [11] = 0x4d5f20,
      [12] = 0x4d5fe0,
      [13] = 0x4d61f0
    },
    [0x4d12b0] = std::set with 14 elements = {
      [0] = 0x4cd830,
      [1] = 0x4cd9a0,
      [2] = 0x4ceb50,
      [3] = 0x4d1c60,
      [4] = 0x4d2fa0,
      [5] = 0x4d3460,
      [6] = 0x4d3760,
      [7] = 0x4d5b60,
      [8] = 0x4d5c20,
      [9] = 0x4d5ce0,
      [10] = 0x4d5da0,
      [11] = 0x4d5f20,
      [12] = 0x4d5fe0,
      [13] = 0x4d61f0
    },
    [0x4d1c60] = std::set with 14 elements = {
      [0] = 0x4cd830,
      [1] = 0x4cd9a0,
      [2] = 0x4ceb50,
      [3] = 0x4d12b0,
      [4] = 0x4d2fa0,
      [5] = 0x4d3460,
      [6] = 0x4d3760,
      [7] = 0x4d5b60,
      [8] = 0x4d5c20,
      [9] = 0x4d5ce0,
      [10] = 0x4d5da0,
      [11] = 0x4d5f20,
      [12] = 0x4d5fe0,
      [13] = 0x4d61f0
    },
    [0x4d2580] = std::set with 7 elements = {
      [0] = 0x4cd830,
      [1] = 0x4d5b60,
      [2] = 0x4d5c20,
      [3] = 0x4d5da0,
      [4] = 0x4d5e60,
      [5] = 0x4d5f20,
      [6] = 0x4d61f0
    },
    [0x4d2fa0] = std::set with 14 elements = {
      [0] = 0x4cd830,
      [1] = 0x4cd9a0,
      [2] = 0x4ceb50,
      [3] = 0x4d12b0,
      [4] = 0x4d1c60,
      [5] = 0x4d3460,
      [6] = 0x4d3760,
      [7] = 0x4d5b60,
      [8] = 0x4d5c20,
      [9] = 0x4d5ce0,
      [10] = 0x4d5da0,
      [11] = 0x4d5f20,
      [12] = 0x4d5fe0,
      [13] = 0x4d61f0
    },
    [0x4d3460] = std::set with 14 elements = {
      [0] = 0x4cd830,
      [1] = 0x4cd9a0,
      [2] = 0x4ceb50,
      [3] = 0x4d12b0,
      [4] = 0x4d1c60,
      [5] = 0x4d2fa0,
      [6] = 0x4d3760,
      [7] = 0x4d5b60,
      [8] = 0x4d5c20,
      [9] = 0x4d5ce0,
      [10] = 0x4d5da0,
      [11] = 0x4d5f20,
      [12] = 0x4d5fe0,
      [13] = 0x4d61f0
    },
    [0x4d36a0] = std::set with 7 elements = {
      [0] = 0x4cd830,
      [1] = 0x4d5b60,
      [2] = 0x4d5c20,
      [3] = 0x4d5da0,
      [4] = 0x4d5e60,
      [5] = 0x4d5f20,
      [6] = 0x4d61f0
    },
    [0x4d3760] = std::set with 14 elements = {
      [0] = 0x4cd830,
      [1] = 0x4cd9a0,
      [2] = 0x4ceb50,
      [3] = 0x4d12b0,
      [4] = 0x4d1c60,
      [5] = 0x4d2fa0,
      [6] = 0x4d3460,
      [7] = 0x4d5b60,
      [8] = 0x4d5c20,
      [9] = 0x4d5ce0,
      [10] = 0x4d5da0,
      [11] = 0x4d5f20,
      [12] = 0x4d5fe0,
      [13] = 0x4d61f0
    },
    [0x4d5b60] = std::set with 17 elements = {
      [0] = 0x4cd830,
      [1] = 0x4cd9a0,
      [2] = 0x4ceb50,
      [3] = 0x4d12b0,
      [4] = 0x4d1c60,
      [5] = 0x4d2580,
      [6] = 0x4d2fa0,
      [7] = 0x4d3460,
      [8] = 0x4d36a0,
      [9] = 0x4d3760,
      [10] = 0x4d5c20,
      [11] = 0x4d5ce0,
      [12] = 0x4d5da0,
      [13] = 0x4d5e60,
      [14] = 0x4d5f20,
      [15] = 0x4d5fe0,
      [16] = 0x4d61f0
    },
    [0x4d5c20] = std::set with 17 elements = {
      [0] = 0x4cd830,
      [1] = 0x4cd9a0,
      [2] = 0x4ceb50,
      [3] = 0x4d12b0,
      [4] = 0x4d1c60,
      [5] = 0x4d2580,
      [6] = 0x4d2fa0,
      [7] = 0x4d3460,
      [8] = 0x4d36a0,
      [9] = 0x4d3760,
      [10] = 0x4d5b60,
      [11] = 0x4d5ce0,
      [12] = 0x4d5da0,
      [13] = 0x4d5e60,
      [14] = 0x4d5f20,
      [15] = 0x4d5fe0,
      [16] = 0x4d61f0
    },
    [0x4d5ce0] = std::set with 14 elements = {
      [0] = 0x4cd830,
      [1] = 0x4cd9a0,
      [2] = 0x4ceb50,
      [3] = 0x4d12b0,
      [4] = 0x4d1c60,
      [5] = 0x4d2fa0,
      [6] = 0x4d3460,
      [7] = 0x4d3760,
      [8] = 0x4d5b60,
      [9] = 0x4d5c20,
      [10] = 0x4d5da0,
      [11] = 0x4d5f20,
      [12] = 0x4d5fe0,
      [13] = 0x4d61f0
    },
    [0x4d5da0] = std::set with 17 elements = {
      [0] = 0x4cd830,
      [1] = 0x4cd9a0,
      [2] = 0x4ceb50,
      [3] = 0x4d12b0,
      [4] = 0x4d1c60,
      [5] = 0x4d2580,
      [6] = 0x4d2fa0,
      [7] = 0x4d3460,
      [8] = 0x4d36a0,
      [9] = 0x4d3760,
      [10] = 0x4d5b60,
      [11] = 0x4d5c20,
      [12] = 0x4d5ce0,
      [13] = 0x4d5e60,
      [14] = 0x4d5f20,
      [15] = 0x4d5fe0,
      [16] = 0x4d61f0
    },
    [0x4d5e60] = std::set with 8 elements = {
      [0] = 0x4cd830,
      [1] = 0x4d2580,
      [2] = 0x4d36a0,
      [3] = 0x4d5b60,
      [4] = 0x4d5c20,
      [5] = 0x4d5da0,
      [6] = 0x4d5f20,
      [7] = 0x4d61f0
    },
    [0x4d5f20] = std::set with 17 elements = {
      [0] = 0x4cd830,
      [1] = 0x4cd9a0,
      [2] = 0x4ceb50,
      [3] = 0x4d12b0,
      [4] = 0x4d1c60,
      [5] = 0x4d2580,
      [6] = 0x4d2fa0,
      [7] = 0x4d3460,
      [8] = 0x4d36a0,
      [9] = 0x4d3760,
      [10] = 0x4d5b60,
      [11] = 0x4d5c20,
      [12] = 0x4d5ce0,
      [13] = 0x4d5da0,
      [14] = 0x4d5e60,
      [15] = 0x4d5fe0,
      [16] = 0x4d61f0
    },
    [0x4d5fe0] = std::set with 14 elements = {
      [0] = 0x4cd830,
      [1] = 0x4cd9a0,
      [2] = 0x4ceb50,
      [3] = 0x4d12b0,
      [4] = 0x4d1c60,
      [5] = 0x4d2fa0,
      [6] = 0x4d3460,
      [7] = 0x4d3760,
      [8] = 0x4d5b60,
      [9] = 0x4d5c20,
      [10] = 0x4d5ce0,
      [11] = 0x4d5da0,
      [12] = 0x4d5f20,
      [13] = 0x4d61f0
    },
    [0x4d61f0] = std::set with 17 elements = {
      [0] = 0x4cd830,
      [1] = 0x4cd9a0,
      [2] = 0x4ceb50,
      [3] = 0x4d12b0,
      [4] = 0x4d1c60,
      [5] = 0x4d2580,
      [6] = 0x4d2fa0,
      [7] = 0x4d3460,
      [8] = 0x4d36a0,
      [9] = 0x4d3760,
      [10] = 0x4d5b60,
      [11] = 0x4d5c20,
      [12] = 0x4d5ce0,
      [13] = 0x4d5da0,
      [14] = 0x4d5e60,
      [15] = 0x4d5f20,
      [16] = 0x4d5fe0
    }
  },
  nodes = std::map with 18 elements = {
    [0x4ccd40] = 0x4d36a0,
    [0x4ccf10] = 0x4cd9a0,
    [0x4cd500] = 0x4d1c60,
    [0x4ce190] = 0x4d3460,
    [0x4ce2a0] = 0x4d3760,
    [0x4cf440] = 0x4d5b60,
    [0x4cfc90] = 0x4d5c20,
    [0x4d0010] = 0x4d5ce0,
    [0x4d0240] = 0x4d5da0,
    [0x4d18d0] = 0x4d5e60,
    [0x4d2bd0] = 0x4d5f20,
    [0x4d2d90] = 0x4d5fe0,
    [0x4d32f0] = 0x4d2580,
    [0x4d64b0] = 0x4ceb50,
    [0x4d6500] = 0x4d2fa0,
    [0x4d65a0] = 0x4d61f0,
    [0x4d65f0] = 0x4d12b0,
    [0x4d6640] = 0x4cd830
  },
  spilled_vars = std::set with 0 elements
}


### 2/16
Something that is likely causing the majority of our error is how we wrote *spillForL2*, apparently rsp is **not** supposed to make it into the interference graphs liveness etc. Currently we are manually creating an 'rsp' variable instance in *spillForL2*, which then makes it into the liveness and interference graphs upon the next try at coloring. This is not expected behavior. We have a more specific problem in test849:
* the first pass of graph coloring goes as expected. There are 16 nodes (15 gp registers and 1 variable), and *my_var_1* has edges with everything, so it must be spilled. The graph color function returns this node in its nodes_to_spill vector output, and *spillForL2* gets called on this singular node/variable.
* This newly constructed graph still contains 16 nodes as expected (since should still have 15 gp registers, a spill variable 'S-1', and the absence of variable 'my_var_1' since it was spilled.) However, all 16 are Register types, with 'rsp' taking the spot of 'S-1' which doesn't appear in the graph anywhere.
* The actual error we receive from this is a segfault in the depopulate / get_node_order function. This happens because we call *getVarNodes()* (which returns a vector of all the non Register type nodes from the graph) then call *back()* on its output, which is invalid since the output is a vector of length zero. 
* So the immediate question is even if the rsp node makes it into interference graph, why does the new spill variable not have node there??
* Our next step should be to quickly cook up a print program visitor so that we can see the state of the program after spilling.

* calling liveness on a normal function will not put rsp in the in/out sets of an instruction. However calling liveness on a function after spilling results in rsp being in the in/out sets and potentially the gen/kill sets.
  * there must be some behavior in spillForL2 causing this which i don't understand
  * spill still passes its test cases though, this is just a side effect

### 2/21/24
Currently failing the following, due to graph coloring:
* 838
* 837
* 275

Segfaults, *best_node* is a null pointer, so the condition makes us grab from *curr_nodes*, an empty set. 
* on the first iteration of coloring, we should only have to spill one of the three variables.
  * %v1 and %v2 connect with every register except for rcx - we would expect the first of these two in node stack to get colored with 'rcx' and then spill the other.
  * %v3 only connects with about 7 registers, so plenty to pick from. However the worst case would be if this node is the first in node stack and the alg colors it with 'rcx' - this means that we would need to spill both %v1 and %v2 since they both connect with %v1 
  
* after the first call to depopulate in the first call to color_graph, variable %v3 is the first to get removed from the graph since it has degree 9 (less than 15). However, after the call to removeNode we see that:
  * The size field of the graph has decreased from 18 to 17.
  * The nodes map has decreased from size 18 to 17.
  * The graph map has decreased from size 18 to 17.
  * **However, %v3 still appears in the neighbor sets of its previous neighbors!**
    * this means that there is a problem with the function *removeNode*.
  * **BRUH** i think its because we don't iterate by reference in the remove node function, after calling 'pair.second.erase(node)' the set pair.second goes from size 17 to 16 but the graph itself's size stays at 17. 
    * However the node degrees do get updated correctly it seems?

  * So the removeNodes function looks fine now, and the segfault seems to be happening on the second iteration of the graph coloring algorithm
    * we have already spilled a variable since %S0 shows up in the graph. At the time of the segfault, none of the other variables are showing up in the printed graph, which has size 16. It should follow that there is still 1 non-register node in the graph - however, currNodes is already empty (which stores the non-register nodes we are iterating from and trying to remove from the graph). This is backed up further by the fact that getSize() returns 1, meaning the while loop still had one more iteration to go.
      * i think that this issue is coming partially from the function getVarNodes, and mostly from how spill variables like %S0 are stored in the graph. For example, this variable should be included in the vector returned by getVarNodes, however it doesn't seem like this is happening (verify this on next run through). %S0 should definitely be able to be removed from the graph, since we still need to color it with a register in order to progress.
* wait but color_graph outputs an empty vector as uncolored_nodes so why are we even performing another iteration of the graph coloring?
  * also this doesn't seem right, both %v1 and %v2 interfere with every other register.
  * also at the end of this first iteration, *interference_graph* has size 15 which does not seem right. We should only be modifying *interference_graph_copy*, so i would think the original would still be in its initial state with size 18? like the graph and nodes fields only have 15 elements as well for *interference_graph*.
    * bruh *interference_graph_copy* also only has 15 (the variables are missing it seems). Why didn't the repopulate function add everything back into the graph?
  * **So we have two problems: the state of the original interference graph is getting affected somehow, and none of the inteference graphs are getting correctly repopulated with the removed variable nodes.**
    * note that printGraph, printColors, and printNodeDegrees all verified the missing variable nodes.
  * Also, the three variables v1-3 are all missing from the function's
  * **BRUH** i was overreacting on this bullet point, we were on the stub function. The original issue is still relevant.

  * okay after the first iteration of color_graph on the real function (ie not stub) we have to spill the node corresponding with the %v2 variable. This is stored in vector *uncolored_nodes* and i believe its pointer 0x4f00c0 is different from the pointer to this node in *interference_graph*. However it shows up in *interference_graph_copy* which is expected behavior, since this is a clone in memory of the original.

  * okay after spilling %v2, whenever color_registers is called none of the registers in the graph get colored. This is weird 

  * okay after this apparently %v1 gets spilled which i didn't realize.

  * we spill once (v1 and v3 left over), twice (v3 left over)

#### infinite loop in test805.L2
* 

#### failing test849 segfaults
* The L1 program segfaults because i don't think it allocates a byte in the function arguments for stack accesses.
  * i confirmed this by running simone's compiler on a version that did have the byte allocation.
* I think the spillForL2 function should be incrementing the 'locals' field in the new function it outputs, currently it just seems like it is zero all the time.

### NOTE
"if (node_name[0]=='%' && node_name[1]=='S')" this case should be find, since a variable must be at least two chars long

### test 805

why is it that after the first spill, 'fptr' (which gets passed in to spillForL2) gets altered with spill varaibles? This seems wrong, all changes should be made in the newFunction and the old one should be left untouched. 

Also, the output of the first spill newFunction is incorrect:

rdi <- 7
rsi <- 1
call allocate 2
%firstRow <- rax
r9 <- mem 8 %firstRow
r9 += 2
mem %firstRow 8 <- r9
rdi <- 7
rsi <- 1
call allocate 2
%S0 <- rax
mem rsp 0 <- %S0
r9 <- mem 16 %S1    // %S1 is used without first being defined
mem rsp 0 <- %S1    // %S1 is used again, still not defined yet
r9 += 2
mem %S2 16 <- r9    // %S2 is used without being defined
rdi <- 7
rsi <- 1
call allocate 2
%thirdRow <- rax
r9 <- mem 24 %thirdRow
r9 += 2
mem %thirdRow 24 <- r9
rdi <- 7
rsi <- 1
call allocate 2
rdi <- rax
mem rdi 8 <- %firstRow
%S2 <- mem 0 rsp    // why is the first time %S2 gets defined all the way down here
mem rdi 16 <- %S2
mem rdi 24 <- %thirdRow
call print 1
return



### 2/23/24
* %v4Encoded <- %v4Encoded      what should the instructions be if we need to spill %v4Enconded?

%S1% is the first to go and it is making it into the if (g->spill_vars.find(node->var) == g->spill_vars.end()) condition (bad)
  - this is because the variable is not being found in the graph's spill_vars set.


  :call_label_ciao__ciao__ciao_6
goto :call_label_ciao__ciao__ciao_13
:call_label_ciao__ciao__ciao_7
return
:call_label_ciao__ciao__ciao_8
%newVar1 <- %i
%newVar1 *= 8
%newVar0 <- %newVar1
%newVar0 += 8
%newVar2 <- %cGs
%newVar2 += %newVar0
%cG <- mem %newVar2 0
%newVar4 <- 0
%newVar4 *= 8
%newVar3 <- %newVar4
%newVar3 += 8
%newVar5 <- %cG
%newVar5 += %newVar3
%g <- mem %newVar5 0
rdi <- %cG
rsi <- %X
mem rsp -8 <- :call_label_ciao__ciao__ciao_14
call %g 2
:call_label_ciao__ciao__ciao_14
%cH <- rax
%newVar7 <- 0
%newVar7 *= 8
%newVar6 <- %newVar7
%newVar6 += 8
%newVar8 <- %cH
%newVar8 += %newVar6
%h <- mem %newVar8 0
rdi <- %cH
rsi <- %Y
mem rsp -8 <- :call_label_ciao__ciao__ciao_15
call %h 2
:call_label_ciao__ciao__ciao_15
%ans <- rax
%num <- %ans
%num *= 2
%num <- %num
%num += 1
rdi <- %num
call print 1
%i <- %i
%i += 1
%fin <- 3 < %i
cjump 1 = %fin :call_label_ciao__ciao__ciao_8
goto :call_label_ciao__ciao__ciao_7
:call_label_ciao__ciao__ciao_9
%i <- 0
goto :call_label_ciao__ciao__ciao_8
:call_label_ciao__ciao__ciao_10
%newVar10 <- %i
%newVar10 *= 8
%newVar9 <- %newVar10
%newVar9 += 8
%newVar11 <- %ops
%newVar11 += %newVar9
%f <- mem %newVar11 0
rdi <- 3
rsi <- 1
call allocate 2
%cF <- rax
%newVar13 <- 0
%newVar13 *= 8
%newVar12 <- %newVar13
%newVar12 += 8
%newVar14 <- %cF
%newVar14 += %newVar12
mem %newVar14 0 <- %f
rdi <- %cF
mem rsp -8 <- :call_label_ciao__ciao__ciao_16
call @curry 1
:call_label_ciao__ciao__ciao_16
%cG <- rax
%newVar16 <- %i
%newVar16 *= 8
%newVar15 <- %newVar16
%newVar15 += 8
%newVar17 <- %cGs
%newVar17 += %newVar15
mem %newVar17 0 <- %cG
%i <- %i
%i += 1
%fin <- 3 < %i
cjump 1 = %fin :call_label_ciao__ciao__ciao_10
goto :call_label_ciao__ciao__ciao_9
:call_label_ciao__ciao__ciao_11
rdi <- 7
rsi <- 1
call allocate 2
%cGs <- rax
%i <- 0
goto :call_label_ciao__ciao__ciao_10
:call_label_ciao__ciao__ciao_12
%newVar19 <- %i
%newVar19 *= 8
%newVar18 <- %newVar19
%newVar18 += 8
%newVar20 <- %ops
%newVar20 += %newVar18
%f <- mem %newVar20 0
rdi <- %ops
rsi <- %X
rdx <- %Y
mem rsp -8 <- :call_label_ciao__ciao__ciao_17
call %f 3
:call_label_ciao__ciao__ciao_17
%ans <- rax
%num <- %ans
%num *= 2
%num <- %num
%num += 1
rdi <- %num
call print 1
%i <- %i
%i += 1
%fin <- 3 < %i
cjump 1 = %fin :call_label_ciao__ciao__ciao_12
goto :call_label_ciao__ciao__ciao_11
:call_label_ciao__ciao__ciao_13
rdi <- 7
rsi <- 1
call allocate 2
%ops <- rax
%plus <- @plus
%minus <- @minus
%times <- @times
%newVar22 <- 0
%newVar22 *= 8
%newVar21 <- %newVar22
%newVar21 += 8
%newVar23 <- %ops
%newVar23 += %newVar21
mem %newVar23 0 <- %plus
%newVar25 <- 1
%newVar25 *= 8
%newVar24 <- %newVar25
%newVar24 += 8
%newVar26 <- %ops
%newVar26 += %newVar24
mem %newVar26 0 <- %minus
%newVar28 <- 2
%newVar28 *= 8
%newVar27 <- %newVar28
%newVar27 += 8
%newVar29 <- %ops
%newVar29 += %newVar27
mem %newVar29 0 <- %times
%X <- 7
%Y <- 2
%i <- 0
goto :call_label_ciao__ciao__ciao_12


* The interference graph contains duplicate registers which does not seem right. There are tons and tons of r10s for example.
* The code then segfaults when it gets to the code generation step, very likely because of these duplicates. 
* wait wtf his liveness also seems incorrect and has duplicates, like %newVar27
  * **NVM** i was confusing liveness and interference graph
* okay so we have the same liveness
* we also have the same interference.
  * these are both from the initial function, we are likely experiencing problems specifically with the spill.


test 534 seems like an L1 compiler problem womp
The prog.L1 file generated by our L2 compiler, when compiled with simone's L1 compiler, produces the output 

9
5
14
9
5
14

which matches the test534.L2.out file exactly. This means that the L2 code we generate is valid, but not the L1. The prog.S file generated by our L1 compiler causes the following assembler errors:

prog.S: Assembler messages:
prog.S:284: Error: too many memory references for `movq'
prog.S:323: Error: too many memory references for `movq'

For reference here are lines:
* movq _curry_arg1, 0(%r11)
* movq _curry_arg2, 0(%r8)

test406 also produces a similar assembler error:

prog.S: Assembler messages:
prog.S:274: Error: too many memory references for `movq'
prog.S:311: Error: too many memory references for `movq'

For reference these lines are:
* movq _curry_arg1, 0(%r10)
* movq _curry_arg2, 0(%r8)
  * The corresponding line in the L1 prog is *mem r8 0 <- @curry_arg2*
Need to look at the Memory_assignment_store code generator in L1 to figure this out.

### after codegen
Now failing test769.L2 test683.L2 test764.L2 test766.L2 test588.L2 test166.L2 test729.L2 test285.L2 test478.L2, which i think are completely different tests from before.

these tests seem to pass after removing the print statements
* 683, 764, 766, 
these tests segfault during a.out execution
* 769
* 588
  * "Cannot access memory at address 0x3c"
  * From the prog.S:
_main:
subq $96, %rsp
_call_label0:
jmp _call_label1
_call_label1:
movq $10, %r10
movq %r10, 408(%rsp)
movq 408(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
salq $1, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
addq $1, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %rdi
movq $2, %rsi
  * does this mean we are subtracting 96 bytes from the stack? why is there an offset of 408 this seems to high for 96
  * all the movqs seem unnecessary?

### test769.L2
Both ours and simone's L1 compiler produce an a.out executable which prints:
```python
26910000
26910000
3074457339547744436
Segmentation fault
```