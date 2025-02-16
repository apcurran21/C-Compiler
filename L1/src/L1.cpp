#include "L1.h"

namespace L1 {
    /*
    Token class extensions
    */

    // Register, derived from Item
    Register::Register(const std::string &r)
        : ID {r}{
        return ;
    }
    std::string Register::translate() {
        return "%" + this->ID;
    }
    std::string Register::print() {
        return this->ID;
    }

    Number::Number (int64_t n)
        : value {n}{
        return ;
    }
    std::string Number::translate () {
        return "$" + std::to_string(this->value);
    }
    std::string Number::print() {
        return std::to_string(this->value);
    }

    Name::Name (const std::string &value)
        : value {value}{
        return ;    
    }
    std::string Name::translate () {
        std::string fname = this->value.replace(0, 1, "_");
        return fname;
    }
    std::string Name::print() {
        return this->value;
    }

    Label::Label (const std::string &value)
        : value {value}{
        return ;
    }
    std::string Label::translate () {
        return this->value.replace(0, 1, "_");
    }
    std::string Label::print() {
        return this->value;
    }

    Operator::Operator (const std::string &sign)
        : sign {sign} {
        return;
    }
    std::string Operator::translate() {
        std::string v = this->sign;
        if (v == "+=") {return "addq";}
        else if (v == "-=") {return "subq";}
        else if (v == "*=") {return "imulq";}
        else if (v == "&=") {return "andq";}
        else if (v == "--") {return "dec";}
        else if (v == "++") {return "inc";}
        else if (v == "<<=") {return "salq";}
        else if (v == ">>=") {return "sarq";}
        else if (v == "<") {return "setl";}
        else if (v == "<=") {return "setle";}
        else if (v == "=") {return "sete";}
        else {
            std::cerr << "invalid operator" << v << "found." << std::endl;
            return "STOP";
        }
    }
    std::string Operator::print() {
        return this->sign;
    }


    // Register::~Register() {}
    // void Register::print() {
    //     std::cout << "found the register's override of Item::print!" << std::endl;
    // }
    // int Register::give_status() {
    //     return 0;
    // }

    // // Integer, derived from Item
    // Integer::Integer(int value) : value(value) {}
    // Integer::~Integer() {}
    // void Integer::print() {
    //     std::cout << "found the integer's override of Item::print!" << std::endl;
    // }
    // int Integer::give_status() {
    //     return 1;
    // }

    // // String, derived from Item
    // String::String(const std::string& value) : value(value) {}
    // String::~String() {}
    // void String::print() {
    //     std::cout << "found the string's override of Item::print!" << std::endl;
    // }
    // int String::give_status() {
    //     return 2;
    // }


    /*
    Instruction class extensions
    */

    Instruction_ret::Instruction_ret() {}
    void Instruction_ret::printMe() {
        std::cout << "Instruction_ret:    return" << std::endl;
    }

    // Instruction_assignment Constructor
    // Instruction_assignment::Instruction_assignment(Item *dst, Item *src) : s(src), d(dst) {}
    Instruction_assignment::Instruction_assignment (Item *dst, Item *src)
        : s { src },
        d { dst } {
        return ;
    }
    void Instruction_assignment::printMe() {
        std::cout << "Instruction_assignment:    " << this->d->translate() << " <- " << this->s->translate() << std::endl;
    }

    // // I don't think this instruction is being used
    // // incdec_instruction Constructor
    // incdec_instruction::incdec_instruction(Item *reg, Item *method) : reg(reg), method(method) {}
    // void incdec_instruction::printMe() {

    // }

    // at_instruction Constructor
    // at_instruction::at_instruction(Item *reg1, Item *reg2, Item *reg3, Integer *num) : reg1(reg1), reg2(reg2), reg3(reg3), num(num) {}

    // label_Instruction Constructor
    label_Instruction::label_Instruction(Item *label) : label(label) {}
    void label_Instruction::printMe() {

    }

    // goto_label_instruction Constructor
    goto_label_instruction::goto_label_instruction(Item *label) : label_Instruction(label) {}
    void goto_label_instruction::printMe() {

    }
    // goto_label_instruction::goto_label_instruction(Item *method, Item *label) : label_Instruction(label), method(method) {}

    // // note that this class is never used, also nothing inherits from it 
    // // Call_Instruction Constructor
    // Call_Instruction::Call_Instruction(Item *method) : method(method) {}
    // void Call_Instruction::printMe() {

    // }

