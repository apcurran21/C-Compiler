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
subq $80, %rsp
_NNNNNNNNN:
jmp _entrance
_entrance:
movq $11, %r10
sarq $1, %r10
movq %r10, %r11
movq $11, %r10
sarq $1, %r10
movq %r11, %r11
imulq %r10, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %r11
addq $4, %r11
movq %r11, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq $11, 0(%r10)
movq 8(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq $11, 0(%r10)
movq $10, %r10
sarq $1, %r10
movq %r10, %r11
movq $10, %r10
sarq $1, %r10
movq %r11, %r11
imulq %r10, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %r11
addq $4, %r11
movq %r11, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 72(%rsp)
movq 72(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq $10, 0(%r10)
movq 72(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq $10, 0(%r10)
movq $20, %r10
sarq $1, %r10
movq %r10, %r10
movq $20, %r11
sarq $1, %r11
movq %r10, %r10
imulq %r11, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r10
addq $4, %r10
movq %r10, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 32(%rsp)
movq 32(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq $20, 0(%r10)
movq 32(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq $20, 0(%r10)
movq $10, %r10
sarq $1, %r10
movq %r10, %r11
movq $40, %r10
sarq $1, %r10
movq %r11, %r11
imulq %r10, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %r11
addq $4, %r11
movq %r11, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 24(%rsp)
movq 24(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq $10, 0(%r10)
movq 24(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq $40, 0(%r10)
movq $3, %r10
sarq $1, %r10
movq %r10, %r10
movq $45, %r11
sarq $1, %r11
movq %r10, %r10
imulq %r11, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r10
addq $4, %r10
movq %r10, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq $3, 0(%r10)
movq 16(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq $45, 0(%r10)
movq $3, %r10
sarq $1, %r10
movq %r10, %r11
movq $10, %r10
sarq $1, %r10
movq %r11, %r11
imulq %r10, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %r11
addq $4, %r11
movq %r11, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 48(%rsp)
movq 48(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq $3, 0(%r10)
movq 48(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq $10, 0(%r10)
movq $3, %r10
sarq $1, %r10
movq %r10, %r11
movq $10, %r10
sarq $1, %r10
movq %r11, %r11
imulq %r10, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %r11
addq $4, %r11
movq %r11, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq $3, 0(%r10)
movq 0(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq $10, 0(%r10)
movq $3, %r10
sarq $1, %r10
movq %r10, %r11
movq $10, %r10
sarq $1, %r10
movq %r11, %r11
imulq %r10, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %r11
addq $4, %r11
movq %r11, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 40(%rsp)
movq 40(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq $3, 0(%r10)
movq 40(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq $10, 0(%r10)
movq $3, %r10
sarq $1, %r10
movq %r10, %r11
movq $10, %r10
sarq $1, %r10
movq %r11, %r11
imulq %r10, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %r11
addq $4, %r11
movq %r11, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 64(%rsp)
movq 64(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq $3, 0(%r10)
movq 64(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq $10, 0(%r10)
movq $3, %r10
sarq $1, %r10
movq %r10, %r11
movq $10, %r10
sarq $1, %r10
movq %r11, %r11
imulq %r10, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %r11
addq $4, %r11
movq %r11, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 56(%rsp)
movq 56(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq $3, 0(%r10)
movq 56(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq $10, 0(%r10)
movq $_sum10, -8(%rsp)
movq 8(%rsp), %r10
movq %r10, %rdi
subq $8, %rsp
jmp _sum
_sum10:
movq %rax, %r10
movq %r10, %r10
movq $_sum11, -8(%rsp)
movq 72(%rsp), %r10
movq %r10, %rdi
subq $8, %rsp
jmp _sum
_sum11:
movq %rax, %r10
movq %r10, %r10
addq %r10, %r10
movq $_sum12, -8(%rsp)
movq 32(%rsp), %r10
movq %r10, %rdi
subq $8, %rsp
jmp _sum
_sum12:
movq %rax, %r10
movq %r10, %r10
addq %r10, %r10
movq $_sum13, -8(%rsp)
movq 24(%rsp), %r10
movq %r10, %rdi
subq $8, %rsp
jmp _sum
_sum13:
movq %rax, %r10
movq %r10, %r10
addq %r10, %r10
movq $_sum14, -8(%rsp)
movq 16(%rsp), %r10
movq %r10, %rdi
subq $8, %rsp
jmp _sum
_sum14:
movq %rax, %r10
movq %r10, %r10
addq %r10, %r10
movq $_sum15, -8(%rsp)
movq 48(%rsp), %r10
movq %r10, %rdi
subq $8, %rsp
jmp _sum
_sum15:
movq %rax, %r10
movq %r10, %r10
addq %r10, %r10
movq $_sum16, -8(%rsp)
movq 0(%rsp), %r10
movq %r10, %rdi
subq $8, %rsp
jmp _sum
_sum16:
movq %rax, %r10
movq %r10, %r10
addq %r10, %r10
movq $_sum17, -8(%rsp)
movq 40(%rsp), %r10
movq %r10, %rdi
subq $8, %rsp
jmp _sum
_sum17:
movq %rax, %r10
movq %r10, %r10
addq %r10, %r10
movq $_sum18, -8(%rsp)
movq 64(%rsp), %r10
movq %r10, %rdi
subq $8, %rsp
jmp _sum
_sum18:
movq %rax, %r10
movq %r10, %r10
addq %r10, %r10
movq $_sum19, -8(%rsp)
movq 56(%rsp), %r10
movq %r10, %rdi
subq $8, %rsp
jmp _sum
_sum19:
movq %rax, %r10
movq %r10, %r10
addq %r10, %r10
addq $80, %rsp
retq
_sum:
_NNNNNNNNNN:
jmp _entrance
_entrance2:
movq $0, %r10
imulq $8, %r10
movq %r10, %r10
addq $8, %r10
movq %r11, %r8
addq %r10, %r8
movq 0(%r8), %r9
movq $1, %r10
imulq $8, %r10
movq %r10, %r8
addq $8, %r8
movq %r11, %r10
addq %r8, %r10
movq 0(%r10), %r10
movq %r9, %r8
subq $1, %r8
movq %r10, %r9
subq $1, %r9
movq $0, %r10
movq %r11, %r10
addq $16, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq $1, %r8
movq %r10, %r8
imulq %r8, %r8
movq $0, %r10
imulq %r8, %r10
movq %r10, %r10
addq %r10, %r10
movq %r10, %r10
addq %r9, %r10
movq %r10, %r8
imulq $8, %r8
movq %r8, %r8
addq $24, %r8
movq %r11, %r10
addq %r8, %r10
movq 0(%r10), %r10
movq %r10, %r10
addq %r10, %r10
movq %r10, %rax
retq
_entrance:
movq $0, %r10
movq $0, %r10
jmp _entrance2
