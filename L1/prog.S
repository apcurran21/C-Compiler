.text
.globl go
go:
pushq %rbx
pushq %rbp
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
subq $16, %rsp
movq $1, %r10
movq %r10, 24(%rsp)
movq $0, %r11
movq $1, %r10
movq %r10, 8(%rsp)
movq $0, %r10
movq %r10, 16(%rsp)
_loop:
movq %r11, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r11
movq 8(%rsp), %r10
addq %r10, %r11
movq %r11, 0(%rsp)
movq 0(%rsp), %r10
movq %r10, %rdi
movq 24(%rsp), %rcx
salq %cl, %rdi
addq $1, %rdi
call print
movq 8(%rsp), %r10
movq %r10, %r11
movq 0(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 16(%rsp), %r10
inc %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
cmpq $20, %r10
setle %al
movzbq %al, %rax
cmpq $1, %rax
je _loop
addq $16, %rsp
retq
