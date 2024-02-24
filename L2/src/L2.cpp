#include "L2.h"

namespace L2 {

    int printdebug = 1;

    /*
    Code Analysis.
    */
    Graph* analyze_L2(Function* fptr) {

        Curr_F_Liveness liveness_results = liveness_analysis(fptr);
        if (printdebug) {
            std::cerr << "printing in and out sets..." <<"\n";
            print_liveness(fptr, liveness_results);
        }
        Graph* interference_graph = build_graph(fptr, liveness_results);

        return interference_graph;
    }

    /*
    Register Allocation.
    */
    Function* allocate_registers(Function* fptr) {
        Function* fptr_out;
        std::map<std::string, bool> seenVariables;

        int spill_count = 0;
        int stack_counter = 0;
        while (true) {
            /*
            We need to iterate until we are able to fully color each node in the 
            function's interference graph, or we spill everything.
            */

            Graph* interference_graph = analyze_L2(fptr);

            // Iterate over seenVariables to remove corresponding nodes from the graph based on their names.
            /*
            for (const auto& varEntry : seenVariables) {
                // Check if the variable is marked as 'seen' (true).
                if (varEntry.second) {
                    // varEntry.first holds the name of the variable.
                    const std::string& varName = varEntry.first;

                    // Directly attempt to remove the node by its variable name, avoiding the creation of a Variable instance.
                    // This assumes you have a method like removeNodeByName implemented in your Graph class.
                    interference_graph->removeNodeByName(varName);
                }
            }
            */
            
            
            
            if (printdebug) std::cerr << "Printing the graph:\n";
            if (printdebug) interference_graph->printGraph();
            Graph* interference_graph_copy = interference_graph->clone();

            std::tuple<bool, std::vector<Node*>> color_result = color_graph(interference_graph, interference_graph_copy, fptr);

            bool big_fail = std::get<0>(color_result);
            std::vector<Node*> uncolored_nodes = std::get<1>(color_result);
            if (big_fail) {

                /*
                Spill all variables in the graph.
                */

                for (auto& pair : interference_graph_copy->nodes) {
                    auto var = pair.first;
                    auto reg_ptr = dynamic_cast<L2::Register*>(var);
                    if ((!reg_ptr) && (fptr->spill_variables_set.find(var) == fptr->spill_variables_set.end())) {
                    std::tuple<std::set<std::string>,L2::Function*,int> resultTuple = L2::spillForL2(fptr, var, spill_count, stack_counter);
                    auto changed = std::get<0>(resultTuple); // For the std::set<std::string>
                    L2::Function* newFunction = std::get<1>(resultTuple);
                    spill_count = std::get<2>(resultTuple);
                    fptr = newFunction;
                    stack_counter++;
                    }
                }

                fptr_out = fptr;
                break;

            } else if (uncolored_nodes.size() == 0) {

                /*
                Graph coloring succeeded.
                -Is it safe to return the original fptr here?
                    - I think so if all we do afterwards is codegen, no more
                        updates that could cause error.
                */

                ColorVariablesVisitor myColorVisitor = ColorVariablesVisitor(interference_graph_copy, fptr);

                for (Instruction *iptr : fptr->instructions) {
                    iptr->accept(&myColorVisitor);
                }
                fptr_out = fptr;
                break;

            } else {

                /*
                Graph coloring failed, need to spill.
                */ 

                for (auto node : uncolored_nodes) {

                    if (printdebug) {
                        std::cerr << "Printing program before spill:\n\n";
                        printFunction(fptr);
                    }

                    std::tuple<std::set<std::string>, L2::Function *,int> spill_result = spillForL2(fptr, node->var, spill_count,stack_counter);
                    std::set<std::string> spilled_set = std::get<0>(spill_result);
                    L2::Function* newFunction = std::get<1>(spill_result);
                    spill_count = std::get<2>(spill_result);
                    seenVariables[node->var->name] = true;
                    fptr = newFunction;
                    spill_count++;
                    
                    if (printdebug) {
                        std::cerr << "Printing program after spill:\n\n";
                        printFunction(fptr);
                    }
                    stack_counter++;

                }   

            }

        }

        return fptr_out;
    }


