# L3 Compiler
Outline the structure of our L3 compiler.

## Requirements
Our compiler needs to implement the following features:
1. Label globalization
    * The scope of L3 labels is the function, but L2 labels are global. This means we need to prepend L3 labels with some strings that will make them globally unique in the corresponding L2 program.
2. Instruction selection
    * At a high level, individual L3 instructions can be repesented as trees. We choose the best way to "tile" these trees completely in order to produce the corresponding L2 instructions.  
3. L2 calling conventions
    * L3 hides the calling convention for custom and std library functions, so we need to make this explicit when we generate the L2 code. This applies to both caller and callee:
        * **Caller** - say we have the L3 function call *%v1 <- call @myF(3)* :
            * In L2, we need to save the return label onto the stack, save all the arguments into registers and onto the stack if necessary, call the function with the correct argument number, place the return label after this function call, and place the return value from rax into the variable destination. The function call in L2 should be generated as:
            ```python
            (@main
             0
             mem rsp -8 <- :myF_ret
             rdi <- 3
             call @myF 1
             :myF_ret
             %v1 <- rax
            )
            ```
        * **Callee** - say we have the following function definition:
            ```python
            define @myF (%p1) {
                return %p1
            }
            ```
            * In L2, we need to specify the number of arguments this function takes, place the arguments from registers and potentially the stack into the corresponding variables specified in the L3 function signature, place the value of the variable contained in the L3 return instruction into rax, and make an L2 return call. The function in L2 should be generated as:
            ```python
            (@myF
             1
             %p1 <- rdi
             rax <- %p1
             return
            )
            ```

## General Structure
The L3 compiler should do the following:
```
For every L3 function f do
    Globalize labels.
    Select L2 instructions based on the L3 instructions in f.
    Implement L2 calling convention.
```


## L3 Program Memory Representation
We'll be able to reuse the majority of our L2 memory representation. For example, we'll keep the *Program*, *Function*, and *Item* classes. However, we can cut down on the number of derived classes we create from *Item* - for example, L3 grammar doesn't allow the programmer to use specific general purpose registers. 

### Item
Interface for things like variables and numbers.
#### Methods
* *print*
    * This function will return the actual value of an Item instance as a string. This will be necessary for code generation and the *printFunction* / *printProgram* debug printers. 
#### Derived Classes
* Variable
* Number
* Label
* Name

### Instruction
Interface for the various L3 instructions.
#### Methods

#### Derived Classes
*


## Todos
1. Write a printFunction visitor, and a printProgram function based around this. We've often run into parsing issues in the past, being able to quickly verify our memory representation's correctness at the start will speed us up.
2. Decide which derived classes are actually necessary for the Item class. For instance, do we still need a distinction between labels and function names?
3. Implement the constructors for all the data types for L3.
4. Think about whether or not we need to make a distinction between labels, function names, and variables in the memory representation.
    * Actually we will probably keep the base *Name* class for these three, and then just implement the derived classes so that we can assign specific methods for them etc.