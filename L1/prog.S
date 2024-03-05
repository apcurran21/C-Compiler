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
jmp _myLabel1_global_1
_myLabel1_global_1:
movq $3, %r10
sarq $1, %r10
movq %r10, %r10
movq %r10, %r10
addq $1, %r10
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
movq $16, %r8
movq $1, %r10
imulq $0, %r10
movq %r10, %r10
imulq $8, %r10
movq %r8, %r8
addq %r10, %r8
movq %r11, %r10
addq %r8, %r10
movq 0(%r10), %r10
movq %r10, %rdi
call print
addq $8, %rsp
retq
