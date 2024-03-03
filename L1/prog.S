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
movq $1, %rdi
movq $_ret_main_global_0, -8(%rsp)
call print
_ret_main_global_0:
retq
