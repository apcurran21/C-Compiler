# L2, Liveness Analysis, etc.

## Questions

## Notes
Overall, we need to make sure that the parser is consistent somehow with the singleton approach to variables that is used in liveness analysis. Worst case, we just do string compare in the liveness analysis.

### Variable allocation structure
* We define a VariableAllocator class in *L2.h*, which has the following:
    * private *allocated_vars* attribute (unordered map of strings to *Variable* pointers).
    * public *allocate()* method that takes a string (name of the variable to be allocated), checks in the *allocated_vars* map to see if a variable with this string already exists. If it does, then it just returns the associated pointer to the user. Otherwise it allocates a new variable instance to the heap using *new* and then returns this pointer to the user, making sure to update the map with this new entry.
    * public *is_defined()* method that takes a variable name, then returns whether or not a variable with this name exists in the map. This will probably only be use in debugging.
* How many instances of this allocator class will exist? Since varaibles have local scope in L2, it might make sense for each function to get its own allocator instance. Is it best for variables with the same name, but encountered/allocated in different functions, to have different instances and therefore pointers?