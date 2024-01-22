.text
.globl go
go:
pushq %rbx
pushq %rbx
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
movq $4, %rax
andq $1, %rax
imulq $2, %rax
addq $1, %rax
movq %rax, %rdi
call print
retq