    std::map<std::string, bool> seenVariables;
    /*
    Token class extensions
    */
    void Program::update_function(Function *oldFunction, Function *newFunction) {
        for (size_t i = 0; i < functions.size(); ++i) {
            if (functions[i] == oldFunction) {
                // Delete or otherwise manage the memory of the old function here if necessary
                // ...
                
                delete oldFunction;
                oldFunction = nullptr; // Good practice to nullify
                
                // Replace the old function with the new one
                functions[i] = newFunction;
                break; // Assuming each function is unique, we can break after the update
            }
        }
    }
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
    Deep Copy Instructions
    */

    Item* Variable::clone() const {
    return new Variable(this->name);
    }

    Item* Register::clone() const {
    return new Register(this->name);
    }

    Item* Number::clone() const {
    return new Number(this->value);
    }

    Item* Name::clone() const {
    return new Name(this->value);
    }

    Item* Label::clone() const {
    return new Label(this->value);
    }

    Item* Operator::clone() const {
    return new Operator(this->sign);
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
    void SpillVisitor::iterReplacementVariable(){
        std::string base = "%S";
        // Assuming replacementVariable format is "%S" followed by a number
        size_t numberStartIndex = base.size();
        std::string numberStr = this->replacementVariable->name.substr(numberStartIndex);
        int number = std::stoi(numberStr); 
        number++; 
        this->replacementVariable = new Variable("%S" + std::to_string(number));
    }
    void SpillVisitor::visit(Instruction_ret *instruction){
        this->copiedInstruction = new Instruction_ret();
    } ;
    void SpillVisitor::visit(Instruction_assignment *instruction){
        Item* d;
        Item* s;
        bool replaceD = replaceIfSpilled(instruction->d);
        bool replaceS = replaceIfSpilled(instruction->s);
        auto varD = dynamic_cast<Variable*>(instruction->d);
        auto varS = dynamic_cast<Variable*>(instruction->s);
        if (replaceD){
            d = this->replacementVariable;
        } else if (varD && varMap.size()>0 && varMap.find(varD->name)!=varMap.end()){
            d = varMap[varD->name];
        } else {
            d = instruction->d->clone();
            if (varD){
                varMap[varD->name] = d;
            }
        }
        if (replaceS){
            s = this->replacementVariable;
        } else if (varS && varMap.size()>0 && varMap.find(varS->name) != varMap.end()){
            s = varMap[varS->name]; // Assuming varMap is correctly defined and accessible
        } else {
            s = instruction->s->clone();
            if (varS){
                varMap[varS->name] = s; // Assuming varMap is correctly defined and accessible
            }
        }
        if (replaceD){
            this->spilledLHS = true;
        }
        if (replaceS){
            this->spilledRHS = true;
        } 
        this->copiedInstruction = new Instruction_assignment(d,s);
    };
    void SpillVisitor::visit(label_Instruction *instruction) {
        auto label = instruction->label->clone();
        this->copiedInstruction = new label_Instruction(label);
    };
    void SpillVisitor::visit(goto_label_instruction *instruction) {
        auto label = instruction->label->clone();
        this->copiedInstruction = new goto_label_instruction(label);
    };
    void SpillVisitor::visit(Call_tenserr_Instruction *instruction) {
        auto F = instruction->F->clone();
        this->copiedInstruction = new Call_tenserr_Instruction(F);
    };
    void SpillVisitor::visit(Call_uN_Instruction *instruction) {
        Item* u;
        bool replaceU = replaceIfSpilled(instruction->u);
        if (replaceU){
            this->spilledRHS = true;
            u = this->replacementVariable;
        } else {
            auto varU = dynamic_cast<Variable*>(instruction->u);
            if (varU && varMap.size() > 0 && varMap.find(varU->name) != varMap.end()) {
                u = varMap[varU->name]; // Assuming varMap is correctly defined and accessible
            } else {
                u = instruction->u->clone();
                if (varU) {
                    varMap[varU->name] = u; // Assuming varMap is correctly defined and accessible
                }
            }
        }
        auto N = instruction->N->clone();
        this->copiedInstruction = new Call_uN_Instruction(u, N);
    };
    void SpillVisitor::visit(Call_print_Instruction *instruction) {
        this->copiedInstruction = new Call_print_Instruction();
    };
    void SpillVisitor::visit(Call_input_Instruction *instruction) {
        this->copiedInstruction = new Call_input_Instruction();
    };
    void SpillVisitor::visit(Call_allocate_Instruction *instruction){
        this->copiedInstruction = new Call_allocate_Instruction();
    } ;
    void SpillVisitor::visit(Call_tuple_Instruction *instruction) {
        this->copiedInstruction = new Call_tuple_Instruction();
    };
    void SpillVisitor::visit(w_increment_decrement *instruction) {
        Item* r;
        bool replaceR = replaceIfSpilled(instruction->r);
        if (replaceR) {
            this->spilledLHS = true;
            this->spilledRHS = true;
            r = this->replacementVariable;
        } else {
            auto varR = dynamic_cast<Variable*>(instruction->r);
            if (varR && varMap.size() > 0 && varMap.find(varR->name) != varMap.end()) {
                r = varMap[varR->name]; // Assuming varMap is correctly defined and accessible
            } else {
                r = instruction->r->clone();
                if (varR) {
                    varMap[varR->name] = r; // Assuming varMap is correctly defined and accessible
                }
            }
        }
        auto symbol = instruction->symbol->clone();
        this->copiedInstruction = new w_increment_decrement(r, symbol);
    };
    void SpillVisitor::visit(w_atreg_assignment *instruction) {
        Item* r1;
        Item* r2;
        Item* r3;
        bool replaceR1 = replaceIfSpilled(instruction->r1);
        bool replaceR2 = replaceIfSpilled(instruction->r2);
        bool replaceR3 = replaceIfSpilled(instruction->r3);

        auto E = instruction->E->clone();

        if (replaceR1) {
            r1 = this->replacementVariable;
            this->spilledLHS = true;
        } else {
            auto varR1 = dynamic_cast<Variable*>(instruction->r1);
            if (varR1 && varMap.size() > 0 && varMap.find(varR1->name) != varMap.end()) {
                r1 = varMap[varR1->name]; // Assuming varMap is correctly defined and accessible
            } else {
                r1 = instruction->r1->clone();
                if (varR1) {
                    varMap[varR1->name] = r1; // Assuming varMap is correctly defined and accessible
                }
            }
        }

        if (replaceR2) {
            r2 = this->replacementVariable;
            this->spilledRHS = true;
        } else {
            auto varR2 = dynamic_cast<Variable*>(instruction->r2);
            if (varR2 && varMap.size() > 0 && varMap.find(varR2->name) != varMap.end()) {
                r2 = varMap[varR2->name]; // Assuming varMap is correctly defined and accessible
            } else {
                r2 = instruction->r2->clone();
                if (varR2) {
                    varMap[varR2->name] = r2; // Assuming varMap is correctly defined and accessible
                }
            }
        }

        if (replaceR3) {
            r3 = this->replacementVariable;
            this->spilledRHS = true;
        } else {
            auto varR3 = dynamic_cast<Variable*>(instruction->r3);
            if (varR3 && varMap.size() > 0 && varMap.find(varR3->name) != varMap.end()) {
                r3 = varMap[varR3->name]; // Assuming varMap is correctly defined and accessible
            } else {
                r3 = instruction->r3->clone();
                if (varR3) {
                    varMap[varR3->name] = r3; // Assuming varMap is correctly defined and accessible
                }
            }
        }

        this->copiedInstruction = new w_atreg_assignment(r1, r2, r3, E);
    };

    void SpillVisitor::visit(Memory_assignment_store *instruction) {
        Item* s;
        Item* dst;
        bool replaceS = replaceIfSpilled(instruction->s);
        bool replaceDST = replaceIfSpilled(instruction->dst); 

        auto M = instruction->M->clone();

        if (replaceS) {
            s = this->replacementVariable;
            this->spilledRHS = true;
        } else {
            auto varS = dynamic_cast<Variable*>(instruction->s);
            if (varS && varMap.find(varS->name) != varMap.end()) {
                s = varMap[varS->name]; // Use the variable mapping if available
            } else {
                s = instruction->s->clone();
                if (varS) {
                    varMap[varS->name] = s; // Update the variable mapping
                }
            }
        }

        if (replaceDST) {
            dst = this->replacementVariable;
            this->spilledRHS = true;
        } else {
            auto varDST = dynamic_cast<Variable*>(instruction->dst);
            if (varDST && varMap.find(varDST->name) != varMap.end()) {
                dst = varMap[varDST->name]; // Use the variable mapping if available
            } else {
                dst = instruction->dst->clone();
                if (varDST) {
                    varMap[varDST->name] = dst; // Update the variable mapping
                }
            }
        }

        this->copiedInstruction = new Memory_assignment_store(dst, s, M);
    };
    void SpillVisitor::visit(Memory_assignment_load *instruction){
        Item* dst;
        Item* x;
        bool replaceD = replaceIfSpilled(instruction->dst);
        bool replaceX = replaceIfSpilled(instruction->x);
        auto M = instruction->M->clone();

        if (replaceD) {
            dst = this->replacementVariable;
            this->spilledLHS = true;
        } else {
            auto varD = dynamic_cast<Variable*>(instruction->dst);
            if (varD && varMap.find(varD->name) != varMap.end()) {
                dst = varMap[varD->name]; // Use the variable mapping if available
            } else {
                dst = instruction->dst->clone();
                if (varD) {
                    varMap[varD->name] = dst; // Update the variable mapping
                }
            }
        }

        if (replaceX) {
            x = this->replacementVariable;
            this->spilledRHS = true;
        } else {
            auto varX = dynamic_cast<Variable*>(instruction->x);
            if (varX && varMap.find(varX->name) != varMap.end()) {
                x = varMap[varX->name]; // Use the variable mapping if available
            } else {
                x = instruction->x->clone();
                if (varX) {
                    varMap[varX->name] = x; // Update the variable mapping
                }
            }
        }

        this->copiedInstruction = new Memory_assignment_load(dst, x, M);
    };

    void SpillVisitor::visit(Memory_arithmetic_load *instruction) {
        Item* dst;
        Item* x;
        bool replaceD = replaceIfSpilled(instruction->dst);
        bool replaceX = replaceIfSpilled(instruction->x);
        auto M = instruction->M->clone();
        auto copied_instruction = instruction->instruction->clone();

        if (replaceD) {
            dst = this->replacementVariable;
            this->spilledLHS = true;
        } else {
            auto varD = dynamic_cast<Variable*>(instruction->dst);
            if (varD && varMap.find(varD->name) != varMap.end()) {
                dst = varMap[varD->name]; // Use the variable mapping if available
            } else {
                dst = instruction->dst->clone();
                if (varD) {
                    varMap[varD->name] = dst; // Update the variable mapping
                }
            }
        }

        if (replaceX) {
            x = this->replacementVariable;
            this->spilledRHS = true;
        } else {
            auto varX = dynamic_cast<Variable*>(instruction->x);
            if (varX && varMap.find(varX->name) != varMap.end()) {
                x = varMap[varX->name]; // Use the variable mapping if available
            } else {
                x = instruction->x->clone();
                if (varX) {
                    varMap[varX->name] = x; // Update the variable mapping
                }
            }
        }

        this->copiedInstruction = new Memory_arithmetic_load(dst, x, copied_instruction, M);
    };

    void SpillVisitor::visit(Memory_arithmetic_store *instruction) {
        Item* dst;
        Item* t;
        bool replaceD = replaceIfSpilled(instruction->dst);
        bool replaceT = replaceIfSpilled(instruction->t);
        auto M = instruction->M->clone();
        auto copied_instruction = instruction->instruction->clone();

        if (replaceD) {
            dst = this->replacementVariable;
            this->spilledLHS = true; // Assuming you want to mark LHS as spilled if replaced
        } else {
            auto varD = dynamic_cast<Variable*>(instruction->dst);
            if (varD && varMap.find(varD->name) != varMap.end()) {
                dst = varMap[varD->name]; // Use the variable mapping if available
            } else {
                dst = instruction->dst->clone();
                if (varD) {
                    varMap[varD->name] = dst; // Update the variable mapping
                }
            }
        }

        if (replaceT) {
            t = this->replacementVariable;
            this->spilledRHS = true;
        } else {
            auto varT = dynamic_cast<Variable*>(instruction->t);
            if (varT && varMap.find(varT->name) != varMap.end()) {
                t = varMap[varT->name]; // Use the variable mapping if available
            } else {
                t = instruction->t->clone();
                if (varT) {
                    varMap[varT->name] = t; // Update the variable mapping
                }
            }
        }

        // Creating the new Memory_arithmetic_store instruction with potentially replaced items.
        this->copiedInstruction = new Memory_arithmetic_store(dst, t, copied_instruction, M);
    };
    void SpillVisitor::visit(cmp_Instruction *instruction) {
        Item* dst;
        Item* t1;
        Item* method;
        Item* t2;
        bool replaceD = replaceIfSpilled(instruction->dst);
        bool replaceT1 = replaceIfSpilled(instruction->t1);
        bool replaceM = replaceIfSpilled(instruction->method);    
        bool replaceT2 = replaceIfSpilled(instruction->t2);    

        // Handling dst replacement or cloning with varMap update if necessary
        if (replaceD) {
            dst = this->replacementVariable;
            this->spilledLHS = true;
        } else {
            auto varD = dynamic_cast<Variable*>(instruction->dst);
            if (varD && varMap.find(varD->name) != varMap.end()) {
                dst = varMap[varD->name];
            } else {
                dst = instruction->dst->clone();
                if (varD) {
                    varMap[varD->name] = dst;
                }
            }
        }

        // Handling t1 replacement or cloning with varMap update if necessary
        if (replaceT1) {
            t1 = this->replacementVariable;
            this->spilledRHS = true;
        } else {
            auto varT1 = dynamic_cast<Variable*>(instruction->t1);
            if (varT1 && varMap.find(varT1->name) != varMap.end()) {
                t1 = varMap[varT1->name];
            } else {
                t1 = instruction->t1->clone();
                if (varT1) {
                    varMap[varT1->name] = t1;
                }
            }
        }

        // Assuming 'method' does not require varMap handling if it's not a variable
        method = replaceM ? this->replacementVariable : instruction->method->clone();

        // Handling t2 replacement or cloning with varMap update if necessary
        if (replaceT2) {
            t2 = this->replacementVariable;
            this->spilledRHS = true; // Assuming you want to mark RHS as spilled if t2 is replaced
        } else {
            auto varT2 = dynamic_cast<Variable*>(instruction->t2);
            if (varT2 && varMap.find(varT2->name) != varMap.end()) {
                t2 = varMap[varT2->name];
            } else {
                t2 = instruction->t2->clone();
                if (varT2) {
                    varMap[varT2->name] = t2;
                }
            }
        }

        // Creating the new cmp_Instruction with potentially replaced or updated items
        this->copiedInstruction = new cmp_Instruction(dst, t2, method, t1);
    }
    void SpillVisitor::visit(cjump_cmp_Instruction *instruction){
        Item* t1;
        Item* cmp;
        Item* t2;
        Item* label;
        bool replaceT2 = replaceIfSpilled(instruction->t2);
        bool replaceCMP = replaceIfSpilled(instruction->cmp);
        bool replaceT1 = replaceIfSpilled(instruction->t1);
        // Assuming labels are not variables and thus not subject to spilling/replacement

        // Handling t2 replacement or cloning with varMap update if necessary
        if (replaceT2) {
            t2 = this->replacementVariable;
            this->spilledRHS = true;
        } else {
            auto varT2 = dynamic_cast<Variable*>(instruction->t2);
            if (varT2 && varMap.find(varT2->name) != varMap.end()) {
                t2 = varMap[varT2->name];
            } else {
                t2 = instruction->t2->clone();
                if (varT2) {
                    varMap[varT2->name] = t2;
                }
            }
        }

        // Handling cmp replacement or cloning
        cmp = replaceCMP ? this->replacementVariable : instruction->cmp->clone();

        // Handling t1 replacement or cloning with varMap update if necessary
        if (replaceT1) {
            t1 = this->replacementVariable;
            this->spilledRHS = true;
        } else {
            auto varT1 = dynamic_cast<Variable*>(instruction->t1);
            if (varT1 && varMap.find(varT1->name) != varMap.end()) {
                t1 = varMap[varT1->name];
            } else {
                t1 = instruction->t1->clone();
                if (varT1) {
                    varMap[varT1->name] = t1;
                }
            }
        }

        // Cloning the label as is, since it doesn't get spilled or replaced
        label = instruction->label; // Assuming Label* type doesn't require cloning

        // Creating the new cjump_cmp_Instruction with potentially replaced or updated items
        this->copiedInstruction = new cjump_cmp_Instruction(t2, cmp, t1, label);
    };

    void SpillVisitor::visit(stackarg_assignment *instruction) {
        Item* w;
        bool replaceW = replaceIfSpilled(instruction->w);
        
        // Handling w replacement or cloning with varMap update if necessary
        if (replaceW) {
            w = this->replacementVariable;
            this->spilledLHS = true;
        } else {
            auto varW = dynamic_cast<Variable*>(instruction->w);
            if (varW && varMap.find(varW->name) != varMap.end()) {
                w = varMap[varW->name]; // Use the variable mapping if available
            } else {
                w = instruction->w->clone();
                if (varW) {
                    varMap[varW->name] = w; // Update the variable mapping
                }
            }
        }

        // Assuming M is a memory offset or similar and not subject to varMap replacement
        auto M = instruction->M->clone();

        // Creating the new stackarg_assignment instruction with potentially replaced or updated w
        this->copiedInstruction = new stackarg_assignment(w, M);
    }

    void SpillVisitor::visit(AOP_assignment *instruction) {
        Item *dst, *src, *method;

        bool replaceD = replaceIfSpilled(instruction->dst);
        bool replaceSrc = replaceIfSpilled(instruction->src);
        // Assuming method is an operation and not a variable to replace, we clone directly.
        method = instruction->method->clone();

        // Handling dst replacement or cloning with varMap update if necessary
        if (replaceD) {
            dst = this->replacementVariable;
            this->spilledLHS = true;
            this->spilledRHS = true;
        } else {
            auto varDst = dynamic_cast<Variable*>(instruction->dst);
            if (varDst && varMap.find(varDst->name) != varMap.end()) {
                dst = varMap[varDst->name]; // Use the variable mapping if available
            } else {
                dst = instruction->dst->clone();
                if (varDst) {
                    varMap[varDst->name] = dst; // Update the variable mapping
                }
            }
        }

        // Handling src replacement or cloning with varMap update if necessary
        if (replaceSrc) {
            src = this->replacementVariable;
            this->spilledRHS = true;
        } else {
            auto varSrc = dynamic_cast<Variable*>(instruction->src);
            if (varSrc && varMap.find(varSrc->name) != varMap.end()) {
                src = varMap[varSrc->name]; // Use the variable mapping if available
            } else {
                src = instruction->src->clone();
                if (varSrc) {
                    varMap[varSrc->name] = src; // Update the variable mapping
                }
            }
        }

        // Spilling flags are adjusted above based on whether replacements were made
        this->copiedInstruction = new AOP_assignment(method, dst, src);
    }

    void SpillVisitor::visit(SOP_assignment *instruction) {
        // Clone the method directly as it's likely an operation rather than a variable.
        auto method = instruction->method->clone();

        // Check if dst and src need to be replaced due to spilling
        bool replaceDst = replaceIfSpilled(instruction->dst);
        bool replaceSrc = replaceIfSpilled(instruction->src);
    
        // Replace or clone dst, update varMap if necessary
        Item *dst;
        if (replaceDst) {
            dst = this->replacementVariable;
            this->spilledRHS = true;
            this->spilledLHS = true;
        } else {
            auto varDst = dynamic_cast<Variable*>(instruction->dst);
            if (varDst && varMap.find(varDst->name) != varMap.end()) {
                dst = varMap[varDst->name]; // Use the variable mapping if available
            } else {
                dst = instruction->dst->clone();
                if (varDst) {
                    varMap[varDst->name] = dst; // Update the variable mapping
                }
            }
        }

        // Replace or clone src, update varMap if necessary
        Item *src;
        if (replaceSrc) {
            src = this->replacementVariable;
            this->spilledRHS = true;
        } else {
            auto varSrc = dynamic_cast<Variable*>(instruction->src);
            if (varSrc && varMap.find(varSrc->name) != varMap.end()) {
                src = varMap[varSrc->name]; // Use the variable mapping if available
            } else {
                src = instruction->src->clone();
                if (varSrc) {
                    varMap[varSrc->name] = src; // Update the variable mapping
                }
            }
        }

        // Note that spilledRHS is already set true if either dst or src is replaced.
        // Create a new SOP_assignment with the potentially replaced or updated dst and src, along with the cloned method.
        this->copiedInstruction = new SOP_assignment(method, dst, src);
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
        std::cerr << instruction->dst->print() << " <- mem " << instruction->x->print() << " " << instruction->M->print() << "\n";
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

    /*
    Utility Functions
    */
    void printFunction(Function *fptr) {
        PrintVisitor* myPrintVisitor = new L2::PrintVisitor();
        for (auto iptr : fptr->instructions) {
            iptr->accept(myPrintVisitor);
        }
    }

}
