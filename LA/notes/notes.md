# LA Notes

### Basic Blocks
* In order to create basic blocks from our LA program, we only need to have the ability to add new labels and goto (unconditional branch) instructions.
    * We have to inject them into the vector of instructions that we are tracking.
* We could have a boolean field and getter method in the base Instruction class that derived instructions can override so that they can answer if they are terminators or not.
    * We might also need to do something similar so that label instructions can disclose their labelness when queried.
    * all this info needs to be known for the basic block creation algo.