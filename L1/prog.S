   .text
   .globl go

go:
   # save callee-saved registers
   pushq %rbx
   pushq %rbp
   pushq %r12
   pushq %r13
   pushq %r14
   pushq %r15

   call _go

   # restore callee-saved registers and return
   popq %r15
   popq %r14
   popq %r13
   popq %r12
   popq %rbp
   popq %rbx
   retq


_encode:
   salq $1, %rdi
   addq $1, %rdi
   movq %rdi, %rax
   retq


_go:
   movq $-41, %rdi
   movq $_test1, -8(%rsp)
   subq $8, %rsp      # Allocate extra arguments on the stack as well as the return address 
   jmp _mod3        # Call to @mod3
_test1:
   movq $234, %rdi
   movq $_test2, -8(%rsp)
   subq $8, %rsp      # Allocate extra arguments on the stack as well as the return address 
   jmp _mod3        # Call to @mod3
_test2:
   movq $0, %rdi
   movq $_test3, -8(%rsp)
   subq $8, %rsp      # Allocate extra arguments on the stack as well as the return address 
   jmp _mod3        # Call to @mod3
_test3:
   movq $-310, %rdi
   movq $_test4, -8(%rsp)
   subq $8, %rsp      # Allocate extra arguments on the stack as well as the return address 
   jmp _mod3        # Call to @mod3
_test4:
   retq


_mod3:
   cmpq $0, %rdi
   jg _positive
   imulq $-2, %rdi
_positive:
_loop:
   cmpq $3, %rdi
   jl _return
   movq %rdi, %rsi
   andq $3, %rsi
   cmpq $3, %rsi
   je _shift
   cmpq $0, %rsi
   je _shift
   subq $3, %rdi
   jmp _loop
_shift:
   sarq $2, %rdi
   jmp _loop
_return:
   movq $_encode_ret, -8(%rsp)
   subq $8, %rsp      # Allocate extra arguments on the stack as well as the return address 
   jmp _encode        # Call to @encode
_encode_ret:
   movq %rax, %rdi
   call print # runtime system call
   retq

