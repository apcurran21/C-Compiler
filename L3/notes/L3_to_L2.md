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
        * I: vari <- stack-arg 8((N-1)-i) for i in {0, ... N-1}
        * N: varN <- stack-arg 0
    *   Instructions ...
    * )
* **Note:** We can write the define phrase and function name to the outfile as soon as we recognize a defined_function_name rule, and can write the list of parameters as soon as we recognize a params_rule. What follows is a series of instructions matched by rules, all of which write to the file. This means that the actual action template for the function_definition rule can just close it off by writing a closing paren.

## Notes
* Need to consider cases where we are defining a variable using that variable, such as:
```python
%v <- 2
%v <- 1 - %v
```

* presently our code produces an output like this, which is incorrect:
```python
%v <- 2
%v <- 1
%v -= %v
```

* the correct way is this:
```python
%v <- 2
%cucu <- 1
%cucu -=%v
%v <- %cucu
```

* we need to introduce stand-in / intermediary variables so that the calculations are still valid
    * are there any other instructions where we need to do this? this will affect our encoding scheme
        * maybe we can just use the same scheme we use for the label globalization
        * also i think we only need to use a temp variable whenever the defined variable is also the righthand operand. **Note** - I think this only matters for operations that aren't commutative (ie we only need to add a case for addition.)
    * **-, <<, >>** are noncommutative operations

#### Other errors
* so basically the labels still need to be consistent at the function level, so we can't just add to the return counter each time. We can track a fnameCounter, and compare it with the size of parsed fnames. If parsed_fnames.size() is ever larger than fnameCounter, then we know we are in a new function and therefore need to increment on the returnCounter for labels.
    * this means we also need to adjust the return label code, since it increments returnCounter

    * have two separate counters, one for return labels and one for other labels
        * since L3 labels are unique to the function scope, we only need to increment the function counter whenever fname counter is less than parsed_fnames.
        * i believe we still need to increment the return counter each time since those are not unique within the function.
        * switch the temporary variables to also use the functionCounter
    * wait actually we don't need functionCounter and fnameCounter, just one of the two.
    * noo all the actual labels need to be unique, it's just that whenever labels are used in instructions other than Instruction_label, they are getting a new counter value so they don't match with the original declaration of the label in the program.
        * i think the map of maps solution would be best - so the first time a label gets referenced (either in an instruction or as an actual program label), it gets put as a key into the dictionary with its corrsponding value as the globalized version. So every time we see a label in the program, we need to first use this dictionary. Lowkey we could just do a vector of dictionaries, we don't care about the actual name of the containing function. 

* Honestly for label globalization i should globalize the label using the map before even putting it into the parsed_items stack. Labels can be used in basically any other instruction, curently I'm only handling these cases inside of the Instruction label and Instruction branch label actions.

* bruh apparently the first function defined does not need to be main (look at test119.)

test 116 might be infinite looping whoops
* 116 fixed, now test 394 is not finishing

Test 331: test381.L3                                                                                           [FAILED]
Test 333: test112.L3                                                                                           [FAILED]
Test 335: test293.L3                                                                                           [FAILED]
Test 336: test214.L3                                                                                           [FAILED]
Test 345: test362.L3                                                                                           [FAILED]
Test 426: test320.L3                                                                                           [FAILED]
Test 427: test319.L3                                                                                           [FAILED]

### Update 
320 passes, all the rest fail. Test 319 fails in the middle of execution instead of afterwards, so this should be a good candidate for the bulk of the debugging.



```python
.text
.globl go
go:
pushq %rbx
pushq %rbp
pushq %r12
pushq %r13
pushq %r14
pushq %r15
call _main
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbp
popq %rbx
retq
_main:
subq $96, %rsp
_MainEntry_global_0:
movq $10, %r10
movq %r10, 400(%rsp)
movq 400(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
salq $1, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
addq $1, %r10
movq %r10, 8(%rsp)
movq $_ret_main_global_1, -8(%rsp)
movq 8(%rsp), %r10
movq %r10, %rdi
movq $2, %rsi
subq $8, %rsp
jmp _Alloc1DArr
_ret_main_global_1:
movq %rax, %r10
movq %r10, 40(%rsp)
movq $_ret_main_global_2, -8(%rsp)
movq 8(%rsp), %r10
movq %r10, %rdi
movq $4, %rsi
subq $8, %rsp
jmp _Alloc1DArr
_ret_main_global_2:
movq %rax, %r10
movq %r10, 24(%rsp)
movq $_ret_main_global_3, -8(%rsp)
movq 40(%rsp), %r10
movq %r10, %rdi
subq $8, %rsp
jmp _CalcArrSum
_ret_main_global_3:
movq %rax, %r10
movq %r10, 48(%rsp)
movq $_ret_main_global_4, -8(%rsp)
movq 24(%rsp), %r10
movq %r10, %rdi
subq $8, %rsp
jmp _CalcArrSum
_ret_main_global_4:
movq %rax, %r10
movq %r10, 32(%rsp)
movq 48(%rsp), %r10
movq %r10, %r10
movq %r10, 152(%rsp)
movq 32(%rsp), %r11
movq 152(%rsp), %r10
addq %r11, %r10
movq %r10, 152(%rsp)
movq 48(%rsp), %r10
movq %r10, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r11
movq 32(%rsp), %r10
imulq %r10, %r11
movq %r11, 0(%rsp)
movq 48(%rsp), %r10
movq %r10, %r10
movq %r10, 224(%rsp)
movq 224(%rsp), %r10
salq $1, %r10
movq %r10, 224(%rsp)
movq 224(%rsp), %r10
movq %r10, %r10
movq %r10, 224(%rsp)
movq 224(%rsp), %r10
addq $1, %r10
movq %r10, 224(%rsp)
movq 224(%rsp), %r10
movq %r10, %rdi
call print
movq 32(%rsp), %r10
movq %r10, %r10
movq %r10, 168(%rsp)
movq 168(%rsp), %r10
salq $1, %r10
movq %r10, 168(%rsp)
movq 168(%rsp), %r10
movq %r10, %r10
movq %r10, 168(%rsp)
movq 168(%rsp), %r10
addq $1, %r10
movq %r10, 168(%rsp)
movq 168(%rsp), %r10
movq %r10, %rdi
call print
movq 152(%rsp), %r10
movq %r10, %r10
movq %r10, 64(%rsp)
movq 64(%rsp), %r10
salq $1, %r10
movq %r10, 64(%rsp)
movq 64(%rsp), %r10
movq %r10, %r10
movq %r10, 64(%rsp)
movq 64(%rsp), %r10
addq $1, %r10
movq %r10, 64(%rsp)
movq 0(%rsp), %r10
movq %r10, %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
salq $1, %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
movq %r10, %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
addq $1, %r10
movq %r10, 16(%rsp)
movq 64(%rsp), %r10
movq %r10, %rdi
call print
movq 16(%rsp), %r10
movq %r10, %rdi
call print
addq $96, %rsp
retq
```


