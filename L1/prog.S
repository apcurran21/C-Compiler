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
_entry_global_0:
movq $541, %rdi
movq $7919, %rsi
movq $7919, %rdx
movq $_ret_main_global_1, -8(%rsp)
subq $8, %rsp
jmp _gcd
_ret_main_global_1:
movq %rax, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %rdi
call print
retq
_gcd:
subq $8, %rsp
movq %rdi, %r10
movq %r10, 0(%rsp)
_entry_global_2:
movq 0(%rsp), %r10
cmpq $0, %r10
sete %r10b
movzbq %r10b, %r10
cmpq $1, %r10
je _initialConditionTrue_global_3
jmp _initialConditionFalse_global_4
_initialConditionFalse_global_4:
movq %r11, %rdi
movq 0(%rsp), %r10
movq %r10, %rsi
movq 0(%rsp), %r10
movq %r10, %rdx
movq $_ret_gcd_global_6, -8(%rsp)
subq $8, %rsp
jmp _mod
_ret_gcd_global_6:
movq %rax, %r11
movq 0(%rsp), %r10
movq %r10, %rdi
movq %r11, %rsi
movq %r11, %rdx
movq $_ret_gcd_global_7, -8(%rsp)
subq $8, %rsp
jmp _gcd
_ret_gcd_global_7:
movq %rax, %r10
movq %r10, %rax
addq $8, %rsp
retq
_initialConditionTrue_global_3:
movq %r11, %rax
addq $8, %rsp
retq
_mod:
movq %rdi, %r9
_entry_global_9:
movq $0, %r10
movq %rcx, %rax
jmp _while_global_10
_while_global_10:
movq %r9, %r8
imulq %r10, %r8
cmpq %rcx, %r8
setle %r11b
movzbq %r11b, %r11
cmpq $1, %r11
je _whileInto_global_12
jmp _whileBreak_global_13
_whileBreak_global_13:
movq %rax, %rax
retq
_whileInto_global_12:
movq %rcx, %rax
movq %rax, %rax
subq %r8, %rax
jmp _whileIncrement_global_16
_whileIncrement_global_16:
movq %r10, %r10
addq $1, %r10
jmp _while_global_10
