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
_new_label_ciao_0_global_0:
movq $0, %r10
movq %r10, 56(%rsp)
movq $0, %r10
movq %r10, 40(%rsp)
movq $0, %r10
movq %r10, 48(%rsp)
movq $601, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
sarq $1, %r10
movq 8(%rsp), %r10
movq %r10, %r10
sarq $1, %r10
movq %r10, %r11
movq %r11, %r11
imulq %r10, %r11
movq %r11, %r11
addq $2, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 48(%rsp)
movq 48(%rsp), %r10
movq %r10, %r11
addq $8, %r11
movq 8(%rsp), %r10
movq %r10, 0(%r11)
movq 48(%rsp), %r10
movq %r10, %r11
addq $16, %r11
movq 8(%rsp), %r10
movq %r10, 0(%r11)
movq 8(%rsp), %r10
movq %r10, %r10
sarq $1, %r10
movq 8(%rsp), %r10
movq %r10, %r10
sarq $1, %r10
movq %r10, %r11
movq %r11, %r11
imulq %r10, %r11
movq %r11, %r11
addq $2, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 40(%rsp)
movq 40(%rsp), %r10
movq %r10, %r11
addq $8, %r11
movq 8(%rsp), %r10
movq %r10, 0(%r11)
movq 40(%rsp), %r10
movq %r10, %r11
addq $16, %r11
movq 8(%rsp), %r10
movq %r10, 0(%r11)
movq 8(%rsp), %r10
movq %r10, %r10
sarq $1, %r10
movq 8(%rsp), %r10
movq %r10, %r10
sarq $1, %r10
movq %r10, %r11
movq %r11, %r11
imulq %r10, %r11
movq %r11, %r11
addq $2, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 56(%rsp)
movq 56(%rsp), %r10
movq %r10, %r11
addq $8, %r11
movq 8(%rsp), %r10
movq %r10, 0(%r11)
movq 56(%rsp), %r10
movq %r10, %r11
addq $16, %r11
movq 8(%rsp), %r10
movq %r10, 0(%r11)
movq $9, %r10
movq %r10, 0(%rsp)
movq $9, %r10
movq %r10, 16(%rsp)
movq $1, %r10
movq %r10, 24(%rsp)
jmp _new_label0_global_1
_new_label0_global_1:
movq 24(%rsp), %r10
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
je _body1_global_3
jmp _leave_global_4
_body1_global_3:
movq $1, %r10
movq %r10, 32(%rsp)
jmp _new_label1_global_6
_new_label1_global_6:
movq 32(%rsp), %r10
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
je _body2_global_8
jmp _endBody1_global_9
_body2_global_8:
movq 48(%rsp), %r10
movq %r10, %rdi
movq 40(%rsp), %r10
movq %r10, %rsi
movq 56(%rsp), %r10
movq %r10, %rdx
movq 24(%rsp), %r10
movq %r10, %rcx
movq 32(%rsp), %r10
movq %r10, %r8
movq $_ret_main_global_11, -8(%rsp)
subq $8, %rsp
jmp _computeAndPrint
_ret_main_global_11:
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
jmp _new_label1_global_6
_endBody1_global_9:
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
jmp _new_label0_global_1
_leave_global_4:
addq $456, %rsp
retq
_computeAndPrint:
subq $200, %rsp
movq %rdi, %r10
movq %r10, 8(%rsp)
movq %rsi, %r10
movq %r10, 0(%rsp)
movq %rdx, %r10
movq %r10, 16(%rsp)
movq %rcx, %r11
movq %r8, %r10
movq %r10, 24(%rsp)
_new_label0_global_16:
movq 8(%rsp), %r10
movq %r10, %rdi
movq %r11, %rsi
movq $_ret_computeAndPrint_global_17, -8(%rsp)
subq $8, %rsp
jmp _initMatrix
_ret_computeAndPrint_global_17:
movq 0(%rsp), %r10
movq %r10, %rdi
movq 24(%rsp), %r10
movq %r10, %rsi
movq $_ret_computeAndPrint_global_18, -8(%rsp)
subq $8, %rsp
jmp _initMatrix
_ret_computeAndPrint_global_18:
movq 8(%rsp), %r10
movq %r10, %rdi
movq 0(%rsp), %r10
movq %r10, %rsi
movq 16(%rsp), %r10
movq %r10, %rdx
movq $_ret_computeAndPrint_global_19, -8(%rsp)
subq $8, %rsp
jmp _matrixMultiplication
_ret_computeAndPrint_global_19:
movq 8(%rsp), %r10
movq %r10, %rdi
movq $_ret_computeAndPrint_global_20, -8(%rsp)
subq $8, %rsp
jmp _totalSum
_ret_computeAndPrint_global_20:
movq %rax, %r10
movq %r10, %rdi
call print
movq 0(%rsp), %r10
movq %r10, %rdi
movq $_ret_computeAndPrint_global_21, -8(%rsp)
subq $8, %rsp
jmp _totalSum
_ret_computeAndPrint_global_21:
movq %rax, %r10
movq %r10, %rdi
call print
movq 16(%rsp), %r10
movq %r10, %rdi
movq $_ret_computeAndPrint_global_22, -8(%rsp)
subq $8, %rsp
jmp _totalSum
_ret_computeAndPrint_global_22:
movq %rax, %r10
movq %r10, %rdi
call print
addq $200, %rsp
retq
_initMatrix:
subq $200, %rsp
movq %rdi, %r10
movq %r10, 16(%rsp)
movq %rsi, %r10
movq %r10, 8(%rsp)
_new_label_ciao_5_global_23:
movq $8, %rdx
movq 16(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %r10
movq %r10, 24(%rsp)
movq $16, %rdx
movq 16(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %r8
movq $1, %r11
jmp _new_label0_global_24
_new_label0_global_24:
movq %r11, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq 24(%rsp), %r10
movq %r10, %r10
movq %r10, %r10
sarq $1, %r10
cmpq %r10, %rcx
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %rcx
movq %rcx, %rcx
sarq $1, %rcx
cmpq $1, %rcx
je _outerBody_global_26
jmp _leave_global_27
_outerBody_global_26:
movq $1, %r9
jmp _new_label1_global_29
_new_label1_global_29:
movq %r9, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq %r8, %r10
movq %r10, %r10
sarq $1, %r10
cmpq %r10, %rcx
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %rcx
movq %rcx, %rcx
sarq $1, %rcx
cmpq $1, %rcx
je _innerBody_global_31
jmp _endOuterBody_global_32
_innerBody_global_31:
movq 8(%rsp), %r10
movq %r10, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq %r11, %r10
movq %r10, %r10
sarq $1, %r10
movq %rcx, %rcx
addq %r10, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
movq %rcx, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq %r9, %r10
movq %r10, %r10
sarq $1, %r10
movq %rcx, %rcx
addq %r10, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
movq %r11, %rsi
movq %rsi, %rsi
sarq $1, %rsi
movq %r9, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
movq %r10, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
sarq $1, %r10
movq %r10, 0(%rsp)
movq $0, %r10
movq 16(%rsp), %r10
cmpq $0, %r10
sete %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _new_label_ciao_0_global_34
jmp _new_label_ciao_1_global_35
_new_label_ciao_0_global_34:
movq $0, %rdi
call array_tensor_error_null
jmp _new_label_ciao_4_global_37
_new_label_ciao_4_global_37:
movq 16(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq 16(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq $0, %rdx
movq %rsi, %rsi
movq %rsi, %rsi
imulq %r10, %rsi
movq %rdx, %rdx
addq %rsi, %rdx
movq 0(%rsp), %r10
movq %r10, %rsi
movq %rdx, %rdx
addq %rsi, %rdx
movq %rdx, %rdx
imulq $8, %rdx
movq %rdx, %rdx
addq $24, %rdx
movq 16(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq %rcx, 0(%r10)
movq %r9, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq $3, %r10
movq %r10, %r10
sarq $1, %r10
movq %rcx, %r9
addq %r10, %r9
movq %r9, %r9
salq $1, %r9
movq %r9, %r9
addq $1, %r9
jmp _new_label1_global_29
_new_label_ciao_1_global_35:
movq $8, %rdx
movq 16(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq %rsi, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
cmpq %rdx, %rsi
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _new_label_ciao_2_global_41
jmp _new_label_ciao_0_global_34
_new_label_ciao_2_global_41:
movq $16, %rdx
movq 16(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq 0(%rsp), %r10
movq %r10, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq 0(%rsp), %r10
cmpq %rdx, %r10
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _new_label_ciao_3_global_44
jmp _new_label_ciao_0_global_34
_new_label_ciao_3_global_44:
jmp _new_label_ciao_4_global_37
_endOuterBody_global_32:
movq %r11, %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq $3, %r10
movq %r10, %r10
sarq $1, %r10
movq %rcx, %r11
addq %r10, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
jmp _new_label0_global_24
_leave_global_27:
addq $200, %rsp
retq
_matrixMultiplication:
subq $456, %rsp
movq %rdi, %r10
movq %r10, 56(%rsp)
movq %rsi, %r10
movq %r10, 48(%rsp)
movq %rdx, %r10
movq %r10, 40(%rsp)
_new_label_ciao_25_global_51:
movq $8, %rsi
movq 56(%rsp), %r10
movq %r10, %rcx
addq %rsi, %rcx
movq 0(%rcx), %r10
movq %r10, 32(%rsp)
movq $16, %rsi
movq 56(%rsp), %r10
movq %r10, %rcx
addq %rsi, %rcx
movq 0(%rcx), %r10
movq %r10, 24(%rsp)
movq $8, %rsi
movq 48(%rsp), %r10
movq %r10, %rcx
addq %rsi, %rcx
movq 0(%rcx), %r8
movq $16, %rsi
movq 48(%rsp), %r10
movq %r10, %rcx
addq %rsi, %rcx
movq 0(%rcx), %r10
movq %r10, 16(%rsp)
movq $8, %rsi
movq 40(%rsp), %r10
movq %r10, %rcx
addq %rsi, %rcx
movq 0(%rcx), %r11
movq $16, %rsi
movq 40(%rsp), %r10
movq %r10, %rcx
addq %rsi, %rcx
movq 0(%rcx), %rcx
movq 24(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq %r8, %r8
movq %r8, %r8
sarq $1, %r8
cmpq %r8, %r9
sete %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
cmpq $1, %r9
je _go1_global_52
jmp _leave_global_53
_go1_global_52:
movq %r11, %r9
movq %r9, %r9
sarq $1, %r9
movq 32(%rsp), %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
cmpq %r8, %r9
sete %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
cmpq $1, %r9
je _go2_global_55
jmp _leave_global_53
_go2_global_55:
movq %rcx, %r9
movq %r9, %r9
sarq $1, %r9
movq 16(%rsp), %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
cmpq %r8, %r9
sete %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
cmpq $1, %r9
je _go_global_58
jmp _leave_global_53
_go_global_58:
movq $1, %r10
jmp _new_label0_global_61
_new_label0_global_61:
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq 32(%rsp), %r11
movq %r11, %r8
movq %r8, %r8
sarq $1, %r8
cmpq %r8, %r9
setl %r11b
movzbq %r11b, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %r9
movq %r9, %r9
sarq $1, %r9
cmpq $1, %r9
je _body1_init_global_63
jmp _done_init_global_64
_body1_init_global_63:
movq $1, %r11
jmp _new_label1_global_66
_new_label1_global_66:
movq %r11, %r9
movq %r9, %r9
sarq $1, %r9
movq 16(%rsp), %r8
movq %r8, %r8
movq %r8, %r8
sarq $1, %r8
cmpq %r8, %r9
setl %r8b
movzbq %r8b, %r8
movq %r8, %r8
salq $1, %r8
movq %r8, %r8
addq $1, %r8
movq %r8, %r9
movq %r9, %r9
sarq $1, %r9
cmpq $1, %r9
je _body2_init_global_68
jmp _endBody1_init_global_69
_body2_init_global_68:
movq $1, %rdx
jmp _new_label2_global_71
_new_label2_global_71:
movq %rdx, %r9
movq %r9, %r9
sarq $1, %r9
movq 24(%rsp), %r8
movq %r8, %r8
movq %r8, %r8
sarq $1, %r8
cmpq %r8, %r9
setl %r8b
movzbq %r8b, %r8
movq %r8, %r8
salq $1, %r8
movq %r8, %r8
addq $1, %r8
movq %r8, %r9
movq %r9, %r9
sarq $1, %r9
cmpq $1, %r9
je _body3_init_global_73
jmp _endBody2_init_global_74
_body3_init_global_73:
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
movq %r11, %r9
movq %r9, %r9
sarq $1, %r9
movq $0, %rcx
movq 40(%rsp), %rcx
cmpq $0, %rcx
sete %cl
movzbq %cl, %rcx
cmpq $1, %rcx
je _new_label_ciao_0_global_76
jmp _new_label_ciao_1_global_77
_new_label_ciao_0_global_76:
movq $0, %rdi
call array_tensor_error_null
jmp _new_label_ciao_4_global_79
_new_label_ciao_4_global_79:
movq 40(%rsp), %rcx
movq %rcx, %rcx
addq $8, %rcx
movq 0(%rcx), %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq 40(%rsp), %rcx
movq %rcx, %rcx
addq $16, %rcx
movq 0(%rcx), %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq $0, %rsi
movq %r8, %r8
movq %r8, %r8
imulq %rcx, %r8
movq %rsi, %rsi
addq %r8, %rsi
movq %r9, %r8
movq %rsi, %rsi
addq %r8, %rsi
movq %rsi, %r8
imulq $8, %r8
movq %r8, %r8
addq $24, %r8
movq 40(%rsp), %r9
movq %r9, %r9
addq %r8, %r9
movq $1, 0(%r9)
movq %rdx, %r9
movq %r9, %r9
sarq $1, %r9
movq $3, %r8
movq %r8, %r8
sarq $1, %r8
movq %r9, %rdx
addq %r8, %rdx
movq %rdx, %rdx
salq $1, %rdx
movq %rdx, %rdx
addq $1, %rdx
jmp _new_label2_global_71
_new_label_ciao_1_global_77:
movq $8, %rsi
movq 40(%rsp), %rcx
movq %rcx, %rcx
addq %rsi, %rcx
movq 0(%rcx), %rsi
movq %rsi, %rsi
sarq $1, %rsi
movq %r8, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
cmpq %rsi, %r8
setl %cl
movzbq %cl, %rcx
cmpq $1, %rcx
je _new_label_ciao_2_global_83
jmp _new_label_ciao_0_global_76
_new_label_ciao_2_global_83:
movq $16, %rsi
movq 40(%rsp), %rcx
movq %rcx, %rcx
addq %rsi, %rcx
movq 0(%rcx), %rsi
movq %rsi, %rsi
sarq $1, %rsi
movq %r9, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
cmpq %rsi, %r9
setl %cl
movzbq %cl, %rcx
cmpq $1, %rcx
je _new_label_ciao_3_global_86
jmp _new_label_ciao_0_global_76
_new_label_ciao_3_global_86:
jmp _new_label_ciao_4_global_79
_endBody2_init_global_74:
movq %r11, %r9
movq %r9, %r9
sarq $1, %r9
movq $3, %r8
movq %r8, %r8
sarq $1, %r8
movq %r9, %r11
addq %r8, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
jmp _new_label1_global_66
_endBody1_init_global_69:
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq $3, %r8
movq %r8, %r8
sarq $1, %r8
movq %r9, %r10
addq %r8, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
jmp _new_label0_global_61
_done_init_global_64:
movq $1, %r10
movq %r10, 8(%rsp)
jmp _new_label3_global_95
_new_label3_global_95:
movq 8(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq 32(%rsp), %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
cmpq %r8, %r9
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
je _body1_global_97
jmp _leave_global_53
_body1_global_97:
movq $1, %r10
movq %r10, 0(%rsp)
jmp _new_label4_global_100
_new_label4_global_100:
movq 0(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq 16(%rsp), %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
cmpq %r8, %r9
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
je _body2_global_102
jmp _endBody1_global_103
_body2_global_102:
movq $1, %rdx
jmp _new_label5_global_105
_new_label5_global_105:
movq %rdx, %r9
movq %r9, %r9
sarq $1, %r9
movq 24(%rsp), %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
cmpq %r8, %r9
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
je _body3_global_107
jmp _endBody2_global_108
_body3_global_107:
movq 8(%rsp), %r10
movq %r10, %r11
movq %r11, %r11
sarq $1, %r11
movq %rdx, %r10
movq %r10, %r10
sarq $1, %r10
movq $0, %r9
movq 56(%rsp), %r8
cmpq $0, %r8
sete %r8b
movzbq %r8b, %r8
cmpq $1, %r8
je _new_label_ciao_5_global_110
jmp _new_label_ciao_6_global_111
_new_label_ciao_5_global_110:
movq $0, %rdi
call array_tensor_error_null
jmp _new_label_ciao_9_global_113
_new_label_ciao_9_global_113:
movq 56(%rsp), %r8
movq %r8, %rcx
addq $8, %rcx
movq 0(%rcx), %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq 56(%rsp), %r8
movq %r8, %rcx
addq $16, %rcx
movq 0(%rcx), %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq $0, %rsi
movq %r11, %r8
movq %r8, %r8
imulq %rcx, %r8
movq %rsi, %rsi
addq %r8, %rsi
movq %r10, %r8
movq %rsi, %rsi
addq %r8, %rsi
movq %rsi, %r8
imulq $8, %r8
movq %r8, %r8
addq $24, %r8
movq 56(%rsp), %r10
movq %r10, %r9
addq %r8, %r9
movq 0(%r9), %r10
movq %rdx, %r8
movq %r8, %r8
sarq $1, %r8
movq 0(%rsp), %r11
movq %r11, %r11
movq %r11, %r11
sarq $1, %r11
movq $0, %rcx
movq 48(%rsp), %r9
cmpq $0, %r9
sete %r9b
movzbq %r9b, %r9
cmpq $1, %r9
je _new_label_ciao_10_global_115
jmp _new_label_ciao_11_global_116
_new_label_ciao_10_global_115:
movq $0, %rdi
call array_tensor_error_null
jmp _new_label_ciao_14_global_118
_new_label_ciao_14_global_118:
movq 48(%rsp), %r9
movq %r9, %rcx
addq $8, %rcx
movq 0(%rcx), %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq 48(%rsp), %r9
movq %r9, %rcx
addq $16, %rcx
movq 0(%rcx), %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq $0, %rsi
movq %r8, %r8
movq %r8, %r8
imulq %rcx, %r8
movq %rsi, %rsi
addq %r8, %rsi
movq %r11, %r8
movq %rsi, %rsi
addq %r8, %rsi
movq %rsi, %r8
imulq $8, %r8
movq %r8, %r8
addq $24, %r8
movq 48(%rsp), %r11
movq %r11, %r9
addq %r8, %r9
movq 0(%r9), %r11
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq %r11, %r8
movq %r8, %r8
sarq $1, %r8
movq %r9, %r10
imulq %r8, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq 8(%rsp), %r11
movq %r11, %r8
movq %r8, %r8
sarq $1, %r8
movq 0(%rsp), %r11
movq %r11, %r11
movq %r11, %r11
sarq $1, %r11
movq $0, %rcx
movq 40(%rsp), %r9
cmpq $0, %r9
sete %r9b
movzbq %r9b, %r9
cmpq $1, %r9
je _new_label_ciao_15_global_120
jmp _new_label_ciao_16_global_121
_new_label_ciao_15_global_120:
movq $0, %rdi
call array_tensor_error_null
jmp _new_label_ciao_19_global_123
_new_label_ciao_19_global_123:
movq 40(%rsp), %r9
movq %r9, %rcx
addq $8, %rcx
movq 0(%rcx), %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq 40(%rsp), %r9
movq %r9, %rcx
addq $16, %rcx
movq 0(%rcx), %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq $0, %rsi
movq %r8, %r8
movq %r8, %r8
imulq %rcx, %r8
movq %rsi, %rsi
addq %r8, %rsi
movq %r11, %r8
movq %rsi, %rsi
addq %r8, %rsi
movq %rsi, %r8
imulq $8, %r8
movq %r8, %r8
addq $24, %r8
movq 40(%rsp), %r11
movq %r11, %r9
addq %r8, %r9
movq 0(%r9), %r11
movq %r11, %r9
movq %r9, %r9
sarq $1, %r9
movq $9, %r8
movq %r8, %r8
sarq $1, %r8
movq %r9, %r11
imulq %r8, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq %r11, %r9
movq %r9, %r9
sarq $1, %r9
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
movq %r9, %r11
addq %r8, %r11
movq %r11, %r11
salq $1, %r11
movq %r11, %r11
addq $1, %r11
movq 8(%rsp), %r10
movq %r10, %r8
movq %r8, %r8
sarq $1, %r8
movq 0(%rsp), %r10
movq %r10, %r10
movq %r10, %r10
sarq $1, %r10
movq $0, %rcx
movq 40(%rsp), %r9
cmpq $0, %r9
sete %r9b
movzbq %r9b, %r9
cmpq $1, %r9
je _new_label_ciao_20_global_125
jmp _new_label_ciao_21_global_126
_new_label_ciao_20_global_125:
movq $0, %rdi
call array_tensor_error_null
jmp _new_label_ciao_24_global_128
_new_label_ciao_24_global_128:
movq 40(%rsp), %r9
movq %r9, %rcx
addq $8, %rcx
movq 0(%rcx), %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq 40(%rsp), %r9
movq %r9, %rcx
addq $16, %rcx
movq 0(%rcx), %rcx
movq %rcx, %rcx
sarq $1, %rcx
movq $0, %rsi
movq %r8, %r8
movq %r8, %r8
imulq %rcx, %r8
movq %rsi, %rsi
addq %r8, %rsi
movq %r10, %r8
movq %rsi, %rsi
addq %r8, %rsi
movq %rsi, %r8
imulq $8, %r8
movq %r8, %r8
addq $24, %r8
movq 40(%rsp), %r10
movq %r10, %r9
addq %r8, %r9
movq %r11, 0(%r9)
movq %rdx, %r9
movq %r9, %r9
sarq $1, %r9
movq $3, %r8
movq %r8, %r8
sarq $1, %r8
movq %r9, %rdx
addq %r8, %rdx
movq %rdx, %rdx
salq $1, %rdx
movq %rdx, %rdx
addq $1, %rdx
jmp _new_label5_global_105
_new_label_ciao_6_global_111:
movq $8, %rsi
movq 56(%rsp), %r8
movq %r8, %rcx
addq %rsi, %rcx
movq 0(%rcx), %r8
movq %r8, %r8
sarq $1, %r8
movq %r11, %r9
movq %r9, %r9
salq $1, %r9
movq %r9, %r9
addq $1, %r9
cmpq %r8, %r11
setl %r8b
movzbq %r8b, %r8
cmpq $1, %r8
je _new_label_ciao_7_global_132
jmp _new_label_ciao_5_global_110
_new_label_ciao_7_global_132:
movq $16, %rsi
movq 56(%rsp), %r8
movq %r8, %rcx
addq %rsi, %rcx
movq 0(%rcx), %r8
movq %r8, %r8
sarq $1, %r8
movq %r10, %r9
movq %r9, %r9
salq $1, %r9
movq %r9, %r9
addq $1, %r9
cmpq %r8, %r10
setl %r8b
movzbq %r8b, %r8
cmpq $1, %r8
je _new_label_ciao_8_global_135
jmp _new_label_ciao_5_global_110
_new_label_ciao_8_global_135:
jmp _new_label_ciao_9_global_113
_new_label_ciao_11_global_116:
movq $8, %rsi
movq 48(%rsp), %r9
movq %r9, %rcx
addq %rsi, %rcx
movq 0(%rcx), %r9
movq %r9, %r9
sarq $1, %r9
movq %r8, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
cmpq %r9, %r8
setl %r9b
movzbq %r9b, %r9
cmpq $1, %r9
je _new_label_ciao_12_global_140
jmp _new_label_ciao_10_global_115
_new_label_ciao_12_global_140:
movq $16, %rsi
movq 48(%rsp), %r9
movq %r9, %rcx
addq %rsi, %rcx
movq 0(%rcx), %r9
movq %r9, %r9
sarq $1, %r9
movq %r11, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
cmpq %r9, %r11
setl %r9b
movzbq %r9b, %r9
cmpq $1, %r9
je _new_label_ciao_13_global_143
jmp _new_label_ciao_10_global_115
_new_label_ciao_13_global_143:
jmp _new_label_ciao_14_global_118
_new_label_ciao_16_global_121:
movq $8, %rsi
movq 40(%rsp), %r9
movq %r9, %rcx
addq %rsi, %rcx
movq 0(%rcx), %r9
movq %r9, %r9
sarq $1, %r9
movq %r8, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
cmpq %r9, %r8
setl %r9b
movzbq %r9b, %r9
cmpq $1, %r9
je _new_label_ciao_17_global_148
jmp _new_label_ciao_15_global_120
_new_label_ciao_17_global_148:
movq $16, %rsi
movq 40(%rsp), %r9
movq %r9, %rcx
addq %rsi, %rcx
movq 0(%rcx), %r9
movq %r9, %r9
sarq $1, %r9
movq %r11, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
cmpq %r9, %r11
setl %r9b
movzbq %r9b, %r9
cmpq $1, %r9
je _new_label_ciao_18_global_151
jmp _new_label_ciao_15_global_120
_new_label_ciao_18_global_151:
jmp _new_label_ciao_19_global_123
_new_label_ciao_21_global_126:
movq $8, %rsi
movq 40(%rsp), %r9
movq %r9, %rcx
addq %rsi, %rcx
movq 0(%rcx), %r9
movq %r9, %r9
sarq $1, %r9
movq %r8, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
cmpq %r9, %r8
setl %r9b
movzbq %r9b, %r9
cmpq $1, %r9
je _new_label_ciao_22_global_156
jmp _new_label_ciao_20_global_125
_new_label_ciao_22_global_156:
movq $16, %rsi
movq 40(%rsp), %r9
movq %r9, %rcx
addq %rsi, %rcx
movq 0(%rcx), %r9
movq %r9, %r9
sarq $1, %r9
movq %r10, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
cmpq %r9, %r10
setl %r9b
movzbq %r9b, %r9
cmpq $1, %r9
je _new_label_ciao_23_global_159
jmp _new_label_ciao_20_global_125
_new_label_ciao_23_global_159:
jmp _new_label_ciao_24_global_128
_endBody2_global_108:
movq 0(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq $3, %r8
movq %r8, %r8
sarq $1, %r8
movq %r9, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
addq %r8, %r10
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
jmp _new_label4_global_100
_endBody1_global_103:
movq 8(%rsp), %r10
movq %r10, %r9
movq %r9, %r9
sarq $1, %r9
movq $3, %r8
movq %r8, %r8
sarq $1, %r8
movq %r9, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
addq %r8, %r10
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
jmp _new_label3_global_95
_leave_global_53:
addq $456, %rsp
retq
_totalSum:
subq $136, %rsp
movq %rdi, %r10
movq %r10, 8(%rsp)
_new_label_ciao_5_global_168:
movq $8, %rdx
movq 8(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %r8
movq $16, %rdx
movq 8(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %r11
movq $1, %r9
movq $1, %r10
movq %r10, 16(%rsp)
jmp _new_label0_global_169
_new_label0_global_169:
movq %r9, %rsi
movq %rsi, %rsi
sarq $1, %rsi
movq %r8, %rdx
movq %rdx, %rdx
sarq $1, %rdx
cmpq %rdx, %rsi
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %rsi
movq %rsi, %rsi
sarq $1, %rsi
cmpq $1, %rsi
je _outerBody_global_171
jmp _leave_global_172
_outerBody_global_171:
movq $1, %rcx
jmp _new_label1_global_174
_new_label1_global_174:
movq %rcx, %rsi
movq %rsi, %rsi
sarq $1, %rsi
movq %r11, %rdx
movq %rdx, %rdx
sarq $1, %rdx
cmpq %rdx, %rsi
setl %r10b
movzbq %r10b, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %rsi
movq %rsi, %rsi
sarq $1, %rsi
cmpq $1, %rsi
je _innerBody_global_176
jmp _endOuterBody_global_177
_innerBody_global_176:
movq %r9, %rsi
movq %rsi, %rsi
sarq $1, %rsi
movq %rcx, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
movq %r10, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
sarq $1, %r10
movq %r10, 0(%rsp)
movq $0, %rdx
movq 8(%rsp), %r10
cmpq $0, %r10
sete %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _new_label_ciao_0_global_179
jmp _new_label_ciao_1_global_180
_new_label_ciao_0_global_179:
movq $0, %rdi
call array_tensor_error_null
jmp _new_label_ciao_4_global_182
_new_label_ciao_4_global_182:
movq 8(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq 8(%rsp), %r10
movq %r10, %r10
addq $16, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq $0, %rdx
movq %rsi, %rsi
movq %rsi, %rsi
imulq %r10, %rsi
movq %rdx, %rdx
addq %rsi, %rdx
movq 0(%rsp), %r10
movq %r10, %rsi
movq %rdx, %rdx
addq %rsi, %rdx
movq %rdx, %rdx
imulq $8, %rdx
movq %rdx, %rdx
addq $24, %rdx
movq 8(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %r10
movq 16(%rsp), %rdx
movq %rdx, %rsi
movq %rsi, %rsi
sarq $1, %rsi
movq %r10, %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq %rsi, %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
addq %rdx, %r10
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
movq %rcx, %rsi
movq %rsi, %rsi
sarq $1, %rsi
movq $3, %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq %rsi, %rcx
addq %rdx, %rcx
movq %rcx, %rcx
salq $1, %rcx
movq %rcx, %rcx
addq $1, %rcx
jmp _new_label1_global_174
_new_label_ciao_1_global_180:
movq $8, %rdx
movq 8(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq %rsi, %rdx
movq %rdx, %rdx
salq $1, %rdx
movq %rdx, %rdx
addq $1, %rdx
cmpq %r10, %rsi
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _new_label_ciao_2_global_186
jmp _new_label_ciao_0_global_179
_new_label_ciao_2_global_186:
movq $16, %rdx
movq 8(%rsp), %r10
movq %r10, %r10
addq %rdx, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq 0(%rsp), %rdx
movq %rdx, %rdx
movq %rdx, %rdx
salq $1, %rdx
movq %rdx, %rdx
addq $1, %rdx
movq 0(%rsp), %rdx
cmpq %r10, %rdx
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _new_label_ciao_3_global_189
jmp _new_label_ciao_0_global_179
_new_label_ciao_3_global_189:
jmp _new_label_ciao_4_global_182
_endOuterBody_global_177:
movq %r9, %rsi
movq %rsi, %rsi
sarq $1, %rsi
movq $3, %rdx
movq %rdx, %rdx
sarq $1, %rdx
movq %rsi, %r9
addq %rdx, %r9
movq %r9, %r9
salq $1, %r9
movq %r9, %r9
addq $1, %r9
jmp _new_label0_global_169
_leave_global_172:
movq 16(%rsp), %r10
movq %r10, %rax
addq $136, %rsp
retq
