# Notes on the IR Parser

### Questions
* What is the actual entry point rule for an IR program?
    * Ie is it a collection of 1 or more functions, where each function is a collection of one or more basic blocks?
    * 

### Parsing

Plan is to have all places onto parsed_items occur in the basic terminal rules, like label and var rules. In the case of t_rules and function arguments array accesses etc, t_rule will have no action, but arg_rule will be defined to take a t_rule (by probably doing seq<t_rule>). Then the corresponding action for arg rule is to grab and pop off the back of parsed items and place onto a parsed args stack. Then once we recognize an args rule or an array load/store rule, we know parsed_args contains all of the arugment t_rule types.

We'll do something similar for function names, so that when we recognize one we can grab and pop the name instance off the parsed_items stack and create a new functions instance based on the name. 
* it might be a little tricky distinguishing between a defined function name rule and a callee, but we'll see.
* also when we recognize a defined function name, after removing it from the parsed_items stack it should be the case that its corresponding type is the next item on top of the stack so we should grab that somehow. 

I think we can switch up the args_rule, since it is only used in a function call instruction. That means whenever we recognize this instruction, all the args will be at the back of the parsed items stack. However this might be weird since we will still have the callee there.
* maybe we can do something like creating a new instruction as soon as we see the call or callee type, thus removing the 
* we could create a call and var <- call rules/actions to capture and distinguish between two types of function calls early on, we could create the corresponding instruction instance and place onto the current function's instruction stack, popping off the necessary number of items from the parsed_items stack (will be either one or two).
    * then the parser continues to place t_rule instances onto the empty stack - once either call instruction is realized, all the items on the parsed_items stack are arguments!
    * note that this style of approach wouldn't necessarily work for every instruction that uses a set of args.

A feature of the language is that a variable must be declared with its type before ever being used. So this means we can keep a dictionary mapping variable names to their corresponding types, so that when we encounter that variable name during the parsing we can handle it correctly (eg by creating the correct instruction).

Bruhh i can just access from the front of the vector too. 
* eg if I recognize a load instruction, I know the first two elements in the vector will be the var <- var, and after getting rid of those all others will be args.

### Types
when defining the types, do we need to track the number of dimensions an int64 array is ? or is it sufficient for this to only be tracked in the corresponding instruction that uses it?
* I'm thinking that this might not work.

It would not be too hard to store the dimensions of an int64, we could just create an action to add the empty brackets to the parsed_items stack then count parsed_items size to get the dimension.
* But what would the benefit of this be? Like if this info is absolutely necessary how would we use it later on in the program?

#### Note about type vs T_rule
since they are so similar, we are going to assume the correctness of the IR program and just place type and T_rule under the same type_rule
* we are also gonna make a terminal type_keyword rule so that this action will place the keywords onto the parsed_items stack, and then whenever we recognize a type_rule we will have both the keywords and any brackets on the stack.
    * we are highly simplifying these rules so make sure the program is correct (ie errors won't be caught in the parser).

### Monday
I think i just need to fully commit to ignoring the basic blocks in the parser, and only creating a list of instructions. it's repeated work, but that code is already written to create basic blocks from a vector of instructions.