    // Call_tenserr_Instruction Constructor
    Call_tenserr_Instruction::Call_tenserr_Instruction(Item *F) : F(F) {}
    void Call_tenserr_Instruction::printMe() {

    }

    // Call_uN_Instruction Constructor
    Call_uN_Instruction::Call_uN_Instruction(Item *u, Item *N) : u(u), N(N) {}
    void Call_uN_Instruction::printMe() {

    }

    Memory_assignment_store::Memory_assignment_store(Item *dst, Item *s, Item *M) : dst(dst), s(s), M(M) {}
    void Memory_assignment_store::printMe() {
        std::cout << "Memory_assignment_store:    " << "dst = " << this->dst->translate() << ", M = " << this->M->translate() << ", s = " << this->s->translate() << std::endl;
    }

    Memory_assignment_load::Memory_assignment_load(Item *dst, Item *x, Item *M) : dst(dst), x(x), M(M) {}
    void Memory_assignment_load::printMe() {
        std::cout << "Memory_assignment_load:    " << "dst = " << this->dst->translate() << ", M = " << this->M->translate() << ", x = " << this->x->translate() << std::endl;
    }

    // Memory_arithmetic Constructor
    Memory_arithmetic_load::Memory_arithmetic_load(Item *dst, Item *x, Item *instruction, Item *M) 
    : dst(dst), x(x), instruction(instruction), M(M) {}
    void Memory_arithmetic_load::printMe() {
        std::cout << "Memory_assignment_load:    " << "dst = " << this->dst->translate() << ", M = " << this->M->translate() << ", x = " << this->x->translate() << ", instruction = " << this->instruction->translate() << std::endl;
    }

    Memory_arithmetic_store::Memory_arithmetic_store(Item *dst, Item *t, Item *instruction, Item *M) 
    : dst(dst), t(t), instruction(instruction), M(M) {}
    void Memory_arithmetic_store::printMe() {
        std::cout << "Memory_assignment_load:    " << "dst = " << this->dst->translate() << ", M = " << this->M->translate() << ", t = " << this->t->translate() << ", instruction = " << this->instruction->translate() << std::endl;
    }
    
    // cmp_Instruction Constructor
    cmp_Instruction::cmp_Instruction(Item *dst, Item *t2, Item *method, Item *t1) : dst(dst), t1(t1), method(method), t2(t2) {}
    void cmp_Instruction::printMe() {

    }

    // cjump_cmp_Instruction Constructor
    cjump_cmp_Instruction::cjump_cmp_Instruction(Item *t2, Item *cmp, Item *t1, Item *label) : t2(t2), cmp(cmp), t1(t1), label(label) {}
    void cjump_cmp_Instruction::printMe() {

    }

    // AOP_assignment Constructor
    AOP_assignment::AOP_assignment(Item *method, Item *dst, Item *src) : Instruction_assignment(dst, src), method(method) {}
    void AOP_assignment::printMe() {
        std::cout << "AOP_assignment:    " << "d = " << this->d->translate() << ", method = " << this->method->translate() << ", s = " << this->s->translate() << std::endl;
    }

    // SOP_assignment Constructor
    SOP_assignment::SOP_assignment(Item *method, Item *dst, Item *src) : Instruction_assignment(dst, src), method(method) {}
    void SOP_assignment::printMe() {
        std::cout << "SOP_assignment:    " << "d = " << this->d->print() << ", method = " << this->method->print() << ", s = " << this->s->print() << std::endl;
    }

    Call_print_Instruction::Call_print_Instruction() {}
    void Call_print_Instruction::printMe() {

    }

    Call_input_Instruction::Call_input_Instruction() {}
    void Call_input_Instruction::printMe() {

    }

    Call_allocate_Instruction::Call_allocate_Instruction() {}
    void Call_allocate_Instruction::printMe() {

    }

    Call_tuple_Instruction::Call_tuple_Instruction() {}
    void Call_tuple_Instruction::printMe() {

    }

    w_increment_decrement::w_increment_decrement(Item *r, Item *symbol) 
        : r(r), symbol(symbol) {
    }
    void w_increment_decrement::printMe() {
        std::cout << "w_increment_decrement:    " << "r = " << this->r->translate() << ", symbol = " << this->symbol->translate() << std::endl;
    }

    w_atreg_assignment::w_atreg_assignment(Item *r1, Item *r2, Item *r3, Item *E) 
        : r1(r1), r2(r2), r3(r3), E(E) {
    }
    void w_atreg_assignment::printMe() {

    }
   

   
}
