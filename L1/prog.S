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
subq $456, %rsp
_call_label0:
jmp _call_label7
_call_label1:
addq $456, %rsp
retq
_call_label2:
movq 24(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq $3, %r11
movq %r11, %r11
sarq $1, %r11
movq %r9, %r10
movq %r10, 24(%rsp)
movq 24(%rsp), %r10
addq %r11, %r10
movq %r10, 24(%rsp)
movq 24(%rsp), %r10
movq %r10, %r10
movq %r10, 24(%rsp)
movq 24(%rsp), %r10
salq $1, %r10
movq %r10, 24(%rsp)
movq 24(%rsp), %r10
movq %r10, %r10
movq %r10, 24(%rsp)
movq 24(%rsp), %r10
addq $1, %r10
movq %r10, 24(%rsp)
jmp _call_label3
_call_label3:
movq 24(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq 16(%rsp), %r10
movq %r10, %r11
movq %r11, %r11
sarq $1, %r11
cmpq %r11, %r9
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
cmpq $1, %r9
je _call_label4
jmp _call_label1
_call_label4:
movq $1, %r10
movq %r10, 32(%rsp)
jmp _call_label5
_call_label5:
movq 32(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq 0(%rsp), %r10
movq %r10, %r11
movq %r11, %r11
sarq $1, %r11
cmpq %r11, %r9
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
cmpq $1, %r9
je _call_label6
jmp _call_label2
_call_label6:
movq 56(%rsp), %r10
movq %r10, %rdi
movq 48(%rsp), %r10
movq %r10, %rsi
movq 40(%rsp), %r10
movq %r10, %rdx
movq 24(%rsp), %r10
movq %r10, %rcx
movq 32(%rsp), %r10
movq %r10, %r8
movq $_call_label8, -8(%rsp)
subq $8, %rsp
jmp _computeAndPrint
_call_label8:
movq 32(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq $3, %r11
movq %r11, %r11
sarq $1, %r11
movq %r9, %r10
movq %r10, 32(%rsp)
movq 32(%rsp), %r10
addq %r11, %r10
movq %r10, 32(%rsp)
movq 32(%rsp), %r10
movq %r10, %r10
movq %r10, 32(%rsp)
movq 32(%rsp), %r10
salq $1, %r10
movq %r10, 32(%rsp)
movq 32(%rsp), %r10
movq %r10, %r10
movq %r10, 32(%rsp)
movq 32(%rsp), %r10
addq $1, %r10
movq %r10, 32(%rsp)
jmp _call_label5
_call_label7:
movq $0, %r10
movq %r10, 40(%rsp)
movq $0, %r10
movq %r10, 48(%rsp)
movq $0, %r10
movq %r10, 56(%rsp)
movq $601, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
sarq $1, %r10
movq %r10, %r11
movq 8(%rsp), %r10
movq %r10, %r10
sarq $1, %r10
movq %r11, %r11
imulq %r10, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %r11
addq $6, %r11
movq %r11, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 56(%rsp)
movq 56(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq $5, 0(%r10)
movq 56(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq 8(%rsp), %r11
movq %r11, 0(%r10)
movq 56(%rsp), %r10
movq %r10, %r11
addq $24, %r11
movq 8(%rsp), %r10
movq %r10, 0(%r11)
movq 8(%rsp), %r10
movq %r10, %r10
sarq $1, %r10
movq %r10, %r11
movq 8(%rsp), %r10
movq %r10, %r10
sarq $1, %r10
movq %r11, %r11
imulq %r10, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %r11
addq $6, %r11
movq %r11, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 48(%rsp)
movq 48(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq $5, 0(%r10)
movq 48(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq 8(%rsp), %r11
movq %r11, 0(%r10)
movq 48(%rsp), %r10
movq %r10, %r10
addq $24, %r10
movq 8(%rsp), %r11
movq %r11, 0(%r10)
movq 8(%rsp), %r10
movq %r10, %r10
sarq $1, %r10
movq %r10, %r11
movq 8(%rsp), %r10
movq %r10, %r10
sarq $1, %r10
movq %r11, %r11
imulq %r10, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %r11
addq $6, %r11
movq %r11, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 40(%rsp)
movq 40(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq $5, 0(%r10)
movq 40(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq 8(%rsp), %r11
movq %r11, 0(%r10)
movq 40(%rsp), %r10
movq %r10, %r10
addq $24, %r10
movq 8(%rsp), %r11
movq %r11, 0(%r10)
movq $9, %r10
movq %r10, 16(%rsp)
movq $9, %r10
movq %r10, 0(%rsp)
movq $1, %r10
movq %r10, 24(%rsp)
jmp _call_label3
_computeAndPrint:
subq $200, %rsp
movq %rdi, %r10
movq %r10, 0(%rsp)
movq %rsi, %r10
movq %r10, 16(%rsp)
movq %rdx, %r10
movq %r10, 8(%rsp)
movq %rcx, %r11
movq %r8, %r10
movq %r10, 24(%rsp)
_call_label_ciao_9:
jmp _call_label_ciao_10
_call_label_ciao_10:
movq 0(%rsp), %r10
movq %r10, %rdi
movq %r11, %rsi
movq $_call_label_ciao_11, -8(%rsp)
subq $8, %rsp
jmp _initMatrix
_call_label_ciao_11:
movq 16(%rsp), %r10
movq %r10, %rdi
movq 24(%rsp), %r10
movq %r10, %rsi
movq $_call_label_ciao_12, -8(%rsp)
subq $8, %rsp
jmp _initMatrix
_call_label_ciao_12:
movq 0(%rsp), %r10
movq %r10, %rdi
movq 16(%rsp), %r10
movq %r10, %rsi
movq 8(%rsp), %r10
movq %r10, %rdx
movq $_call_label_ciao_13, -8(%rsp)
subq $8, %rsp
jmp _matrixMultiplication
_call_label_ciao_13:
movq 0(%rsp), %r10
movq %r10, %rdi
movq $_call_label_ciao_14, -8(%rsp)
subq $8, %rsp
jmp _totalSum
_call_label_ciao_14:
movq %rax, %r10
movq %r10, %rdi
call print
movq 16(%rsp), %r10
movq %r10, %rdi
movq $_call_label_ciao_15, -8(%rsp)
subq $8, %rsp
jmp _totalSum
_call_label_ciao_15:
movq %rax, %r10
movq %r10, %rdi
call print
movq 8(%rsp), %r10
movq %r10, %rdi
movq $_call_label_ciao_16, -8(%rsp)
subq $8, %rsp
jmp _totalSum
_call_label_ciao_16:
movq %rax, %r10
movq %r10, %rdi
call print
addq $200, %rsp
retq
_initMatrix:
subq $328, %rsp
movq %rdi, %r10
movq %r10, 24(%rsp)
movq %rsi, %r10
movq %r10, 16(%rsp)
_call_label_ciao__ciao_17:
jmp _call_label_ciao__ciao_29
_call_label_ciao__ciao_18:
addq $328, %rsp
retq
_call_label_ciao__ciao_19:
movq 8(%rsp), %r10
movq %r10, %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq $3, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq %rdx, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
addq %rcx, %r10
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
jmp _call_label_ciao__ciao_20
_call_label_ciao__ciao_20:
movq 8(%rsp), %r10
movq %r10, %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq %r11, %rcx
movq %rcx, %rcx
sarq $1, %rcx
cmpq %rcx, %rdx
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %rdx
movq %rdx, %rdx
sarq $1, %rdx
cmpq $1, %rdx
je _call_label_ciao__ciao_21
jmp _call_label_ciao__ciao_18
_call_label_ciao__ciao_21:
movq $1, %r9
jmp _call_label_ciao__ciao_22
_call_label_ciao__ciao_22:
movq %r9, %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq %r8, %rcx
movq %rcx, %rcx
sarq $1, %rcx
cmpq %rcx, %rdx
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %rdx
movq %rdx, %rdx
sarq $1, %rdx
cmpq $1, %rdx
je _call_label_ciao__ciao_23
jmp _call_label_ciao__ciao_19
_call_label_ciao__ciao_23:
movq 16(%rsp), %r10
movq %r10, %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq 8(%rsp), %r10
movq %r10, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq %rdx, %r10
movq %r10, 40(%rsp)
movq 40(%rsp), %r10
addq %rcx, %r10
movq %r10, 40(%rsp)
movq 40(%rsp), %r10
movq %r10, %r10
movq %r10, 40(%rsp)
movq 40(%rsp), %r10
salq $1, %r10
movq %r10, 40(%rsp)
movq 40(%rsp), %r10
movq %r10, %r10
movq %r10, 40(%rsp)
movq 40(%rsp), %r10
addq $1, %r10
movq %r10, 40(%rsp)
movq 40(%rsp), %r10
movq %r10, %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq %r9, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq %rdx, %r10
movq %r10, 40(%rsp)
movq 40(%rsp), %r10
addq %rcx, %r10
movq %r10, 40(%rsp)
movq 40(%rsp), %r10
movq %r10, %r10
movq %r10, 40(%rsp)
movq 40(%rsp), %r10
salq $1, %r10
movq %r10, 40(%rsp)
movq 40(%rsp), %r10
movq %r10, %r10
movq %r10, 40(%rsp)
movq 40(%rsp), %r10
addq $1, %r10
movq %r10, 40(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 32(%rsp)
movq 32(%rsp), %r10
movq %r10, %r10
movq %r10, 32(%rsp)
movq 32(%rsp), %r10
sarq $1, %r10
movq %r10, 32(%rsp)
movq %r9, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq $0, %rsi
movq 24(%rsp), %r10
cmpq $0, %r10
sete %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao_28
jmp _call_label_ciao__ciao_24
_call_label_ciao__ciao_24:
movq $0, %r10
imulq $8, %r10
movq %r10, %rdx
addq $16, %rdx
movq 24(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq 32(%rsp), %r10
movq %r10, %rsi
movq %rsi, %rsi
salq $1, %rsi
movq %rsi, %rsi
addq $1, %rsi
movq 32(%rsp), %r10
cmpq %rdx, %r10
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao_25
jmp _call_label_ciao__ciao_28
_call_label_ciao__ciao_25:
movq $1, %r10
imulq $8, %r10
movq %r10, %rdx
addq $16, %rdx
movq 24(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq %rcx, %rsi
movq %rsi, %rsi
salq $1, %rsi
movq %rsi, %rsi
addq $1, %rsi
cmpq %r10, %rcx
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao_26
jmp _call_label_ciao__ciao_28
_call_label_ciao__ciao_26:
jmp _call_label_ciao__ciao_27
_call_label_ciao__ciao_27:
movq $0, %rdx
movq 24(%rsp), %r10
movq %r10, %r10
addq $24, %r10
movq 0(%r10), %r10
movq %r10, %rsi
sarq $1, %rsi
movq $1, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
movq %r10, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
imulq %rsi, %r10
movq %r10, 0(%rsp)
movq 32(%rsp), %r10
movq %r10, %r10
movq 0(%rsp), %rsi
imulq %rsi, %r10
movq %rdx, %rdx
addq %r10, %rdx
movq %rdx, %rdx
addq %rcx, %rdx
movq %rdx, %rcx
imulq $8, %rcx
movq %rcx, %rcx
addq $32, %rcx
movq 24(%rsp), %r10
movq %r10, %r10
addq %rcx, %r10
movq 40(%rsp), %rcx
movq %rcx, 0(%r10)
movq %r9, %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq $3, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq %rdx, %r9
addq %rcx, %r9
movq %r9, %r9
salq $1, %r9
movq %r9, %r9
addq $1, %r9
jmp _call_label_ciao__ciao_22
_call_label_ciao__ciao_28:
movq $0, %rdi
call array_tensor_error_null
jmp _call_label_ciao__ciao_27
_call_label_ciao__ciao_29:
movq $0, %r10
imulq $8, %r10
movq %r10, %r11
addq $16, %r11
movq 24(%rsp), %r10
movq %r10, %r10
addq %r11, %r10
movq 0(%r10), %r11
movq $1, %r10
imulq $8, %r10
movq %r10, %r8
addq $16, %r8
movq 24(%rsp), %r10
movq %r10, %r10
addq %r8, %r10
movq 0(%r10), %r8
movq $1, %r10
movq %r10, 8(%rsp)
jmp _call_label_ciao__ciao_20
_matrixMultiplication:
subq $648, %rsp
movq %rdi, %r10
movq %r10, 48(%rsp)
movq %rsi, %r10
movq %r10, 40(%rsp)
movq %rdx, %r10
movq %r10, 32(%rsp)
_call_label_ciao__ciao__ciao_30:
jmp _call_label_ciao__ciao__ciao_77
_call_label_ciao__ciao__ciao_31:
addq $648, %rsp
retq
_call_label_ciao__ciao__ciao_32:
movq 64(%rsp), %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
movq $3, %r9
movq %r9, %r9
sarq $1, %r9
movq %r8, %r10
movq %r10, 64(%rsp)
movq 64(%rsp), %r10
addq %r9, %r10
movq %r10, 64(%rsp)
movq 64(%rsp), %r10
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
jmp _call_label_ciao__ciao__ciao_33
_call_label_ciao__ciao__ciao_33:
movq 64(%rsp), %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
movq 24(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
cmpq %r9, %r8
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
cmpq $1, %r8
je _call_label_ciao__ciao__ciao_34
jmp _call_label_ciao__ciao__ciao_31
_call_label_ciao__ciao__ciao_34:
movq $1, %r10
movq %r10, 0(%rsp)
jmp _call_label_ciao__ciao__ciao_35
_call_label_ciao__ciao__ciao_35:
movq 0(%rsp), %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
movq 16(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
cmpq %r9, %r8
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
cmpq $1, %r8
je _call_label_ciao__ciao__ciao_36
jmp _call_label_ciao__ciao__ciao_32
_call_label_ciao__ciao__ciao_36:
movq $1, %r11
jmp _call_label_ciao__ciao__ciao_37
_call_label_ciao__ciao__ciao_37:
movq %r11, %r8
movq %r8, %r8
sarq $1, %r8
movq 8(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
cmpq %r9, %r8
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
cmpq $1, %r8
je _call_label_ciao__ciao__ciao_38
jmp _call_label_ciao__ciao__ciao_55
_call_label_ciao__ciao__ciao_38:
movq 64(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq %r11, %r8
movq %r8, %r8
sarq $1, %r8
movq $0, %rcx
movq 48(%rsp), %r10
cmpq $0, %r10
sete %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_59
jmp _call_label_ciao__ciao__ciao_39
_call_label_ciao__ciao__ciao_39:
movq $0, %r10
imulq $8, %r10
movq %r10, %rcx
addq $16, %rcx
movq 48(%rsp), %r10
movq %r10, %r10
addq %rcx, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq %r9, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
cmpq %r10, %r9
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_40
jmp _call_label_ciao__ciao__ciao_59
_call_label_ciao__ciao__ciao_40:
movq $1, %r10
imulq $8, %r10
movq %r10, %rcx
addq $16, %rcx
movq 48(%rsp), %r10
movq %r10, %r10
addq %rcx, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq %r8, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
cmpq %r10, %r8
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_41
jmp _call_label_ciao__ciao__ciao_59
_call_label_ciao__ciao__ciao_41:
jmp _call_label_ciao__ciao__ciao_42
_call_label_ciao__ciao__ciao_42:
movq $0, %rcx
movq 48(%rsp), %r10
movq %r10, %r10
addq $24, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq $1, %rdx
movq %rdx, %rdx
imulq %r10, %rdx
movq %r9, %r10
imulq %rdx, %r10
movq %rcx, %rcx
addq %r10, %rcx
movq %rcx, %rcx
addq %r8, %rcx
movq %rcx, %r8
imulq $8, %r8
movq %r8, %r8
addq $32, %r8
movq 48(%rsp), %r10
movq %r10, %r10
addq %r8, %r10
movq 0(%r10), %r8
movq %r11, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq 0(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq $0, %rdx
movq 40(%rsp), %r10
cmpq $0, %r10
sete %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_58
jmp _call_label_ciao__ciao__ciao_43
_call_label_ciao__ciao__ciao_43:
movq $0, %r10
imulq $8, %r10
movq %r10, %rdx
addq $16, %rdx
movq 40(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq %rcx, %rdx
movq %rdx, %rdx
salq $1, %rdx
movq %rdx, %rdx
addq $1, %rdx
cmpq %r10, %rcx
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_44
jmp _call_label_ciao__ciao__ciao_58
_call_label_ciao__ciao__ciao_44:
movq $1, %r10
imulq $8, %r10
movq %r10, %rdx
addq $16, %rdx
movq 40(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq %r9, %rdx
movq %rdx, %rdx
salq $1, %rdx
movq %rdx, %rdx
addq $1, %rdx
cmpq %r10, %r9
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_45
jmp _call_label_ciao__ciao__ciao_58
_call_label_ciao__ciao__ciao_45:
jmp _call_label_ciao__ciao__ciao_46
_call_label_ciao__ciao__ciao_46:
movq $0, %rdx
movq 40(%rsp), %r10
movq %r10, %r10
addq $24, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq $1, %rsi
movq %rsi, %rsi
imulq %r10, %rsi
movq %rcx, %r10
imulq %rsi, %r10
movq %rdx, %rdx
addq %r10, %rdx
movq %rdx, %rdx
addq %r9, %rdx
movq %rdx, %r9
imulq $8, %r9
movq %r9, %r9
addq $32, %r9
movq 40(%rsp), %r10
movq %r10, %r10
addq %r9, %r10
movq 0(%r10), %r10
movq %r8, %r8
movq %r8, %r8
sarq $1, %r8
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq %r8, %rcx
imulq %r9, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
movq 64(%rsp), %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
movq 0(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq $0, %rdx
movq 32(%rsp), %r10
cmpq $0, %r10
sete %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_57
jmp _call_label_ciao__ciao__ciao_47
_call_label_ciao__ciao__ciao_47:
movq $0, %r10
imulq $8, %r10
movq %r10, %rdx
addq $16, %rdx
movq 32(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq %r8, %rdx
movq %rdx, %rdx
salq $1, %rdx
movq %rdx, %rdx
addq $1, %rdx
cmpq %r10, %r8
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_48
jmp _call_label_ciao__ciao__ciao_57
_call_label_ciao__ciao__ciao_48:
movq $1, %r10
imulq $8, %r10
movq %r10, %rdx
addq $16, %rdx
movq 32(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq %r9, %rdx
movq %rdx, %rdx
salq $1, %rdx
movq %rdx, %rdx
addq $1, %rdx
cmpq %r10, %r9
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_49
jmp _call_label_ciao__ciao__ciao_57
_call_label_ciao__ciao__ciao_49:
jmp _call_label_ciao__ciao__ciao_50
_call_label_ciao__ciao__ciao_50:
movq $0, %rdx
movq 32(%rsp), %r10
movq %r10, %r10
addq $24, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq $1, %rsi
movq %rsi, %rsi
imulq %r10, %rsi
movq %r8, %r10
imulq %rsi, %r10
movq %rdx, %rdx
addq %r10, %rdx
movq %rdx, %rdx
addq %r9, %rdx
movq %rdx, %r8
imulq $8, %r8
movq %r8, %r8
addq $32, %r8
movq 32(%rsp), %r10
movq %r10, %r10
addq %r8, %r10
movq 0(%r10), %r8
movq %r8, %r8
movq %r8, %r8
sarq $1, %r8
movq $9, %r9
movq %r9, %r9
sarq $1, %r9
movq %r8, %r8
imulq %r9, %r8
movq %r8, %r8
salq $1, %r8
movq %r8, %r8
addq $1, %r8
movq %r8, %r8
movq %r8, %r8
sarq $1, %r8
movq %rcx, %r9
movq %r9, %r9
sarq $1, %r9
movq %r8, %r8
addq %r9, %r8
movq %r8, %r8
salq $1, %r8
movq %r8, %r8
addq $1, %r8
movq 64(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq 0(%rsp), %r10
movq %r10, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq $0, %rdx
movq 32(%rsp), %r10
cmpq $0, %r10
sete %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_56
jmp _call_label_ciao__ciao__ciao_51
_call_label_ciao__ciao__ciao_51:
movq $0, %r10
imulq $8, %r10
movq %r10, %rdx
addq $16, %rdx
movq 32(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq %r9, %rdx
movq %rdx, %rdx
salq $1, %rdx
movq %rdx, %rdx
addq $1, %rdx
cmpq %r10, %r9
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_52
jmp _call_label_ciao__ciao__ciao_56
_call_label_ciao__ciao__ciao_52:
movq $1, %r10
imulq $8, %r10
movq %r10, %rdx
addq $16, %rdx
movq 32(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq %rcx, %rdx
movq %rdx, %rdx
salq $1, %rdx
movq %rdx, %rdx
addq $1, %rdx
cmpq %r10, %rcx
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_53
jmp _call_label_ciao__ciao__ciao_56
_call_label_ciao__ciao__ciao_53:
jmp _call_label_ciao__ciao__ciao_54
_call_label_ciao__ciao__ciao_54:
movq $0, %rdx
movq 32(%rsp), %r10
movq %r10, %r10
addq $24, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq $1, %rsi
movq %rsi, %rsi
imulq %r10, %rsi
movq %r9, %r10
imulq %rsi, %r10
movq %rdx, %rdx
addq %r10, %rdx
movq %rdx, %rdx
addq %rcx, %rdx
movq %rdx, %r9
imulq $8, %r9
movq %r9, %r9
addq $32, %r9
movq 32(%rsp), %r10
movq %r10, %r10
addq %r9, %r10
movq %r8, 0(%r10)
movq %r11, %r8
movq %r8, %r8
sarq $1, %r8
movq $3, %r9
movq %r9, %r9
sarq $1, %r9
movq %r8, %r11
addq %r9, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
jmp _call_label_ciao__ciao__ciao_37
_call_label_ciao__ciao__ciao_55:
movq 0(%rsp), %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
movq $3, %r9
movq %r9, %r9
sarq $1, %r9
movq %r8, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
addq %r9, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
movq %r10, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
salq $1, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
movq %r10, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
addq $1, %r10
movq %r10, 0(%rsp)
jmp _call_label_ciao__ciao__ciao_35
_call_label_ciao__ciao__ciao_56:
movq $0, %rdi
call array_tensor_error_null
jmp _call_label_ciao__ciao__ciao_54
_call_label_ciao__ciao__ciao_57:
movq $0, %rdi
call array_tensor_error_null
jmp _call_label_ciao__ciao__ciao_50
_call_label_ciao__ciao__ciao_58:
movq $0, %rdi
call array_tensor_error_null
jmp _call_label_ciao__ciao__ciao_46
_call_label_ciao__ciao__ciao_59:
movq $0, %rdi
call array_tensor_error_null
jmp _call_label_ciao__ciao__ciao_42
_call_label_ciao__ciao__ciao_60:
movq $1, %r10
movq %r10, 64(%rsp)
jmp _call_label_ciao__ciao__ciao_33
_call_label_ciao__ciao__ciao_61:
movq %r11, %r8
movq %r8, %r8
sarq $1, %r8
movq $3, %r9
movq %r9, %r9
sarq $1, %r9
movq %r8, %r11
addq %r9, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
jmp _call_label_ciao__ciao__ciao_62
_call_label_ciao__ciao__ciao_62:
movq %r11, %r8
movq %r8, %r8
sarq $1, %r8
movq 24(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
cmpq %r9, %r8
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
cmpq $1, %r8
je _call_label_ciao__ciao__ciao_63
jmp _call_label_ciao__ciao__ciao_60
_call_label_ciao__ciao__ciao_63:
movq $1, %rcx
jmp _call_label_ciao__ciao__ciao_64
_call_label_ciao__ciao__ciao_64:
movq %rcx, %r8
movq %r8, %r8
sarq $1, %r8
movq 16(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
cmpq %r9, %r8
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
cmpq $1, %r8
je _call_label_ciao__ciao__ciao_65
jmp _call_label_ciao__ciao__ciao_61
_call_label_ciao__ciao__ciao_65:
movq $1, %rdx
jmp _call_label_ciao__ciao__ciao_66
_call_label_ciao__ciao__ciao_66:
movq %rdx, %r8
movq %r8, %r8
sarq $1, %r8
movq 8(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
cmpq %r9, %r8
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
cmpq $1, %r8
je _call_label_ciao__ciao__ciao_67
jmp _call_label_ciao__ciao__ciao_72
_call_label_ciao__ciao__ciao_67:
movq %r11, %r8
movq %r8, %r8
sarq $1, %r8
movq %rcx, %r10
movq %r10, 80(%rsp)
movq 80(%rsp), %r10
movq %r10, %r10
movq %r10, 80(%rsp)
movq 80(%rsp), %r10
sarq $1, %r10
movq %r10, 80(%rsp)
movq $0, %rsi
movq 32(%rsp), %r10
cmpq $0, %r10
sete %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_73
jmp _call_label_ciao__ciao__ciao_68
_call_label_ciao__ciao__ciao_68:
movq $0, %r10
imulq $8, %r10
movq %r10, %r9
addq $16, %r9
movq 32(%rsp), %r10
movq %r10, %r10
addq %r9, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq %r8, %rsi
movq %rsi, %rsi
salq $1, %rsi
movq %rsi, %rsi
addq $1, %rsi
cmpq %r10, %r8
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_69
jmp _call_label_ciao__ciao__ciao_73
_call_label_ciao__ciao__ciao_69:
movq $1, %r10
imulq $8, %r10
movq %r10, %r9
addq $16, %r9
movq 32(%rsp), %r10
movq %r10, %r10
addq %r9, %r10
movq 0(%r10), %r9
movq %r9, %r9
sarq $1, %r9
movq 80(%rsp), %r10
movq %r10, %rsi
movq %rsi, %rsi
salq $1, %rsi
movq %rsi, %rsi
addq $1, %rsi
movq 80(%rsp), %r10
cmpq %r9, %r10
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_70
jmp _call_label_ciao__ciao__ciao_73
_call_label_ciao__ciao__ciao_70:
jmp _call_label_ciao__ciao__ciao_71
_call_label_ciao__ciao__ciao_71:
movq $0, %r9
movq 32(%rsp), %r10
movq %r10, %r10
addq $24, %r10
movq 0(%r10), %r10
movq %r10, %r10
movq %r10, 72(%rsp)
movq 72(%rsp), %r10
sarq $1, %r10
movq %r10, 72(%rsp)
movq $1, %r10
movq %r10, 56(%rsp)
movq 56(%rsp), %r10
movq %r10, %r10
movq %r10, 56(%rsp)
movq 56(%rsp), %rsi
movq 72(%rsp), %r10
imulq %r10, %rsi
movq %rsi, 56(%rsp)
movq %r8, %r8
movq 56(%rsp), %r10
imulq %r10, %r8
movq %r9, %r9
addq %r8, %r9
movq %r9, %r9
movq 80(%rsp), %r10
addq %r10, %r9
movq %r9, %r8
imulq $8, %r8
movq %r8, %r8
addq $32, %r8
movq 32(%rsp), %r10
movq %r10, %r10
addq %r8, %r10
movq $1, 0(%r10)
movq %rdx, %r8
movq %r8, %r8
sarq $1, %r8
movq $3, %r9
movq %r9, %r9
sarq $1, %r9
movq %r8, %rdx
addq %r9, %rdx
movq %rdx, %rdx
salq $1, %rdx
movq %rdx, %rdx
addq $1, %rdx
jmp _call_label_ciao__ciao__ciao_66
_call_label_ciao__ciao__ciao_72:
movq %rcx, %r8
movq %r8, %r8
sarq $1, %r8
movq $3, %r9
movq %r9, %r9
sarq $1, %r9
movq %r8, %rcx
addq %r9, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
jmp _call_label_ciao__ciao__ciao_64
_call_label_ciao__ciao__ciao_73:
movq $0, %rdi
call array_tensor_error_null
jmp _call_label_ciao__ciao__ciao_71
_call_label_ciao__ciao__ciao_74:
movq $1, %r11
jmp _call_label_ciao__ciao__ciao_62
_call_label_ciao__ciao__ciao_75:
movq %rdx, %r8
movq %r8, %r8
sarq $1, %r8
movq 16(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
cmpq %r9, %r8
sete %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
cmpq $1, %r8
je _call_label_ciao__ciao__ciao_74
jmp _call_label_ciao__ciao__ciao_31
_call_label_ciao__ciao__ciao_76:
movq %rcx, %r8
movq %r8, %r8
sarq $1, %r8
movq 24(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
cmpq %r9, %r8
sete %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
cmpq $1, %r8
je _call_label_ciao__ciao__ciao_75
jmp _call_label_ciao__ciao__ciao_31
_call_label_ciao__ciao__ciao_77:
movq $0, %r10
imulq $8, %r10
movq %r10, %r11
addq $16, %r11
movq 48(%rsp), %r10
movq %r10, %r10
addq %r11, %r10
movq 0(%r10), %r10
movq %r10, 24(%rsp)
movq $1, %r10
imulq $8, %r10
movq %r10, %r11
addq $16, %r11
movq 48(%rsp), %r10
movq %r10, %r10
addq %r11, %r10
movq 0(%r10), %r10
movq %r10, 8(%rsp)
movq $0, %r10
imulq $8, %r10
movq %r10, %r11
addq $16, %r11
movq 40(%rsp), %r10
movq %r10, %r10
addq %r11, %r10
movq 0(%r10), %r11
movq $1, %r10
imulq $8, %r10
movq %r10, %r8
addq $16, %r8
movq 40(%rsp), %r10
movq %r10, %r10
addq %r8, %r10
movq 0(%r10), %r10
movq %r10, 16(%rsp)
movq $0, %r10
imulq $8, %r10
movq %r10, %r8
addq $16, %r8
movq 32(%rsp), %r10
movq %r10, %r10
addq %r8, %r10
movq 0(%r10), %rcx
movq $1, %r10
imulq $8, %r10
movq %r10, %r8
addq $16, %r8
movq 32(%rsp), %r10
movq %r10, %r10
addq %r8, %r10
movq 0(%r10), %rdx
movq 8(%rsp), %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
movq %r11, %r9
movq %r9, %r9
sarq $1, %r9
cmpq %r9, %r8
sete %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
cmpq $1, %r8
je _call_label_ciao__ciao__ciao_76
jmp _call_label_ciao__ciao__ciao_31
_totalSum:
subq $264, %rsp
movq %rdi, %r11
_call_label_ciao__ciao__ciao__ciao_78:
jmp _call_label_ciao__ciao__ciao__ciao_90
_call_label_ciao__ciao__ciao__ciao_79:
movq 8(%rsp), %r10
movq %r10, %rax
addq $264, %rsp
retq
_call_label_ciao__ciao__ciao__ciao_80:
movq 16(%rsp), %r10
movq %r10, %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq $3, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq %rdx, %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
addq %rcx, %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
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
jmp _call_label_ciao__ciao__ciao__ciao_81
_call_label_ciao__ciao__ciao__ciao_81:
movq 16(%rsp), %r10
movq %r10, %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq 24(%rsp), %r10
movq %r10, %rcx
movq %rcx, %rcx
sarq $1, %rcx
cmpq %rcx, %rdx
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %rdx
movq %rdx, %rdx
sarq $1, %rdx
cmpq $1, %rdx
je _call_label_ciao__ciao__ciao__ciao_82
jmp _call_label_ciao__ciao__ciao__ciao_79
_call_label_ciao__ciao__ciao__ciao_82:
movq $1, %r9
jmp _call_label_ciao__ciao__ciao__ciao_83
_call_label_ciao__ciao__ciao__ciao_83:
movq %r9, %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq %r8, %rcx
movq %rcx, %rcx
sarq $1, %rcx
cmpq %rcx, %rdx
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %rdx
movq %rdx, %rdx
sarq $1, %rdx
cmpq $1, %rdx
je _call_label_ciao__ciao__ciao__ciao_84
jmp _call_label_ciao__ciao__ciao__ciao_80
_call_label_ciao__ciao__ciao__ciao_84:
movq 16(%rsp), %r10
movq %r10, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq %r9, %r10
movq %r10, 32(%rsp)
movq 32(%rsp), %r10
movq %r10, %r10
movq %r10, 32(%rsp)
movq 32(%rsp), %r10
sarq $1, %r10
movq %r10, 32(%rsp)
movq $0, %rsi
cmpq $0, %r11
sete %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao__ciao_89
jmp _call_label_ciao__ciao__ciao__ciao_85
_call_label_ciao__ciao__ciao__ciao_85:
movq $0, %r10
imulq $8, %r10
movq %r10, %r10
addq $16, %r10
movq %r11, %rdx
addq %r10, %rdx
movq 0(%rdx), %r10
movq %r10, %r10
sarq $1, %r10
movq %rcx, %rsi
movq %rsi, %rsi
salq $1, %rsi
movq %rsi, %rsi
addq $1, %rsi
cmpq %r10, %rcx
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao__ciao_86
jmp _call_label_ciao__ciao__ciao__ciao_89
_call_label_ciao__ciao__ciao__ciao_86:
movq $1, %r10
imulq $8, %r10
movq %r10, %r10
addq $16, %r10
movq %r11, %rdx
addq %r10, %rdx
movq 0(%rdx), %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq 32(%rsp), %r10
movq %r10, %rsi
movq %rsi, %rsi
salq $1, %rsi
movq %rsi, %rsi
addq $1, %rsi
movq 32(%rsp), %r10
cmpq %rdx, %r10
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao__ciao_87
jmp _call_label_ciao__ciao__ciao__ciao_89
_call_label_ciao__ciao__ciao__ciao_87:
jmp _call_label_ciao__ciao__ciao__ciao_88
_call_label_ciao__ciao__ciao__ciao_88:
movq $0, %rdx
movq %r11, %r10
addq $24, %r10
movq 0(%r10), %r10
movq %r10, %rsi
sarq $1, %rsi
movq $1, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
movq %r10, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
imulq %rsi, %r10
movq %r10, 0(%rsp)
movq %rcx, %rcx
movq 0(%rsp), %r10
imulq %r10, %rcx
movq %rdx, %rdx
addq %rcx, %rdx
movq %rdx, %rdx
movq 32(%rsp), %r10
addq %r10, %rdx
movq %rdx, %r10
imulq $8, %r10
movq %r10, %r10
addq $32, %r10
movq %r11, %rcx
addq %r10, %rcx
movq 0(%rcx), %r10
movq 8(%rsp), %rcx
movq %rcx, %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq %r10, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq %rdx, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
addq %rcx, %r10
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
movq %r9, %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq $3, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq %rdx, %r9
addq %rcx, %r9
movq %r9, %r9
salq $1, %r9
movq %r9, %r9
addq $1, %r9
jmp _call_label_ciao__ciao__ciao__ciao_83
_call_label_ciao__ciao__ciao__ciao_89:
movq $0, %rdi
call array_tensor_error_null
jmp _call_label_ciao__ciao__ciao__ciao_88
_call_label_ciao__ciao__ciao__ciao_90:
movq $0, %r10
imulq $8, %r10
movq %r10, %r8
addq $16, %r8
movq %r11, %r10
addq %r8, %r10
movq 0(%r10), %r10
movq %r10, 24(%rsp)
movq $1, %r10
imulq $8, %r10
movq %r10, %r8
addq $16, %r8
movq %r11, %r10
addq %r8, %r10
movq 0(%r10), %r8
movq $1, %r10
movq %r10, 16(%rsp)
movq $1, %r10
movq %r10, 8(%rsp)
jmp _call_label_ciao__ciao__ciao__ciao_81
