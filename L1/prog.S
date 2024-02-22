.text
.globl go
go:
pushq %rbx
pushq %rbp
pushq %r12
pushq %r13
pushq %r14
pushq %r15
call _entry
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbp
popq %rbx
retq
_entry:
movq $1, %r10
movq %r10, 0(%rsp)
movq $1, %rdi
salq $1, %rdi
addq $1, %rdi
call print
movq 0(%rsp), %r10
movq %r10, %rdi
call print
retq
