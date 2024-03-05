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
movq $1, %r10
movq $2, %r11
jmp _myLabel1_global_1
_myLabel1_global_1:
movq %r10, %r10
addq %r11, %r10
cmpq $1, %r10
setg %r11b
movzbq %r11b, %r11
cmpq $1, %r11
je _true_global_3
jmp _false_global_4
_false_global_4:
retq
_true_global_3:
movq %r10, %rdi
call print
retq
