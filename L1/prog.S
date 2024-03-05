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
_NNNNNNNNN_global_0:
jmp _entry_global_1
_true_global_2:
movq $1, %rdi
call print
retq
_myLabel1_global_3:
jmp _true_global_2
_entry_global_1:
jmp _myLabel1_global_3
