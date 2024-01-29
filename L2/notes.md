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