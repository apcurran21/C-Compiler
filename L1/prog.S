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
_entry_global_0:
movq $5, %rdi
movq $5, %rsi
movq $3, %rdx
movq $9, %rcx
call tensor_error
retq
