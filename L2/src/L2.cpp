#include "L2.h"

namespace L2 {
    /*
    Token class extensions
    */

    // Register, derived from Variable
    Variable::Variable(std::string name) : name(name) { 
   
    }
    Register::Register(std::string r) : Variable(r), name(r) {

    }
    std::string Variable::translate() {
    // implement later 
    return name;
    }
    std::string Variable::print() {
    //implement later
    return name;
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

    stackarg_assignment::stackarg_assignment(Item *w, Item *M)
        : w(w), M(M) {
    }
    void stackarg_assignment::printMe()
    {
    }


    /*
    Instruction Class accept definitions
    */
    void Instruction_ret::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the Instruction_assignment class
    void Instruction_assignment::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the label_Instruction class
    void label_Instruction::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the goto_label_instruction class
    void goto_label_instruction::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the Call_tenserr_Instruction class
    void Call_tenserr_Instruction::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the Call_uN_Instruction class
    void Call_uN_Instruction::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the Call_print_Instruction class
    void Call_print_Instruction::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the Call_input_Instruction class
    void Call_input_Instruction::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the Call_allocate_Instruction class
    void Call_allocate_Instruction::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the Call_tuple_Instruction class
    void Call_tuple_Instruction::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the w_increment_decrement class
    void w_increment_decrement::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the w_atreg_assignment class
    void w_atreg_assignment::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the Memory_assignment_store class
    void Memory_assignment_store::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the Memory_assignment_load class
    void Memory_assignment_load::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the Memory_arithmetic_load class
    void Memory_arithmetic_load::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the Memory_arithmetic_store class
    void Memory_arithmetic_store::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the cmp_Instruction class
    void cmp_Instruction::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the cjump_cmp_Instruction class
    void cjump_cmp_Instruction::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the stackarg_assignment class
    void stackarg_assignment::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the AOP_assignment class
    void AOP_assignment::accept(Visitor *visitor) {
        visitor->visit(this);
    }

    // Inside the SOP_assignment class
    void SOP_assignment::accept(Visitor *visitor) {
        visitor->visit(this);
    }
    
    void Function::calculateCFG(void){
        /*
        1. We need to first clear the previous predecessors/successors
        2. We then need to collect all of the jump function within this->instructions
        3. Find the predecessors 
        4. Find the successors 
        */
        std::set<cjump_cmp_Instruction *> total_cjump_instructions{};
        for (auto instruction : this->instructions){
            auto cast_instruction = dynamic_cast<cjump_cmp_Instruction *>(instruction);
            instruction->predecessors.clear(); // clearing out the predecessors
            instruction->successors.clear(); //clearing out the successors
            if (cast_instruction){
                total_cjump_instructions.insert(cast_instruction);
            };
        }
        Instruction *prev = nullptr;
        for (auto instruction: this->instructions){
            // this handles the predecessors where we have to move through different characters 
            auto jump_cast = dynamic_cast<cjump_cmp_Instruction *>(prev);
            auto goto_cast = dynamic_cast<goto_label_instruction *>(prev);
            if (!prev){
            } else if (!jump_cast && !goto_cast){
                instruction->predecessors.insert(prev);
            };
            auto label_cast = dynamic_cast<label_Instruction *>(instruction);
            // Clarified in OH: basically we know that up to this point, the insturciton is not a label, or a jump instruction
            // or a goto instruction. This means that the previous instruction 
            if (!label_cast){
                prev = instruction;
                continue;
            }
            std::cerr << "Current instruction: " << typeid(*instruction).name() << "\n";
            std::cerr << "Label cast result: " << label_cast << "\n";       
            auto label = label_cast->label;
            for (auto jump_label : total_cjump_instructions){
                auto compare_label = jump_label->label;
                // string comparisons are slow -> we want to do something more efficient hi isaac u are doing compliers but im doing ur dad
                if (compare_label == label){ 
                    instruction->predecessors.insert(jump_label);
                }
            }
            std::cerr<<"post label cast";

            prev = instruction;
            
        };
        for (auto instruction: this->instructions){
            for (auto predecessor: instruction->predecessors){
                predecessor->successors.insert(instruction);
            }
        }
    }   

    void UseDefVisitor::visit(Instruction_ret * instruction){
        // // ONE BIG PROBLEM IS THAT WE'RE GONNA HAVE TO MAKE SURE THAT VARIABLES GET COUNTED SOMEHOW 
        // // This will be an annoying bug to fix...need some sort of counter 
        // Variable* var1 = new Variable("r12");
        // Variable* var2 = new Variable("r13");
        // Variable* var3 = new Variable("r14");
        // Variable* var4 = new Variable("r15");
        // Variable* var5 = new Variable("rax");
        // Variable* var6 = new Variable("rbp");
        // Variable* var7 = new Variable("rbx");
        // instruction->used.insert(var1);
        // instruction->used.insert(var2);
        // instruction->used.insert(var3);
        // instruction->used.insert(var4);
        // instruction->used.insert(var5);
        // instruction->used.insert(var6);
        // instruction->used.insert(var7);
    }
    void UseDefVisitor::visit(Instruction_assignment * instruction) {
        Variable* var = dynamic_cast<Variable*>(instruction->s);
        if (var){
            instruction->used.insert(dynamic_cast<Variable*>(instruction->s));
        }
        instruction->defined.insert(dynamic_cast<Variable*>(instruction->d));
    }
    void UseDefVisitor::visit(label_Instruction *instruction) {
        
    }
    void UseDefVisitor::visit(goto_label_instruction *instruction) {

    }
    void UseDefVisitor::visit(Call_tenserr_Instruction *instruction) {
        // Variable* rdi = new Variable("rdi");
        // Variable* rsi = new Variable("rsi");
        // Variable* rdx = new Variable("rdx");
        // Variable* rcx = new Variable("rcx");
        // Variable* r8 = new Variable("r8");
        // Variable* r9 = new Variable("r9 ");
        // Variable* r10 = new Variable("r10");
        // Variable* r11 = new Variable("r11");
        // Variable* rax = new Variable("rax");

        // Number* count = dynamic_cast<Number*>(instruction->F);
        // int value = count->value;
        // if (value >= 8) instruction->used.insert(rdi);
        // if (value >= 16) instruction->used.insert(rsi);
        // if (value >= 24) instruction->used.insert(rdx);
        // if (value >= 32) instruction->used.insert(rcx);
        // if (value >= 40) instruction->used.insert(r8);
        // if (value >= 48) instruction->used.insert(r9);
        // // Caller Saved
        // instruction->defined.insert(r10);
        // instruction->defined.insert(r11);
        // instruction->defined.insert(r8);
        // instruction->defined.insert(r9);
        // instruction->defined.insert(rax);
        // instruction->defined.insert(rcx);
        // instruction->defined.insert(rdi);
        // instruction->defined.insert(rdx);
        // instruction->defined.insert(rsi);
    }
   
    void UseDefVisitor::visit(Call_print_Instruction *instruction) {
        // Variable* rdi = new Variable("rdi");
        // Variable* rsi = new Variable("rsi");
        // Variable* rdx = new Variable("rdx");
        // Variable* rcx = new Variable("rcx");
        // Variable* r8 = new Variable("r8");
        // Variable* r9 = new Variable("r9 ");
        // Variable* r10 = new Variable("r10");
        // Variable* r11 = new Variable("r11");
        // Variable* rax = new Variable("rax");
        // instruction->used.insert(rdi);
        // // Caller Saved
        // instruction->defined.insert(r10);
        // instruction->defined.insert(r11);
        // instruction->defined.insert(r8);
        // instruction->defined.insert(r9);
        // instruction->defined.insert(rax);
        // instruction->defined.insert(rcx);
        // instruction->defined.insert(rdi);
        // instruction->defined.insert(rdx);
        // instruction->defined.insert(rsi);
    }
    void UseDefVisitor::visit(Call_input_Instruction *instruction) {
        // Variable* rdi = new Variable("rdi");
        // Variable* rsi = new Variable("rsi");
        // Variable* rdx = new Variable("rdx");
        // Variable* rcx = new Variable("rcx");
        // Variable* r8 = new Variable("r8");
        // Variable* r9 = new Variable("r9 ");
        // Variable* r10 = new Variable("r10");
        // Variable* r11 = new Variable("r11");
        // Variable* rax = new Variable("rax");
        // // Caller Saved
        // instruction->defined.insert(r10);
        // instruction->defined.insert(r11);
        // instruction->defined.insert(r8);
        // instruction->defined.insert(r9);
        // instruction->defined.insert(rax);
        // instruction->defined.insert(rcx);
        // instruction->defined.insert(rdi);
        // instruction->defined.insert(rdx);
        // instruction->defined.insert(rsi);
    }
    void UseDefVisitor::visit(Call_allocate_Instruction *instruction) {
        // Variable* rdi = new Variable("rdi");
        // Variable* rsi = new Variable("rsi");
        // Variable* rdx = new Variable("rdx");
        // Variable* rcx = new Variable("rcx");
        // Variable* r8 = new Variable("r8");
        // Variable* r9 = new Variable("r9 ");
        // Variable* r10 = new Variable("r10");
        // Variable* r11 = new Variable("r11");
        // Variable* rax = new Variable("rax");
        // instruction->used.insert(rdi);
        // instruction->used.insert(rsi);
        // // Caller Saved
        // instruction->defined.insert(r10);
        // instruction->defined.insert(r11);
        // instruction->defined.insert(r8);
        // instruction->defined.insert(r9);
        // instruction->defined.insert(rax);
        // instruction->defined.insert(rcx);
        // instruction->defined.insert(rdi);
        // instruction->defined.insert(rdx);
        // instruction->defined.insert(rsi);
    }
    void UseDefVisitor::visit(Call_tuple_Instruction *instruction) {
        // Variable* rdi = new Variable("rdi");
        // Variable* rsi = new Variable("rsi");
        // Variable* rdx = new Variable("rdx");
        // Variable* rcx = new Variable("rcx");
        // Variable* r8 = new Variable("r8");
        // Variable* r9 = new Variable("r9 ");
        // Variable* r10 = new Variable("r10");
        // Variable* r11 = new Variable("r11");
        // Variable* rax = new Variable("rax");
        // instruction->used.insert(rdi);
        // instruction->used.insert(rsi);
        // instruction->used.insert(rdx);
        // // Caller Saved
        // instruction->defined.insert(r10);
        // instruction->defined.insert(r11);
        // instruction->defined.insert(r8);
        // instruction->defined.insert(r9);
        // instruction->defined.insert(rax);
        // instruction->defined.insert(rcx);
        // instruction->defined.insert(rdi);
        // instruction->defined.insert(rdx);
        // instruction->defined.insert(rsi);
    }

    void UseDefVisitor::visit(Call_uN_Instruction * instruction) {
        // Variable* rdi = new Variable("rdi");
        // Variable* rsi = new Variable("rsi");
        // Variable* rdx = new Variable("rdx");
        // Variable* rcx = new Variable("rcx");
        // Variable* r8 = new Variable("r8");
        // Variable* r9 = new Variable("r9 ");
        // Variable* r10 = new Variable("r10");
        // Variable* r11 = new Variable("r11");
        // Variable* rax = new Variable("rax");

        // Variable* var = dynamic_cast<Variable*>(instruction->u);
        // if (var){
        //     instruction->used.insert(var);
        // };
        // Number* count = dynamic_cast<Number*>(instruction->N);
        // int value = count->value;
        // if (value >= 8) instruction->used.insert(rdi);
        // if (value >= 16) instruction->used.insert(rsi);
        // if (value >= 24) instruction->used.insert(rdx);
        // if (value >= 32) instruction->used.insert(rcx);
        // if (value >= 40) instruction->used.insert(r8);
        // if (value >= 48) instruction->used.insert(r9);
        // // Caller Saved
        // instruction->defined.insert(r10);
        // instruction->defined.insert(r11);
        // instruction->defined.insert(r8);
        // instruction->defined.insert(r9);
        // instruction->defined.insert(rax);
        // instruction->defined.insert(rcx);
        // instruction->defined.insert(rdi);
        // instruction->defined.insert(rdx);
        // instruction->defined.insert(rsi);
    }



    void UseDefVisitor::visit(w_increment_decrement *instruction) {
        instruction->used.insert(dynamic_cast<Variable*>(instruction->r));
        instruction->defined.insert(dynamic_cast<Variable*>(instruction->r));
    }

    void UseDefVisitor::visit(w_atreg_assignment *instruction) {
        // last two W's are going to be gen
        // the first w is going to be kill
        instruction->used.insert(dynamic_cast<Variable*>(instruction->r3));
        instruction->used.insert(dynamic_cast<Variable*>(instruction->r2));
        instruction->defined.insert(dynamic_cast<Variable*>(instruction->r1));
    }
    void UseDefVisitor::visit(Memory_assignment_store *instruction) {
        // src is of type s, which can be either a variable, register, number, lable, or I name
        Variable* s_cast = dynamic_cast<Variable*>(instruction->s);
        if (s_cast) instruction->used.insert(s_cast);
        instruction->used.insert(dynamic_cast<Variable*>(instruction->dst));
    }

    void UseDefVisitor::visit(Memory_assignment_load *instruction) { // I'm not sure if this one is wrong 
        instruction->used.insert(dynamic_cast<Variable*>(instruction->x));
        instruction->defined.insert(dynamic_cast<Variable*>(instruction->dst));
    }
    void UseDefVisitor::visit(Memory_arithmetic_load *instruction) {
        instruction->used.insert(dynamic_cast<Variable*>(instruction->x));
        instruction->defined.insert(dynamic_cast<Variable*>(instruction->dst));
    }

    void UseDefVisitor::visit(Memory_arithmetic_store *instruction) {
        instruction->used.insert(dynamic_cast<Variable*>(instruction->t)); // Is t correct here?
        instruction->defined.insert(dynamic_cast<Variable*>(instruction->dst));  
    }
    void UseDefVisitor::visit(cmp_Instruction *instruction) {
        Variable* var1 = dynamic_cast<Variable*>(instruction->t1);
        Variable* var2 = dynamic_cast<Variable*>(instruction->t2);
        if (var1){
            instruction->used.insert(dynamic_cast<Variable*>(instruction->t1)); 
        }
        if (var2){
            instruction->used.insert(dynamic_cast<Variable*>(instruction->t2)); 
        }
        instruction->defined.insert(dynamic_cast<Variable*>(instruction->dst));
    }
    void UseDefVisitor::visit(cjump_cmp_Instruction *instruction) {
        instruction->used.insert(dynamic_cast<Variable*>(instruction->t1)); 
        instruction->used.insert(dynamic_cast<Variable*>(instruction->t2)); 
    }
    void UseDefVisitor::visit(stackarg_assignment *instruction) {
        instruction->defined.insert(dynamic_cast<Variable*>(instruction->w)); 
    }
    void UseDefVisitor::visit(AOP_assignment * instruction) {
        instruction->used.insert(dynamic_cast<Variable*>(instruction->src));
        instruction->defined.insert(dynamic_cast<Variable*>(instruction->dst));
    }

    void UseDefVisitor::visit(SOP_assignment *instruction){
        instruction->used.insert(dynamic_cast<Variable*>(instruction->src));
        instruction->used.insert(dynamic_cast<Variable*>(instruction->dst));
    }    
    void Function::calculateUseDefs(){
        UseDefVisitor visitor;
        for (auto instruction: this->instructions){
            instruction->accept(&visitor);
        };
    }
   

}
