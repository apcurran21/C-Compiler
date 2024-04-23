.text
.globl go
go:
pushq %rbx
pushq %rbp
pushq %r12
pushq %r13
pushq %r14
pushq %r15
call _go
popq %r15
popq %r14
popq %r13
popq %r12
popq %rbp
popq %rbx
retq
_go:
subq $8, %rsp
movq $5, %rdi
movq $5, %rsi
call allocate
movq %rax, %r10
movq %r10, 0(%rsp)
movq 0(%rsp), %r10
movq %r10, %rdi
call print
movq 0(%rsp), %r10
movq %r10, %rdi
movq $0, %rsi
movq $_checkArray_ret, -8(%rsp)
subq $8, %rsp
jmp _checkArray
_checkArray_ret:
movq %rax, %r10
movq %r10, %rdi
movq $_printValue_ret, -8(%rsp)
subq $8, %rsp
jmp _printValue
_printValue_ret:
movq $5, %rdi
movq $0, %rsi
movq $_checkArray_ret2, -8(%rsp)
subq $8, %rsp
jmp _checkArray
_checkArray_ret2:
movq %rax, %r10
movq %r10, %rdi
movq $_printValue_ret2, -8(%rsp)
subq $8, %rsp
jmp _printValue
_printValue_ret2:
addq $8, %rsp
retq
_checkArray:
movq %rdi, %r8
movq %rsi, %r11
movq %r8, %r10
andq $1, %r10
cmpq $0, %r10
je _isAnArray
jmp _isAnInt
_isAnInt:
movq $1, %rax
retq
_isAnArray:
movq %r11, %r10
imulq $8, %r10
addq $8, %r10
movq %r10, %r10
addq %r8, %r10
movq 0(%r10), %r10
movq %r10, %rdi
call print
movq $0, %rax
retq
_printValue:
movq %rdi, %r10
salq $1, %r10
inc %r10
movq %r10, %rdi
call print
retq
