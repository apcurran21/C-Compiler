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
subq $96, %rsp
_call_label0:
movq $10, %r10
movq %r10, 352(%rsp)
movq 352(%rsp), %r10
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
movq $2, %rsi
movq $_call_label1, -8(%rsp)
subq $8, %rsp
jmp _Alloc1DArr
_call_label1:
movq %rax, %r10
movq %r10, 40(%rsp)
movq 8(%rsp), %r10
movq %r10, %rdi
movq $4, %rsi
movq $_call_label2, -8(%rsp)
subq $8, %rsp
jmp _Alloc1DArr
_call_label2:
movq %rax, %r10
movq %r10, 24(%rsp)
movq 40(%rsp), %r10
movq %r10, %rdi
movq $_call_label3, -8(%rsp)
subq $8, %rsp
jmp _CalcArrSum
_call_label3:
movq %rax, %r10
movq %r10, 48(%rsp)
movq 24(%rsp), %r10
movq %r10, %rdi
movq $_call_label4, -8(%rsp)
subq $8, %rsp
jmp _CalcArrSum
_call_label4:
movq %rax, %r10
movq %r10, 32(%rsp)
movq 48(%rsp), %r10
movq %r10, %r10
movq %r10, 152(%rsp)
movq 32(%rsp), %r11
movq 152(%rsp), %r10
addq %r11, %r10
movq %r10, 152(%rsp)
movq 48(%rsp), %r10
movq %r10, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r11
movq 32(%rsp), %r10
imulq %r10, %r11
movq %r11, 0(%rsp)
movq 48(%rsp), %r10
movq %r10, %r10
movq %r10, 224(%rsp)
movq 224(%rsp), %r10
salq $1, %r10
movq %r10, 224(%rsp)
movq 224(%rsp), %r10
movq %r10, %r10
movq %r10, 224(%rsp)
movq 224(%rsp), %r10
addq $1, %r10
movq %r10, 224(%rsp)
movq 224(%rsp), %r10
movq %r10, %rdi
call print
movq 32(%rsp), %r10
movq %r10, %r10
movq %r10, 168(%rsp)
movq 168(%rsp), %r10
salq $1, %r10
movq %r10, 168(%rsp)
movq 168(%rsp), %r10
movq %r10, %r10
movq %r10, 168(%rsp)
movq 168(%rsp), %r10
addq $1, %r10
movq %r10, 168(%rsp)
movq 168(%rsp), %r10
movq %r10, %rdi
call print
movq 152(%rsp), %r10
movq %r10, %r10
movq %r10, 64(%rsp)
movq 64(%rsp), %r10
salq $1, %r10
movq %r10, 64(%rsp)
movq 64(%rsp), %r10
movq %r10, %r10
movq %r10, 64(%rsp)
movq 64(%rsp), %r10
addq $1, %r10
movq %r10, 64(%rsp)
movq 0(%rsp), %r10
movq %r10, %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
salq $1, %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
movq %r10, %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
addq $1, %r10
movq %r10, 16(%rsp)
movq 64(%rsp), %r10
movq %r10, %rdi
call print
movq 16(%rsp), %r10
movq %r10, %rdi
call print
addq $96, %rsp
retq
_CalcArrSum:
movq %rdi, %r8
_call_label_ciao_5:
movq $0, %r10
imulq $8, %r10
movq %r10, %r10
addq $16, %r10
movq %r8, %r11
addq %r10, %r11
movq 0(%r11), %rax
movq %rax, %rax
sarq $1, %rax
movq $0, %rcx
movq $0, %r9
jmp _call_label_ciao_6
_call_label_ciao_6:
movq $0, %r10
movq $1, %r11
movq %r10, %r10
addq %rcx, %r10
movq %r10, %r11
imulq $8, %r11
movq %r11, %r11
addq $24, %r11
movq %r8, %r10
addq %r11, %r10
movq 0(%r10), %r10
movq %rcx, %rcx
addq $1, %rcx
movq %r9, %r9
addq %r10, %r9
cmpq %rax, %rcx
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao_6
jmp _call_label_ciao_7
_call_label_ciao_7:
movq %r9, %rax
retq
_Alloc1DArr:
subq $16, %rsp
movq %rdi, %r10
movq %r10, 8(%rsp)
movq %rsi, %r10
movq %r10, 0(%rsp)
_call_label_ciao__ciao_8:
movq 8(%rsp), %r10
movq %r10, %r10
sarq $1, %r10
movq %r10, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r10
addq $4, %r10
movq %r10, %rdi
movq $1, %rsi
call allocate
movq %rax, %r11
movq %r11, %r10
addq $8, %r10
movq $3, 0(%r10)
movq %r11, %r10
addq $16, %r10
movq 8(%rsp), %r8
movq %r8, 0(%r10)
movq $0, %r10
imulq $8, %r10
movq %r10, %r8
addq $16, %r8
movq %r11, %r10
addq %r8, %r10
movq 0(%r10), %r8
movq %r8, %r8
sarq $1, %r8
movq $0, %r9
movq $0, %r10
jmp _call_label_ciao__ciao_9
_call_label_ciao__ciao_9:
movq $0, %rcx
movq $1, %r10
movq %rcx, %rcx
addq %r9, %rcx
movq %rcx, %r10
imulq $8, %r10
movq %r10, %r10
addq $24, %r10
movq %r11, %rcx
addq %r10, %rcx
movq 0(%rsp), %r10
movq %r10, 0(%rcx)
movq %r9, %r9
addq $1, %r9
cmpq %r8, %r9
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao_9
jmp _call_label_ciao__ciao_10
_call_label_ciao__ciao_10:
movq %r11, %rax
addq $16, %rsp
retq
