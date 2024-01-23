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
subq $8, %rsp
movq %r12, 0(%rsp)
movq $50, %rdi
salq $1, %rdi
addq $1, %rdi
movq $1, %rsi
call allocate
movq %rax, %r12
movq %r12, %rdi
addq $8, %rdi
movq %r12, %rsi
addq $16, %rsi
movq $3, 0(%rdi)
movq $3, 0(%rsi)
movq $1, %rsi
movq $1, %rax
movq $2, %r8
_call_label0:
addq $1, %r8
movq %rsi, %rdx
addq %rax, %rdx
movq %rdx, %rdi
salq $1, %rdi
addq $1, %rdi
movq %r8, %r9
imulq $8, %r9
movq %r12, %rcx
addq %r9, %rcx
movq %rdi, 0(%rcx)
movq %rax, %rsi
movq %rdx, %rax
cmpq $50, %r8
setl %dil
movzbq %dil, %rdi
cmpq $1, %rdi
je _call_label0
movq %r12, %rdi
call print
movq $0, %rsi
movq $0, %r8
_call_label1:
cmpq $50, %r8
setge %dil
movzbq %dil, %rdi
cmpq $1, %rdi
je _call_label2
movq %r8, %r9
imulq $8, %r9
movq %r9, %rcx
addq %r12, %rcx
movq 0(%rcx), %rdi
sarq $1, %rdi
addq %rdi, %rsi
addq $1, %r8
jmp _call_label1
_call_label2:
salq $1, %rsi
addq $1, %rsi
movq %rsi, %rdi
call print
movq 0(%rsp), %r12
addq $8, %rsp
retq
