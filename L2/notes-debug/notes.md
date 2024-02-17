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