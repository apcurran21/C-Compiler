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
subq $16, %rsp
movq $1, %r10
movq $2, %r11
movq $_ret_main_global_0, -8(%rsp)
movq %r10, %rdi
movq %r11, %rsi
movq $3, %rdx
subq $8, %rsp
jmp _myF
_ret_main_global_0:
movq %rax, %r10
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
movq $_ret_main_global_1, -8(%rsp)
movq 8(%rsp), %r10
movq %r10, %rdi
call print
_ret_main_global_1:
movq $_ret_main_global_2, -8(%rsp)
movq 8(%rsp), %r10
movq %r10, %rdi
movq $1, %rsi
call allocate
_ret_main_global_2:
movq %rax, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
movq %r10, %r10
addq $8, %r10
movq 0(%r10), %r10
movq $_ret_main_global_3, -8(%rsp)
movq %r10, %rdi
call print
_ret_main_global_3:
movq $_ret_main_global_4, -8(%rsp)
movq 0(%rsp), %r10
movq %r10, %rdi
call print
_ret_main_global_4:
movq $0, %rax
addq $16, %rsp
retq
_myF:
movq %rdi, %r11
movq %rsi, %r8
movq %rdx, %r10
movq %r11, %r11
addq %r8, %r11
movq %r11, %r11
addq %r10, %r11
movq %r11, %rax
retq
