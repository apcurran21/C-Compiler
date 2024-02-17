#include "L2.h"

namespace L2 {
    std::map<std::string, bool> seenVariables;
    /*
    Token class extensions
    */

    // Register, derived from Variable
    Variable::Variable(std::string name) : name(name) { 
   
    }
    Register::Register(std::string r) : Variable(r), name(r) {

    }
    std::string Register::print() {
        return name;
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
        std::set<Instruction *> total_cjump_instructions{};
        // for (auto instruction : this->instructions){
        for (auto instruction : instructions) {
            auto cast_instruction = dynamic_cast<cjump_cmp_Instruction *>(instruction);
            auto goto_instruction = dynamic_cast<goto_label_instruction*>(instruction);
            instruction->predecessors.clear(); // clearing out the predecessors
            instruction->successors.clear(); //clearing out the successors
            if (cast_instruction){
                total_cjump_instructions.insert(cast_instruction);
            }
            if (goto_instruction){
                total_cjump_instructions.insert(goto_instruction);
            }
            ;
        }
        Instruction *prev = nullptr;
        for (auto instruction: this->instructions){
            // if (debug) std::cerr<<"we iterating";
            auto tenserr_cast = dynamic_cast<Call_tenserr_Instruction *>(prev);
            auto ret_cast = dynamic_cast<Instruction_ret*>(prev);
            auto tuple_err = dynamic_cast<Call_tuple_Instruction*>(prev);
            auto goto_cast = dynamic_cast<goto_label_instruction*>(prev);
            auto cjump_cast = dynamic_cast<cjump_cmp_Instruction *>(prev);
            auto label_cast = dynamic_cast<label_Instruction*>(instruction);
            if (!prev && !label_cast){
                prev = instruction;
                continue;
            }
            if (tenserr_cast || ret_cast || tuple_err || goto_cast||!prev){
            } else{
                instruction->predecessors.insert(prev);
            }
            auto check_goto_cast = dynamic_cast<goto_label_instruction*>(instruction);
            if (check_goto_cast){
                prev = instruction;
                continue;
            }
            // everything that the previous one WILL be this instruciton predecessor 
            // essentially we know that if the instruction is NOT A LABEL that everything before it 
            // will be a predecessor
            if (!label_cast){
                prev = instruction;
                continue;
            };
            for (auto jump_label : total_cjump_instructions){
                auto cast_label = dynamic_cast<cjump_cmp_Instruction *>(jump_label);
                auto goto_label = dynamic_cast<goto_label_instruction*>(jump_label);
                Label* compare_label = nullptr; // Initialize to nullptr
                std::string compare;
                
                if (cast_label){
                    compare_label = dynamic_cast<Label *>(cast_label->label);
                    if (compare_label) { // Make sure the dynamic_cast was successful
                        compare = compare_label->value;
                    }
                } else if (goto_label) {
                    compare_label = dynamic_cast<Label *>(goto_label->label);
                    if (compare_label) { // Make sure the dynamic_cast was successful
                        compare = compare_label->value;
                    }
                }
                if (compare_label && compare == label_cast->getLabel()){ 
                    instruction->predecessors.insert(jump_label);
                }
            }
            // if (debug) std::cerr<<"post label cast";

            prev = instruction;
            
        };
        for (auto instruction: this->instructions){
            for (auto predecessor: instruction->predecessors){
                predecessor->successors.insert(instruction);
            }
        }
        // for (auto instruction: this->instructions){
        //     // if (debug) std::cerr<<"printing successors"<<std::endl;
        //     for (auto successor : instruction->successors) {
        //         successor->printMe();
        //     }
        // }
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
        Variable* x_cast = dynamic_cast<Variable*>(instruction->x);
        if (x_cast->name != "rsp") {
            instruction->used.insert(dynamic_cast<Variable*>(instruction->x));
        }
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
    bool SpillVisitor::replaceIfSpilled(Item*& item) {
        auto variable = dynamic_cast<Variable*>(item);
        if (variable) {
            if (variable->name == spilledVariable->name) { //need to fix this lol
                item = this->replacementVariable;
                return 1;
            }
        }
        return 0;
    }
    bool SpillVisitor::IfSpilled(Item*& item) {
        auto variable = dynamic_cast<Variable*>(item);
        if (variable) {
            if (variable->name == spilledVariable->name) { //need to fix this lol                
                return 1;
            }
        }
        return 0;
    }
    void SpillVisitor::iterReplacementVariable(){
        count++;
        this->replacementVariable = new Variable("%S" + std::to_string(count));
        this->spilled = true;
    }
    void SpillVisitor::visit(Instruction_ret *instruction){} ;
    void SpillVisitor::visit(Instruction_assignment *instruction){
        bool replaceD = IfSpilled(instruction->d);
        if (replaceD){
            if (instruction->d->print() == instruction->s->print()){
                bool temp = replaceIfSpilled(instruction->d);
                bool replaceS = replaceIfSpilled(instruction->s);
                this->spilled = true;
                return;
            }
            iterReplacementVariable();
        }
        bool temp = replaceIfSpilled(instruction->d);
        bool replaceS = replaceIfSpilled(instruction->s);

    };
    void SpillVisitor::visit(label_Instruction *instruction) {};
    void SpillVisitor::visit(goto_label_instruction *instruction) {};
    void SpillVisitor::visit(Call_tenserr_Instruction *instruction) {};
    void SpillVisitor::visit(Call_uN_Instruction *instruction) {
        bool replaceU = replaceIfSpilled(instruction->u);
    };
    void SpillVisitor::visit(Call_print_Instruction *instruction) {};
    void SpillVisitor::visit(Call_input_Instruction *instruction) {};
    void SpillVisitor::visit(Call_allocate_Instruction *instruction){} ;
    void SpillVisitor::visit(Call_tuple_Instruction *instruction) {};
    void SpillVisitor::visit(w_increment_decrement *instruction) {
        bool replaceR = replaceIfSpilled(instruction->r);
        if (replaceR) {
            iterReplacementVariable();
        }
    };
    void SpillVisitor::visit(w_atreg_assignment *instruction) {
        bool replaceR1 = replaceIfSpilled(instruction->r1);
        bool replaceR2 = replaceIfSpilled(instruction->r2);
        bool replaceR3 = replaceIfSpilled(instruction->r3);
        if (replaceR1 || replaceR2 || replaceR3) {
            iterReplacementVariable();
        }
    };
    void SpillVisitor::visit(Memory_assignment_store *instruction) {
        bool replaceS = replaceIfSpilled(instruction->s);
        bool replaceDST = replaceIfSpilled(instruction->dst);   

    };
    void SpillVisitor::visit(Memory_assignment_load *instruction){
        bool replaceD = replaceIfSpilled(instruction->dst);
        bool replaceX = replaceIfSpilled(instruction->x);
        bool replaceM = replaceIfSpilled(instruction->M); 
        if (replaceD || replaceX || replaceM) {
            iterReplacementVariable();
        }            
    } ;
    void SpillVisitor::visit(Memory_arithmetic_load *instruction) {
        bool replaceD = replaceIfSpilled(instruction->dst);
        bool replaceInstruction = replaceIfSpilled(instruction->instruction);    
        bool replaceM = replaceIfSpilled(instruction->M);  
        if (replaceD) {
            iterReplacementVariable();
        }         
    };
    void SpillVisitor::visit(Memory_arithmetic_store *instruction){
        bool replaceD = replaceIfSpilled(instruction->dst);
        bool replaceT = replaceIfSpilled(instruction->t);
        bool replaceInstruction = replaceIfSpilled(instruction->instruction);    
        bool replaceM = replaceIfSpilled(instruction->M);              
    };
    void SpillVisitor::visit(cmp_Instruction *instruction){
        bool replaceD = replaceIfSpilled(instruction->dst);
        bool replaceT = replaceIfSpilled(instruction->t1);
        bool replaceM = replaceIfSpilled(instruction->method);    
        bool replaceT2 = replaceIfSpilled(instruction->t2); 
        if (replaceD) {
            iterReplacementVariable();
        }     
    };
    void SpillVisitor::visit(cjump_cmp_Instruction *instruction){
        bool replaceT2 = replaceIfSpilled(instruction->t2);
        bool replaceCMP = replaceIfSpilled(instruction->cmp);
        bool replaceT1 = replaceIfSpilled(instruction->t1);    
        bool replaceLabel = replaceIfSpilled(instruction->label);     
        if (replaceT2 || replaceT1 ) {
            iterReplacementVariable();
        }          
    } ;
    void SpillVisitor::visit(stackarg_assignment *instruction){
        bool replaceW = replaceIfSpilled(instruction->w);
        bool replaceM = replaceIfSpilled(instruction->M);   
        if (replaceW) {
            iterReplacementVariable();
        }          
    };
    void SpillVisitor::visit(AOP_assignment *instruction){
        bool replaceMethod = replaceIfSpilled(instruction->method);
        bool replaceD = replaceIfSpilled(instruction->dst);   
        bool replaceSrc = replaceIfSpilled(instruction->src);   
        if (replaceD) {
            iterReplacementVariable();
        }          
    };
    void SpillVisitor::visit(SOP_assignment *instruction) {
        bool replaceMethod = replaceIfSpilled(instruction->method);
        bool replaceDst = replaceIfSpilled(instruction->dst);   
        bool replaceSrc = replaceIfSpilled(instruction->src);  
        if (replaceDst) {
            iterReplacementVariable();
        }          
    };  

    /*
    Calculate the Use/Def sets by running over each instruction's visit method
    */
    void Function::calculateUseDefs(){
        UseDefVisitor visitor;
        // for (auto instruction: this->instructions){
        for (auto instruction: instructions) {
            instruction->accept(&visitor);
        };
    }
    void ColorVariablesVisitor::colorVar(Variable * &var) {
        // Node* correspondingNode = color_graph->nodes[var];
        // if (correspondingNode) {
        //     std::string color = correspondingNode->color;
        //     Variable* new_var = current_function->variable_allocator.allocate_variable(color, VariableType::reg);
        //     *var = *new_var;
        // } else {
        //     // The variable was not found in the graph.
        //     // theoretically shouldn't get here...
        // }
        auto iterator = color_graph->nodes.find(var);
        if (iterator != color_graph->nodes.end()) {
            Node* correspondingNode = iterator->second;
            std::string color = correspondingNode->color;
            Variable* new_var = current_function->variable_allocator.allocate_variable(color, VariableType::reg);
            *var = *new_var;
        } else {

        }
        // auto iterator = color_graph->nodes.find(var);
        // if (iterator != color_graph->nodes.end()) {
        //     Node* correspondingNode = iterator->second();
        //     std::string color = correspondingNode->color;
        //     Variable* new_var = current_function->variable_allocator.allocate_variable(color, VariableType::reg);
        //     *var = *new_var;
        // } else {
        //     // The variable was not found in the graph.
        //     // theoretically shouldn't get here...
        // }
    }
    void ColorVariablesVisitor::visit(Instruction_ret * instruction) {
    }
    void ColorVariablesVisitor::visit(Instruction_assignment *instruction) {
        auto s = dynamic_cast<Variable*>(instruction->s);
        auto d = dynamic_cast<Variable*>(instruction->d);
        colorVar(s);
        colorVar(d);
    }
    void ColorVariablesVisitor::visit(label_Instruction *instruction) {
        auto label = dynamic_cast<Variable*>(instruction->label);
        colorVar(label);
    }
    void ColorVariablesVisitor::visit(goto_label_instruction *instruction) {
    }
    void ColorVariablesVisitor::visit(Call_tenserr_Instruction *instruction) {
    }
    void ColorVariablesVisitor::visit(Call_uN_Instruction *instruction) {
    }
    void ColorVariablesVisitor::visit(Call_print_Instruction *instruction) {
    }
    void ColorVariablesVisitor::visit(Call_input_Instruction *instruction) {
    }
    void ColorVariablesVisitor::visit(Call_allocate_Instruction *instruction) {
    }
    void ColorVariablesVisitor::visit(Call_tuple_Instruction *instruction) {
    }
    void ColorVariablesVisitor::visit(w_increment_decrement *instruction) {
        auto r = dynamic_cast<Variable*>(instruction->r);
        colorVar(r);
    }
    void ColorVariablesVisitor::visit(w_atreg_assignment *instruction) {
        auto r1 = dynamic_cast<Variable*>(instruction->r1);
        auto r2 = dynamic_cast<Variable*>(instruction->r2);
        auto r3 = dynamic_cast<Variable*>(instruction->r3);
        colorVar(r1);
        colorVar(r2);
        colorVar(r3);

    }
    void ColorVariablesVisitor::visit(Memory_assignment_store *instruction) {
        auto dst = dynamic_cast<Variable*>(instruction->dst);
        auto s = dynamic_cast<Variable*>(instruction->s);
        colorVar(dst);
        colorVar(s);
    }
    void ColorVariablesVisitor::visit(Memory_assignment_load *instruction) {
        auto dst = dynamic_cast<Variable*>(instruction->dst);
        auto x = dynamic_cast<Variable*>(instruction->x);
        colorVar(dst);
        colorVar(x);

    }
    void ColorVariablesVisitor::visit(Memory_arithmetic_load *instruction) {
        auto dst = dynamic_cast<Variable*>(instruction->dst);
        auto x = dynamic_cast<Variable*>(instruction->x);
        colorVar(dst);
        colorVar(x);
    }
    void ColorVariablesVisitor::visit(Memory_arithmetic_store *instruction) {
        auto dst = dynamic_cast<Variable*>(instruction->dst);
        auto t = dynamic_cast<Variable*>(instruction->t);
        colorVar(dst);
        colorVar(t);
    }
    void ColorVariablesVisitor::visit(cmp_Instruction *instruction) {
        auto dst = dynamic_cast<Variable*>(instruction->dst);
        auto t1 = dynamic_cast<Variable*>(instruction->t1);
        auto t2 = dynamic_cast<Variable*>(instruction->t2);
        colorVar(dst);
        colorVar(t1);
        colorVar(t2);

    }
    void ColorVariablesVisitor::visit(cjump_cmp_Instruction *instruction) {
        auto label = dynamic_cast<Variable*>(instruction->label);
        auto t1 = dynamic_cast<Variable*>(instruction->t1);
        auto t2 = dynamic_cast<Variable*>(instruction->t2);
        colorVar(label);
        colorVar(t1);
        colorVar(t2);
    }
    void ColorVariablesVisitor::visit(stackarg_assignment *instruction) {
        auto w = dynamic_cast<Variable*>(instruction->w);
        colorVar(w);
    }
    void ColorVariablesVisitor::visit(AOP_assignment *instruction) {
        auto dst = dynamic_cast<Variable*>(instruction->dst);
        auto src = dynamic_cast<Variable*>(instruction->src);
        colorVar(dst);        
        colorVar(src);
    }
    void ColorVariablesVisitor::visit(SOP_assignment *instruction) {
        auto dst = dynamic_cast<Variable*>(instruction->dst);
        auto src = dynamic_cast<Variable*>(instruction->src);
        colorVar(dst);        
        colorVar(src);
    }

    /*
    Instruction print visitor.
    */
    void PrintVisitor::visit(Instruction_ret *instruction) {
        std::cerr << "return" << "\n";
    }
    void PrintVisitor::visit(Instruction_assignment *instruction) {
        std::cerr << instruction->d->print() << " <- " << instruction->s->print() << "\n";
    }
    void PrintVisitor::visit(label_Instruction *instruction) {
        std::cerr << instruction->label->print() << "\n";
    }
    void PrintVisitor::visit(goto_label_instruction *instruction) {
        std::cerr << "goto " << instruction->label->print() << "\n";
    }
    void PrintVisitor::visit(Call_tenserr_Instruction *instruction) {
        std::cerr << "call tensor-error " << instruction->F->print() << "\n";
    }
    void PrintVisitor::visit(Call_uN_Instruction *instruction) {
        std::cerr << "call " << instruction->u->print() << " " << instruction->N->print() << "\n";
    }
    void PrintVisitor::visit(Call_print_Instruction *instruction) {
        std::cerr << "call print 1" << "\n";
    }
    void PrintVisitor::visit(Call_input_Instruction *instruction) {
        std::cerr << "call input 0" << "\n";
    }
    void PrintVisitor::visit(Call_allocate_Instruction *instruction) {
        std::cerr << "call allocate 2" << "\n";
    }
    void PrintVisitor::visit(Call_tuple_Instruction *instruction) {
        std::cerr << "call tuple-error 3" << "\n";
    }
    void PrintVisitor::visit(w_increment_decrement *instruction) {
        std::cerr << instruction->r->print() << " " << instruction->symbol->print() << "\n";
    }
    void PrintVisitor::visit(w_atreg_assignment *instruction) {
        std::cerr << instruction->r1->print() << " @ " << instruction->r2->print() << " " << instruction->r3->print() << " " << instruction->E->print() << "\n";
    }
    void PrintVisitor::visit(Memory_assignment_store *instruction) {
        std::cerr << "mem " << instruction->dst->print() << " " << instruction->M->print() << " <- " << instruction->s->print() << "\n";
    }
    void PrintVisitor::visit(Memory_assignment_load *instruction) {
        std::cerr << instruction->dst->print() << " <- mem " << instruction->M->print() << " " << instruction->x->print() << "\n";
    }
    void PrintVisitor::visit(Memory_arithmetic_load *instruction) {
        std::cerr << instruction->dst->print() << " " << instruction->instruction->print() << " mem " << instruction->x->print() << " " << instruction->M->print() << "\n";
    }
    void PrintVisitor::visit(Memory_arithmetic_store *instruction) {
        std::cerr << "mem " << instruction->dst->print() << " " << instruction->M->print() << " " << instruction->instruction->print() << " " << instruction->t->print() << "\n";
    }
    void PrintVisitor::visit(cmp_Instruction *instruction) {
        std::cerr << instruction->dst->print() << " <- " << instruction->t1->print() << " " << instruction->method->print() << " " << instruction->t2->print() << "\n";
    }
    void PrintVisitor::visit(cjump_cmp_Instruction *instruction) {
        std::cerr << "cjump " << instruction->t1->print() << " " << instruction->cmp->print() << " " << instruction->t2->print() << " " << instruction->label->print() << "\n";
    }
    void PrintVisitor::visit(stackarg_assignment *instruction) {
        std::cerr << instruction->w->print() << " <- stack-arg " << instruction->M->print() << "\n";
    }
    void PrintVisitor::visit(AOP_assignment *instruction) {
        std::cerr << instruction->dst->print() << " " << instruction->method->print() << " " << instruction->src->print() << "\n";
    }
    void PrintVisitor::visit(SOP_assignment *instruction) {
        std::cerr << instruction->dst->print() << " " << instruction->method->print() << " " << instruction->src->print() << "\n"; 
    }

}
