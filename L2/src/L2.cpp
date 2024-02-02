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

    // AOP_assignment ConstructorInstruction_assignment(dst, src),
    AOP_assignment::AOP_assignment(Item *method, Item *dst, Item *src) : src(src), dst(dst), method(method) {}
    void AOP_assignment::printMe() {
        std::cout << "AOP_assignment:    " << "d = " << this->dst->translate() << ", method = " << this->method->translate() << ", s = " << this->src->translate() << std::endl;
    }

    // SOP_assignment Constructor
    SOP_assignment::SOP_assignment(Item *method, Item *dst, Item *src) : src(src), dst(dst), method(method) {}
    void SOP_assignment::printMe() {
        std::cout << "SOP_assignment:    " << "d = " << this->dst->print() << ", method = " << this->method->print() << ", s = " << this->src->print() << std::endl;
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
            auto tenserr_cast = dynamic_cast<Call_tenserr_Instruction *>(prev);
            auto ret_cast = dynamic_cast<Instruction_ret*>(prev);
            if (tenserr_cast || ret_cast) {
                prev = instruction;
                continue; // Skip successor assignment
            }
            // this handles the predecessors where we have to move through different characters 
            auto jump_cast = dynamic_cast<cjump_cmp_Instruction *>(prev);
            auto goto_cast = dynamic_cast<goto_label_instruction *>(prev);
            if (!prev){
            } else if (!jump_cast && !goto_cast){
                instruction->predecessors.insert(prev);
            };
            auto label_cast = dynamic_cast<label_Instruction *>(instruction);
            auto cjump_cast = dynamic_cast<cjump_cmp_Instruction *>(instruction);
            // Clarified in OH: basically we know that up to this point, the insturciton is not a label, or a jump instruction
            // or a goto instruction. This means that the previous instruction 
            if (!label_cast){
                prev = instruction;
                continue;  
            }
            if (debug) std::cerr << "Current instruction: " << typeid(*instruction).name() << "\n";
            if (debug) std::cerr << "Label cast result: " << label_cast << "\n";    
            Item* label = nullptr; // Initialize to nullptr to avoid undefined behavior

            if (cjump_cast) {
                label = cjump_cast->label; // Assign to the outer label
            } else {
                label = label_cast->label; // Assign to the outer label
            }

            for (auto jump_label : total_cjump_instructions){
                auto compare_label = jump_label->label;
                if (compare_label->print() == label->print()){ 
                    instruction->predecessors.insert(jump_label);
                }
            }
            if (debug) std::cerr<<"post label cast";

            prev = instruction;
            
        };
        for (auto instruction: this->instructions){
            for (auto predecessor: instruction->predecessors){
                auto tenserr_cast = dynamic_cast<Call_tenserr_Instruction *>(predecessor);
                auto ret_cast = dynamic_cast<Instruction_ret*>(predecessor);
                if (tenserr_cast || ret_cast) {
                } else {
                    predecessor->successors.insert(instruction);
                }
            }
        }
        for (auto instruction: this->instructions){
            if (debug) std::cerr<<"printing successors"<<std::endl;
            for (auto successor : instruction->successors) {
                successor->printMe();
            }
        }
    }   

    /*
    Use/Def Set Visitor methods
    */
    void UseDefVisitor::visit(Instruction_ret * instruction){

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

    }
   
    void UseDefVisitor::visit(Call_print_Instruction *instruction) {

    }

    void UseDefVisitor::visit(Call_input_Instruction *instruction) {

    }

    void UseDefVisitor::visit(Call_allocate_Instruction *instruction) {

    }

    void UseDefVisitor::visit(Call_tuple_Instruction *instruction) {

    }

    void UseDefVisitor::visit(Call_uN_Instruction * instruction) {
        Variable* var = dynamic_cast<Variable*>(instruction->u);
        if (var){
            instruction->used.insert(var);
        };
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
        Variable* d_cast = dynamic_cast<Variable*>(instruction->dst);
        if (d_cast->name != "rsp"){
            instruction->used.insert(d_cast);
        }
    }

    void UseDefVisitor::visit(Memory_assignment_load *instruction) {
        instruction->used.insert(dynamic_cast<Variable*>(instruction->x));
        instruction->defined.insert(dynamic_cast<Variable*>(instruction->dst));
    }

    void UseDefVisitor::visit(Memory_arithmetic_load *instruction) {
        instruction->used.insert(dynamic_cast<Variable*>(instruction->x));
        instruction->used.insert(dynamic_cast<Variable*>(instruction->dst));
        instruction->defined.insert(dynamic_cast<Variable*>(instruction->dst));
    }

    void UseDefVisitor::visit(Memory_arithmetic_store *instruction) {
        Variable* t_cast = dynamic_cast<Variable*>(instruction->t);
        if (t_cast) instruction->used.insert(t_cast);
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
        Variable* var1 = dynamic_cast<Variable*>(instruction->t1);
        Variable* var2 = dynamic_cast<Variable*>(instruction->t2);
        if (var1){
            instruction->used.insert(dynamic_cast<Variable*>(instruction->t1)); 
        }
        if (var2){
            instruction->used.insert(dynamic_cast<Variable*>(instruction->t2)); 
        }

    }

    void UseDefVisitor::visit(stackarg_assignment *instruction) {
        instruction->defined.insert(dynamic_cast<Variable*>(instruction->w)); 
    }

    void UseDefVisitor::visit(AOP_assignment * instruction) {
        Variable* src_cast = dynamic_cast<Variable*>(instruction->src);
        if (src_cast) instruction->used.insert(src_cast);
        instruction->used.insert(dynamic_cast<Variable*>(instruction->dst));
        instruction->defined.insert(dynamic_cast<Variable*>(instruction->dst));
    }

    void UseDefVisitor::visit(SOP_assignment *instruction){
        Variable* src_cast = dynamic_cast<Variable*>(instruction->src);
        if (src_cast) instruction->used.insert(src_cast);
        instruction->used.insert(dynamic_cast<Variable*>(instruction->dst));
        instruction->defined.insert(dynamic_cast<Variable*>(instruction->dst));
    }


    /*
    Calculate the Use/Def sets by running over each instruction's visit method
    */
    void Function::calculateUseDefs(){
        UseDefVisitor visitor;
        for (auto instruction: this->instructions){
            instruction->accept(&visitor);
        };
    }
   

}


