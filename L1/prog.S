.text
.globl go
go:
pushq %rbx
pushq %rbx
pushq %r12
pushq %r13
pushq %r14
pushq %r15
call _go
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbp
popq %rbx
retq
_go:
movq $7, %rdi
sarq STOP, %rdi
call print
retq
