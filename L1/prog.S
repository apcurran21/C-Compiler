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
_call_label0:
jmp _call_label1
_call_label1:
movq $_call_label2, -8(%rsp)
subq $8, %rsp
jmp _read_input_arr
_call_label2:
movq %rax, %r10
jmp _sort_arr
_call_label3:
movq %rax, %r10
movq %r10, %rdi
subq $8, %rsp
jmp _print_arr
_call_label4:
retq
_swap:
subq $8, %rsp
movq %rdi, %r11
movq %rsi, %r9
movq %rdx, %r8
_call_label_ciao_5:
jmp _call_label_ciao_6
_call_label_ciao_6:
movq $0, %rcx
movq $1, %r10
movq %rcx, %rcx
addq %r11, %rcx
movq %rcx, %r10
imulq $8, %r10
movq %r10, %r10
addq $16, %r10
movq %r8, %rcx
addq %r10, %rcx
movq 0(%rcx), %rdi
movq $0, %r10
movq $1, %rcx
movq %r10, %r10
addq %r9, %r10
movq %r10, %rcx
imulq $8, %rcx
movq %rcx, %rcx
addq $16, %rcx
movq %r8, %r10
addq %rcx, %r10
movq 0(%r10), %rcx
movq $0, %rdx
movq $1, %r10
movq %rdx, %rdx
addq %r9, %rdx
movq %rdx, %r9
imulq $8, %r9
movq %r9, %r9
addq $16, %r9
movq %r8, %r10
addq %r9, %r10
movq %rdi, 0(%r10)
movq $0, %r10
movq $1, %r9
movq %r10, %r10
addq %r11, %r10
movq %r10, %r11
imulq $8, %r11
movq %r11, %r11
addq $16, %r11
movq %r8, %r10
addq %r11, %r10
movq %rcx, 0(%r10)
addq $8, %rsp
retq
_sort_arr:
subq $200, %rsp
movq %rdi, %r10
movq %r10, 16(%rsp)
_call_label_ciao__ciao_7:
jmp _call_label_ciao__ciao_15
_call_label_ciao__ciao_8:
movq 16(%rsp), %r10
movq %r10, %rax
addq $200, %rsp
retq
_call_label_ciao__ciao_9:
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
subq $1, %r10
movq %r10, 8(%rsp)
jmp _call_label_ciao__ciao_10
_call_label_ciao__ciao_10:
movq $0, %r10
movq %r10, 0(%rsp)
movq 8(%rsp), %r10
cmpq $0, %r10
setle %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao_8
jmp _call_label_ciao__ciao_11
_call_label_ciao__ciao_11:
movq 0(%rsp), %r11
movq 8(%rsp), %r10
cmpq %r11, %r10
setle %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao_9
jmp _call_label_ciao__ciao_12
_call_label_ciao__ciao_12:
movq $0, %r11
movq $1, %r10
movq %r11, %r11
movq 0(%rsp), %r10
addq %r10, %r11
movq %r11, %r11
imulq $8, %r11
movq %r11, %r11
addq $16, %r11
movq 16(%rsp), %r10
movq %r10, %r10
addq %r11, %r10
movq 0(%r10), %r11
movq 0(%rsp), %r10
movq %r10, %r10
movq %r10, 24(%rsp)
movq 24(%rsp), %r10
addq $1, %r10
movq %r10, 24(%rsp)
movq $0, %r8
movq $1, %r10
movq %r8, %r8
movq 24(%rsp), %r10
addq %r10, %r8
movq %r8, %r8
imulq $8, %r8
movq %r8, %r8
addq $16, %r8
movq 16(%rsp), %r10
movq %r10, %r10
addq %r8, %r10
movq 0(%r10), %r10
cmpq %r11, %r10
setl %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao_13
jmp _call_label_ciao__ciao_14
_call_label_ciao__ciao_13:
movq 16(%rsp), %r10
movq %r10, %rdi
call print
movq 0(%rsp), %r10
movq %r10, %rdi
movq 24(%rsp), %r10
movq %r10, %rsi
movq 16(%rsp), %r10
movq %r10, %rdx
movq $_call_label_ciao__ciao_16, -8(%rsp)
subq $8, %rsp
jmp _swap
_call_label_ciao__ciao_16:
movq 16(%rsp), %r10
movq %r10, %rdi
call print
jmp _call_label_ciao__ciao_14
_call_label_ciao__ciao_14:
movq 0(%rsp), %r10
movq %r10, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
addq $1, %r10
movq %r10, 0(%rsp)
jmp _call_label_ciao__ciao_11
_call_label_ciao__ciao_15:
movq $0, %r10
imulq $8, %r10
movq %r10, %r11
addq $8, %r11
movq 16(%rsp), %r10
movq %r10, %r10
addq %r11, %r10
movq 0(%r10), %r10
movq %r10, %r10
sarq $1, %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
subq $1, %r10
movq %r10, 8(%rsp)
jmp _call_label_ciao__ciao_10
_read_input_arr:
subq $136, %rsp
_call_label_ciao__ciao__ciao_17:
jmp _call_label_ciao__ciao__ciao_21
_call_label_ciao__ciao__ciao_18:
movq 8(%rsp), %r10
movq %r10, %rax
addq $136, %rsp
retq
_call_label_ciao__ciao__ciao_19:
call input
movq %rax, %r8
movq $0, %r11
movq $1, %r10
movq %r11, %r11
movq 0(%rsp), %r10
addq %r10, %r11
movq %r11, %r11
imulq $8, %r11
movq %r11, %r11
addq $16, %r11
movq 8(%rsp), %r10
movq %r10, %r10
addq %r11, %r10
movq %r8, 0(%r10)
movq 0(%rsp), %r10
movq %r10, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
addq $1, %r10
movq %r10, 0(%rsp)
movq 8(%rsp), %r10
movq %r10, %rdi
call print
jmp _call_label_ciao__ciao__ciao_20
_call_label_ciao__ciao__ciao_20:
movq 0(%rsp), %r10
movq 16(%rsp), %r11
cmpq %r10, %r11
setle %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao_18
jmp _call_label_ciao__ciao__ciao_19
_call_label_ciao__ciao__ciao_21:
call input
movq %rax, %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
movq %r10, %r10
sarq $1, %r10
movq %r10, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %r10
addq $2, %r10
movq %r10, %rdi
movq $1, %rsi
call allocate
movq %rax, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq 16(%rsp), %r11
movq %r11, 0(%r10)
movq $0, %r10
imulq $8, %r10
movq %r10, %r11
addq $8, %r11
movq 8(%rsp), %r10
movq %r10, %r10
addq %r11, %r10
movq 0(%r10), %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
movq %r10, %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
sarq $1, %r10
movq %r10, 16(%rsp)
movq $0, %r10
movq %r10, 0(%rsp)
jmp _call_label_ciao__ciao__ciao_20
_print_arr:
subq $136, %rsp
movq %rdi, %r10
movq %r10, 0(%rsp)
_call_label_ciao__ciao__ciao__ciao_22:
jmp _call_label_ciao__ciao__ciao__ciao_26
_call_label_ciao__ciao__ciao__ciao_23:
addq $136, %rsp
retq
_call_label_ciao__ciao__ciao__ciao_24:
movq $0, %r11
movq $1, %r10
movq %r11, %r11
movq 8(%rsp), %r10
addq %r10, %r11
movq %r11, %r11
imulq $8, %r11
movq %r11, %r11
addq $16, %r11
movq 0(%rsp), %r10
movq %r10, %r10
addq %r11, %r10
movq 0(%r10), %r10
movq %r10, %rdi
call print
movq 8(%rsp), %r10
movq %r10, %r10
movq %r10, 8(%rsp)
movq 8(%rsp), %r10
addq $1, %r10
movq %r10, 8(%rsp)
jmp _call_label_ciao__ciao__ciao__ciao_25
_call_label_ciao__ciao__ciao__ciao_25:
movq 8(%rsp), %r10
movq 16(%rsp), %r11
cmpq %r10, %r11
setle %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _call_label_ciao__ciao__ciao__ciao_23
jmp _call_label_ciao__ciao__ciao__ciao_24
_call_label_ciao__ciao__ciao__ciao_26:
movq $0, %r10
imulq $8, %r10
movq %r10, %r11
addq $8, %r11
movq 0(%rsp), %r10
movq %r10, %r10
addq %r11, %r10
movq 0(%r10), %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
movq %r10, %r10
movq %r10, 16(%rsp)
movq 16(%rsp), %r10
sarq $1, %r10
movq %r10, 16(%rsp)
movq $0, %r10
movq %r10, 8(%rsp)
jmp _call_label_ciao__ciao__ciao__ciao_25
