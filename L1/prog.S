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
movq $3, %rdi
movq $3, %rsi
movq $_ret_main_global_1, -8(%rsp)
subq $8, %rsp
jmp _createTuple
_ret_main_global_1:
movq %rax, %r10
retq
_createTuple:
subq $72, %rsp
movq %rdi, %r10
movq %r10, 8(%rsp)
_entry_global_2:
movq $21, %r10
movq %r10, 0(%rsp)
movq $5, %rdi
movq $1, %rsi
call allocate
movq %rax, %r8
movq %r8, %r10
addq $8, %r10
movq $0, 0(%r10)
movq %r8, %r10
addq $8, %r10
movq $1, 0(%r10)
movq %r8, %r10
addq $8, %r10
movq 8(%rsp), %r11
movq %r11, 0(%r10)
movq %r8, %r11
addq $8, %r11
movq 0(%rsp), %r10
movq %r10, 0(%r11)
movq %r8, %rax
addq $72, %rsp
retq
