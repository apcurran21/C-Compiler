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
subq $240, %rsp
_call_label0:
jmp _call_label1
_call_label1:
movq $0, %r10
movq %r10, 8(%rsp)
movq $43, %r10
movq %r10, 8(%rsp)
movq $55, %r10
movq %r10, 0(%rsp)
movq $32, %r8
movq $74, %r9
movq $67, %rax
movq $83, %r10
movq %r10, 0(%rsp)
movq $39, %rcx
movq $45, %rdi
movq $22, %rdx
movq $41, %rsi
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq 8(%rsp), %r10
movq 0(%rsp), %r10
movq 8(%rsp), %r10
movq 0(%rsp), %r10
movq 8(%rsp), %r10
movq 8(%rsp), %r10
movq 0(%rsp), %r10
movq 0(%rsp), %r11
movq 8(%rsp), %r10
movq 8(%rsp), %r10
movq 8(%rsp), %r10
addq %r11, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 0(%rsp), %r10
movq 0(%rsp), %r10
movq 0(%rsp), %r10
movq 8(%rsp), %r10
movq 8(%rsp), %r10
movq 0(%rsp), %r10
movq 8(%rsp), %r10
movq 0(%rsp), %r10
movq 0(%rsp), %r10
movq 8(%rsp), %r10
movq 8(%rsp), %r11
movq 0(%rsp), %r10
movq 0(%rsp), %r10
movq 0(%rsp), %r10
addq %r10, %r11
movq %r11, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
addq %r8, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
addq %r9, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
addq %rax, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r11
movq 0(%rsp), %r10
addq %r10, %r11
movq %r11, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
addq %rcx, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
addq %rdi, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
addq %rdx, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
addq %rsi, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
salq $1, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
addq $1, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %rdi
call print
addq $240, %rsp
retq