### Latest
Here is instruction after which the program segfaults
```python
 %ProdOfArr <- %Arr1Sum * %Arr2Sum
```

 call print (1)


 Test 426: test320.L3                                                                                           [FAILED]
Test 427: test319.L3                                                                                           [FAILED]
Test 430: test178.L3                                                                                           [OK]

########## SUMMARY
Failed tests: test319.L3 test320.L3 
Test passed: 429 out of 431


The error in test320 seems to be caused by our L3 parser. Once we pass in the L2 program produced by simone's L3 compiler to our own L2 compiler, we get the correct output from the subsequent a.out. We also found that Simone's L2 compiler produces a valid a.out executable when run on the prog.L2 output of our L3 compiler. Simone's L1 compiler also produces a correct a.out executable whenever it is run on the prog.L1 ouput created by our L3 and L2 compilers.

We found that the Prog.L2 output of simone's L3 compiler, when compiled by our L2 and L1 compilers, produces a correct a.out executable.

From all of these, it seems that our L3 and L2 compilers are not cooperating. I would guess that simone's L2 compiler is able to produce a working executable only because his doesn't spill as great a quantity of variables as our L2 compiler does. In other words, simone's compiler doesn't trigger the bug created by our L3 compiler because it is only evident when dealing with stack locations or something of that nature.

The program is actually segfaulting in the *entry_label_6* labeled section of the prog code. Here is the stack and error output from gdb:
```
[0] from 0x0000000000401e38 in _entry_global_64
[1] from 0x0000000000000002
[2] from 0x00007ffff7a9be73 in _IO_new_file_overflow+259 at fileops.c:788
[3] from 0x0000000000000020
[4] from 0x0000000000000001
[5] from 0x0000000000403745 in print+21 at ../lib/runtime.c:84
[6] from 0x0000000000401fd3 in _save_global_97
[7] from 0x0000000000000020
[8] from 0x0000000000000001
[9] from 0x00007ffff7208080
[+]
```
```
==3865998== Invalid read of size 8
==3865998==    at 0x401E38: ??? (in /home/apc6353/Documents/school/cs322/322_framework/L3/a.out)
==3865998==    by 0x1: ???
==3865998==    by 0x4EDAE72: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:788)
==3865998==    by 0x1F: ???
==3865998==  Address 0x30 is not stack'd, malloc'd or (recently) free'd
==3865998== 
==3865998== 
==3865998== Process terminating with default action of signal 11 (SIGSEGV)
==3865998==  Access not within mapped region at address 0x30
==3865998==    at 0x401E38: ??? (in /home/apc6353/Documents/school/cs322/322_framework/L3/a.out)
==3865998==    by 0x1: ???
==3865998==    by 0x4EDAE72: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:788)
==3865998==    by 0x1F: ???
==3865998==  If you believe this happened as a result of a stack
==3865998==  overflow in your program's main thread (unlikely but
==3865998==  possible), you can try to increase the size of the
==3865998==  main thread stack using the --main-stacksize= flag.
==3865998==  The main thread stack size used in this run was 8388608.
==3865998== 
```

### Update
Ok so after switching our L3 compiler to stop saving return labels for standard library functions, the executable was able to produce a few more lines of output. note that only the first two lines match simones output however.
```
1
{s:6, 2, 2, 0, 1, 1, 1}
2
nil
Segmentation fault
```

### Attempts

* *call allocate (a, b)* means that we allocate a size 5 array of 1's i think.
    * so the following sequence of instructions should print 5 i believe (i placed this into customtests\testg.L3):
```
 %printing_buf <- call allocate (5, 1)

 %andy_var <- load %printing_buf
 %andy_var <- %andy_var << 1
 %andy_var <- %andy_var + 1
 call print(%andy_var)
```

okay the program went nuts infinite looping after this. However it did produce the expected behavior when compiled with simone's L3c. Note that you pass in encoded values to allocate (we pass in 5 to allocate, this is an encoded 2 so the allocate function creates an array of size 2.)