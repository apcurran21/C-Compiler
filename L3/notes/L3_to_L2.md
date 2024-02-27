# Translating L3 to L2 directly:

#### L3 assignment
* var <- s
* L2: var <- s

#### L3 operation assignment
* var <- t1 op t2
    * op has { + , - , * , & , << , >> }
* L2: dependent on op:
    * "+"
        * var <- t1
        * var += t2
    * "-"
        * var <- t1
        * var -= t2
    * "*"
        * var <- t1
        * var *= t2
    * "&"
        * var <- t1
        * var &= t2
    * "<<"
        * var <- t1
        * var <<= t2
    * ">>"
        * var <- t1
        * var >>= t2

#### L3 comparison assignment
* var <- t1 cmp t2
    * cmp has { < , <= , = , >= , > }
* L2: dependent on op:
    * "<"
        * var <- t1 < t2
    * "<="
        * var <- t1 <= t2
    * "="
        * var <- t1 = t2
    * ">="
        * var <- t2 < t1
    * ">"
        * var <- t2 <= t1

#### L3 memory load
* var1 <- load var2
    * this is kind of tough, depends on what was stored into var2.
    * note: we should keep a map of variable names to their types and values as we parse so that we know which instructions to generate.
    * var <- s can result in a variable, number, label or function name being stored in var.
    * actually i think its just fine to simply pass on var2 to the L2 load, the real trouble will be finding which M to get from? In L2 we have to specify the offset
        * should this M always be 0?
        * just try this for now
* L2: var1 <- mem var2 0

#### L3 memory store
* store var <- s
    * L3 s can be a var, N, t, label, or I 
        * the L3 s is a subset of the L2 s, so we are good to just transfer over (also with a memory offset of M=0)?
* L2: mem var 0 <- s

#### L3 return
* return
    * very ez
* L2: return

#### L3 return a value
* return t
    * L3 t can be a var or N, basically the same as in L2.
* L2: need to save into output registsern register.
    * rax <- t
    * return

#### L3 label
* label
    * L3 labels are local, while L2 labels are global. So we need to do label globalization before creating the L2 translation.
* L2: label

#### L3 branch to label
* br label
* L2: 
    * cjump 0 = 0 label

#### L3 conditional branch to label
* br t label
    * I think this is just branching if t is nonzero (ie false:zero, true:nonzero)
* L2:
    cjump 0 < t label

#### L3 call function
* call callee ( args )
    * We need to explicitly store the return label for the function on the stack, place any necessary arguments onto the stack, make the function call, and place the return label after the call.
        * The first 6 arguments of a function are stored in registers, so any more get put on stack.
        * We should think about how to globalize these new return labels, since they are not included in the original L3 program.
* L2:
    * mem rsp -8 <- :return_label
    * L2: for each parameter 1 through 6 ...
        * 1: rdi <- arg1
        * 2: rsi <- arg2
        * 3: rdx <- arg3
        * 4: rcx <- arg4
        * 5: r8 <- arg5
        * 6: r9 <- arg6
    * L2: for each parameter 7 though N ...
        * 7: mem rsp -16 <- arg7
        * N: mem rsp -8-8(N-6)
    * call callee N
    * :return_label

#### L3 call function assignment
* var <- call callee ( args )
    * same as before, except we also need to extract the function's return value from rax.
* L2:
    * mem rsp -8 <- :return_label
    * L2: for each parameter 1 through 6 ...
        * 1: rdi <- arg1
        * 2: rsi <- arg2
        * 3: rdx <- arg3
        * 4: rcx <- arg4
        * 5: r8 <- arg5
        * 6: r9 <- arg6
    * L2: for each parameter 7 though N ...
        * 7: mem rsp -16 <- arg7
        * N: mem rsp -8-8(N-6) <- argN
    * call callee N
    * :return_label
    * var <- rax

#### L3 function definition
* define I ( vars ) { i+ }
    * if the number of parameters N is greater than 6, then we need to store onto the stack
* L2:
    * ( I
    *   N
    * L2: for each parameter 1 through 6 ...
        * 1: var1 <- rdi
        * 2: var2 <- rsi
        * 3: var3 <- rdx
        * 4: var4 <- rcx
        * 5: var5 <- r8
        * 6: var6 <- r9
    * L2: for each parameter 7 through N ...
        * 7: var7 <- stack-arg 8(N-7)
        * N: varN <- stack-arg 0
    *   Instructions ...
    * )
* **Note:** We can write the define phrase and function name to the outfile as soon as we recognize a defined_function_name rule, and can write the list of parameters as soon as we recognize a params_rule. What follows is a series of instructions matched by rules, all of which write to the file. This means that the actual action template for the function_definition rule can just close it off by writing a closing paren.