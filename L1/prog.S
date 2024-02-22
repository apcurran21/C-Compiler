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
movq $1, %r10
movq $2, %r11
cmpq %r11, %r10
setl %r10b
movzbq %r10b, %r10
movq %r10, %rax
retq
