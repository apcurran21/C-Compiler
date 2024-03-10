# LA Notes

### Basic Blocks
* In order to create basic blocks from our LA program, we only need to have the ability to add new labels and goto (unconditional branch) instructions.
    * We have to inject them into the vector of instructions that we are tracking.
* We could have a boolean field and getter method in the base Instruction class that derived instructions can override so that they can answer if they are terminators or not.
    * We might also need to do something similar so that label instructions can disclose their labelness when queried.
    * all this info needs to be known for the basic block creation algo.


### Memory checks
What I could do is create a check single index function, which only checks the memory access at a single index. It would need to take an **int** signifiying the index of the array object to check on, and a **bool** indicating whether or not the array object is a tuple or int64 tensor. There would be a lot of repeated code between the two cases, so having this bool would help us change the one or two instructions that differentiate them.

If an array is not a tuple, we will indicate a one dimensioned tensor in the check index function as having a passed in dimension index equal to -1 (ie we have to use the tensor-error call with three args.) Otherwise, we know it's a multidimensional tensor and we need to use the tensor-error call with 4 args.

how we create the condition check is very odd for defining when we have a 1D tensor.