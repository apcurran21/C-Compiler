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
subq $8, %rsp
_entry_global_0:
movq $3, %r10
sarq $1, %r10
movq $5, %r11
sarq $1, %r11
movq %r10, %r10
movq %r10, %r10
imulq %r11, %r10
movq %r10, %r10
addq $2, %r10
movq %r10, %r10
salq $1, %r10
movq %r10, %r10
addq $1, %r10
movq %r10, %rdi
movq $1, %rsi
call allocate
movq %rax, %r11
movq %r11, %r10
addq $8, %r10
movq $3, 0(%r10)
movq %r11, %r10
addq $16, %r10
movq $5, 0(%r10)
movq %r11, %rdi
movq %r11, %rsi
movq $_ret_main_global_1, -8(%rsp)
subq $8, %rsp
jmp _myF
_ret_main_global_1:
movq %rax, %r10
movq %r10, %rdi
call print
addq $8, %rsp
retq
_myF:
movq %rdi, %r10
_entry_global_2:
movq $16, %r11
movq %r10, %r10
addq %r11, %r10
movq 0(%r10), %r10
movq %r10, %rax
retq
