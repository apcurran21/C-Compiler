#include "L1.h"

namespace L1 {

    // Register Constructor
    Register::Register(RegisterID r) : ID(r) {}

    Integer::Integer(int value) : value(value) {}

    String::String(const std::string& value) : value(value) {}

    // Instruction_assignment Constructor
    Instruction_assignment::Instruction_assignment(Item *dst, Item *src) : s(src), d(dst) {}

    // incdec_instruction Constructor
    incdec_instruction::incdec_instruction(Item *reg, Item *method) : reg(reg), method(method) {}

    // at_instruction Constructor
    // at_instruction::at_instruction(Item *reg1, Item *reg2, Item *reg3, Integer *num) : reg1(reg1), reg2(reg2), reg3(reg3), num(num) {}

    // label_Instruction Constructor
    label_Instruction::label_Instruction(Item *label) : label(label) {}

    // goto_label_instruction Constructor
    goto_label_instruction::goto_label_instruction(Item *method, Item *label) : label_Instruction(label), method(method) {}

    // Call_Instruction Constructor
    Call_Instruction::Call_Instruction(Item *method) : method(method) {}

    // Call_tenserr_Instruction Constructor
    Call_tenserr_Instruction::Call_tenserr_Instruction(Item *F) : F(F) {
    }
    // Call_uN_Instruction Constructor
    Call_uN_Instruction::Call_uN_Instruction(Item *u, Item *N) : u(u), N(N) {}

    // Memory_assignment Constructor
    Memory_assignment::Memory_assignment(Item *dst, Item *method, Item *x, Item *M) : dst(dst), method(method), x(x), M(M) {}

    // Memory_arithmetic Constructor
    Memory_arithmetic::Memory_arithmetic(Item *dst, Item *method, Item *x, Item *instruction, Item *M) 
    : dst(dst), method(method), x(x), instruction(instruction), M(M) {}
    // cmp_Instruction Constructor
    cmp_Instruction::cmp_Instruction(Item *dst, Item *t1, Item *method, Item *t2) : dst(dst), t1(t1), method(method), t2(t2) {}

    // cjump_cmp_Instruction Constructor
    cjump_cmp_Instruction::cjump_cmp_Instruction(Item *t1, Item *method, Item *t2, Item *label) : t1(t1), method(method), t2(t2), label(label) {}

    // AOP_assignment Constructor
    AOP_assignment::AOP_assignment(Item *method, Item *dst, Item *src) : Instruction_assignment(dst, src), method(method) {}

    // SOP_assignment Constructor
    SOP_assignment::SOP_assignment(Item *method, Item *dst, Item *src) : Instruction_assignment(dst, src), method(method) {}

    Call_print_Instruction::Call_print_Instruction() {
    // Implementation details (if any)
    }

    Call_input_Instruction::Call_input_Instruction() {
    }

    Call_allocate_Instruction::Call_allocate_Instruction() {
    }

    Call_tuple_Instruction::Call_tuple_Instruction() {
    }

    w_increment_decrement::w_increment_decrement(Item *r, Item *symbol) 
        : r(r), symbol(symbol) {
    }

    w_atreg_assignment::w_atreg_assignment(Item *r1, Item *r2, Item *r3, Item *E) 
        : r1(r1), r2(r2), r3(r3), E(E) {
    }
    // // String_Instruction_Assignment Constructor
    // // String_Instruction_Assignment::String_Instruction_Assignment(std::string method, Item *dst, Item *src) : Instruction_assignment(dst, src), method(method) {}

    // // AOP_assignment Constructor
    // AOP_assignment::AOP_assignment(Item *method, Item *dst, Item *src) : String_Instruction_Assignment(method, dst, src) {}

    // // SOP_assignment Constructor
    // SOP_assignment::SOP_assignment(Item *method, Item *dst, Item *src) : String_Instruction_Assignment(method, dst, src) {}

} // namespace L1
