# office hour notes

must do globalization of labels, just follow whats in the slides
* follow the definition of context in the slides
    * for everything that isn't part of the context, don't add a tree.
    * a call instruction is in a context by itself for example.

each instruction gets their own context

Algorithm frrom the slides:

bottom up code generate the L2 instructions from the leaves of the trees to the roots.

First identify all context.
Then for every instruction in ever context build a tree, creating a sequence of trees in each context.

Then for each tree in a context, tile it independently of other trees in the same context.

Note that contexts are primarily used in the merging trees step - but we still need it.

Need to have a memory representation that constantly/consistently covers the trees.

How we store the mapping of trees and tiles is a design decision, up to us. 

Would it make sense to store a tile field in the tree to associate the tile with the tree. How do we know what a tree is tiled as, and how much of it is covered?
* You can encode this info explicitly into the tree data structure
* Can do it implicitly by deleting a portion of the tree once it's been tiled, or just replacing that section of the tree with a tile. 
    * In simone's code ,a tile is a stateful tile. A tile "eats" a tree and results in a tile with the tree inside of tile. 

the naive solution (which we don't want to do) would be to just do a one to one mapping of L3 to L2 instructions

Implementing the maximal munch algorithm:
* Note that for H3 we are always running max munch on a small individual tree, but it sets us up for large trees that are created by merging (H4)
    * so we still need to implement it!

Tiling process:
* First implement the minimum set of tiles needed to cover/match any tree
    * these tiles are enough to pass H3
    * the tiling could be "naive", but in order to get credit we need to implement all other algorithms
    * think of tiles as the "input" to the algorithm, and the "engine" can take any set of tiles.
        * The output of the compiler will match the Naive solution if we use these basic one to one tiles.
        * H3 is seeing if we can implement the engine which is the tiling algorithm.

Do one to one tiling then implement everything else fully!

How do we know if max munch is correct?
* Statistically our max munch alg will be correct, but the bugs won't be triggered in H3. This is why H4 is so difficult, since it will expose all the bugs in our H3 code and previously with the tiling. 

Need to spend time thinking about how to represent a tile and implement max munch to get a similar difficulty as H2. 
* It will be very worth it to design this well.

implement the code with the following mindset:
* if tomorrow someone wants to implement a new set of tiles, they should not have to edit any of our current code (tiles are the inputs of the algorithms!)

make sure max munch is recursive to get the credit hehe otherwise don't worry about full correctness

is it worth it to use pegtl for the tile matching?
* it will work, but it will take more code

Our matching algorithm is literally maximal munch:
* start from the root of the tree, then go through the list of tiles and check if any can eat the root. If any answer yes, then keep. Then choose the tile which can then eat the largest part of the tree. 
* max munch is a greedy recursive algorithm
* how we match the patterns is up to us - the tile is a pattern
    * "the center has to be a multiplication, the right child has to be a number" are all example characteristics of the tree that a tile will match to

There is no shortcut for the three steps of H3. 


Naive implement H3, skip H4, then do 5, 6, 7, submit for the competition, then submit H3 if we have the time (if we feel fully comfortable with what parsing is involving, then maybe do H8 before H3 even), then do H9


a shortcut on the memory representation will come back to bite us


Naive solution for H3 is to just go L3 string to L2 string

DEADLINE FOR COMPETITON IS NEXT WEDNESDAY AT 2PM