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


_funct:
   movq 8(%rsp), %rax
   addq $16, %rsp # Free stack locations
   retq


_go:
   movq $_funct_ret, -8(%rsp)
   movq $3, %rdi
   movq $5, %rsi
   movq $7, %rdx
   movq $9, %rcx
   movq $11, %r8
   movq $13, %r9
   movq $15, -16(%rsp)
   movq $-17, -24(%rsp)
   subq $24, %rsp      # Allocate extra arguments on the stack as well as the return address 
   jmp _funct        # Call to @funct
_funct_ret:
   movq %rax, %rdi
   call print # runtime system call
   retq

