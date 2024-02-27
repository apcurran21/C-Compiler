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
        * var << t2
    * ">>"
        * var <- t1
        * var >> t2

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

