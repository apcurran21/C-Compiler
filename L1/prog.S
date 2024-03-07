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
_entry_main_global_0:
movq $5, %r10
movq $7, %r11
movq $9, %r8
movq %r10, %rdi
movq %r11, %rsi
movq %r8, %rdx
movq $_ret_main_global_1, -8(%rsp)
subq $8, %rsp
jmp _f
_ret_main_global_1:
retq
_f:
movq %rdi, %r10
