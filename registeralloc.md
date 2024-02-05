# Notes / Design Doc

Finished the liveness analysis part of register allocation, still need to handle the interference graph, spilling, and graph coloring

## Interference Graph


## Spilling


## Graph Coloring

Still finalizing our graph implementation, but here is a recap from lecture.

* The graph coloring stage takes the current interference graph as input, and outputs an updated interference graph where each node is colored (ie the *color* field is assigned a register)

Coloring process:
1. Make a copy of the input graph, in case we have trouble coloring it. If we can't color all variables, and can't spill them either (ie if only our new spill variables remain in the graph), then we just spill every single variable in this initial copy of the graph.
2. Color each general-purpose register node in the graph with its own 'color'. Ie, the *color* field of register node r11 gets assigned the enum r11.
3. Repeatedly select and remove a node from the graph until it is empty, placing them on top of a stack.
    1. We can just use a vector of node pointers as a our stack.
    2. We remove all the nodes with a number of edges less than the number of colors, in order of decreasing degree.
        1. In L1, there are 15 general purpose registers, so we first remove all the nodes with strictly less than 15 edges.
        2. We would want to first remove the nodes with 14 edges, then those with 13, etc.
        3. Note that after each removal, it would be best to recalculate the number of edges each node has (this improves the quality of the register allocator). However, I don't think this is absolutely necessary.
    3. Once the only remaining nodes have >= 15 edges, we remove them in order of decreasing degree again (ie if there aren't any with 14 or less, take the one with the most edges out first.)
4. Rebuild the graph by popping off the next node from the stack and assigning it a color.
    1. We keep a list of colors, sorted so that the caller-save registers appear first and the rest follow. 
    2. For each node, choose the first register from the sorted list that is not the color for any of the node's neighbors.
        1. We can do some set logic stuff on this im sure. We probably don't even need to use an explicit set object to hold the 15 colors/registers, since all the *algorithms* set methods work on containers like vectors I believe. 
    3. If a node isn't able to be colored by any of the 15 registers, then we mark it as being uncolored (although i think we still place it back in the graph?). We should also keep track of the uncolored nodes in some other vector, so that it's easy to check if the algorithm failed and handle accordingly. 
5. If there are any nodes in our uncolored vector (meaning that the algorithm failed to allocate all variables to registers), then we can simply spill all of these nodes in one go. 
    1. We could choose other heuristics (like choosing only one variable to spill at a time) but this should work well.
    2. Important !! We need to keep track of the variables that were created by previous spillings, so that we don't accidentally spill these variables and create an infinite loop.




Implementation notes
* We should use some sort of RegisterID enum to fill the *color* field of each node. 
* We need to be able to make copies of our graph, it would be best to implement a *copy_graph* method early on
* Each node should track its number of edges in a *degree* field, so that 

## Code Generation
* By coloring nodes with register enums, then we can have a nice code generation helper (just a big switch statement) that can replace L2 variables with their assigned registers.
