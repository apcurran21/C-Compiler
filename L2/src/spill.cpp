#include <map>
#include <set>
#include <string>
#include <stack>
#include <L2.h>
#include <graph_coloring.h>
#include <code_generator.h>
#include <interference_graph.h>

namespace L2{
    // bool spillForL2(Program &p, Variable* spilledVar){
    bool spillForL2(Function* f, Variable* spilledVar) {    
        // Function* f = p.functions[0]; 
        std::string temp = "%S";

        int temp_var = -1;
        std::string result = temp + std::to_string(temp_var);
        Variable* initial_replacement = new Variable(result);

        Number* stack = new Number(0);
        SpillVisitor * visitor = new SpillVisitor(spilledVar,initial_replacement);
        bool changed = false;
        int assignment_counter = 0;
        for (size_t i = 0; i < f->instructions.size(); ++i) {
            auto instruction = f->instructions[i];
            auto assignment_instruction = dynamic_cast<Instruction_assignment*>(instruction);
            auto cjump_instruction = dynamic_cast<cjump_cmp_Instruction*>(instruction);
            instruction->accept(visitor);
            if (visitor->spilled) {
                if (assignment_instruction){
                    Variable* var = f->variable_allocator.allocate_variable("rsp", VariableType::reg);
                    Instruction * instruction1 = new Memory_assignment_store(var,visitor->replacementVariable, stack);
                    f->instructions.insert(f->instructions.begin() + i + 1, instruction1);
                    i += 1;
                    
                    if (i+1< f->instructions.size()){
                        auto check_instruction = f->instructions[i+1];
                        auto check_memory_store = dynamic_cast<Memory_assignment_store*>(check_instruction);
                        while (i+1<f->instructions.size()){
                            if (!check_memory_store || check_memory_store->dst->print() != "rsp"){
                                break;
                            }
                            i++;
                            check_memory_store = dynamic_cast<Memory_assignment_store*>(f->instructions[i+1]);
                        }
                        auto check_instruct = f->instructions[i+1];
                        auto instruct = dynamic_cast<Instruction_ret*>(check_instruct);
                        if (!instruct){
                            Variable* tempVar = new Variable(temp + std::to_string(visitor->count+1));
                            Instruction* instruction2 = new Memory_assignment_load(tempVar, var, stack);
                            f->instructions.insert(f->instructions.begin() + i + 1, instruction2);
                            visitor->count++;
                            visitor->replacementVariable = tempVar;
                        }
                    }
                } else if (cjump_instruction){
                    Variable* var = f->variable_allocator.allocate_variable("rsp", VariableType::reg);
                    Variable* tempVar = new Variable(temp + std::to_string(visitor->count-1));
                    i++;
                    while (i<f->instructions.size()){
                        auto label_instruct = dynamic_cast<label_Instruction*>(f->instructions[i]);
                        if (!label_instruct){
                            break;
                        }
                        i++;
                    }
                    if (i+1< f->instructions.size()){
                        auto check_instruction = f->instructions[i+1];
                        auto instruct = dynamic_cast<Instruction_ret*>(check_instruction);
                        
                        if (!instruct){ 
                            Instruction* instruction2 = new Memory_assignment_load(visitor->replacementVariable, var, stack);
                            f->instructions.insert(f->instructions.begin() + i , instruction2);
                        }
                    }
                } else {
                    Variable* var = f->variable_allocator.allocate_variable("rsp", VariableType::reg);
                    Variable* tempVar = new Variable(temp + std::to_string(visitor->count-1));
                    Instruction * instruction1 = new Memory_assignment_store(var,tempVar, stack);
                    f->instructions.insert(f->instructions.begin() + i + 1, instruction1);
                    i += 1;
                    if (i+1< f->instructions.size()){
                        auto check_instruction = f->instructions[i+1];
                        auto instruct = dynamic_cast<Instruction_ret*>(check_instruction);
                        if (!instruct){ 
                            Instruction* instruction2 = new Memory_assignment_load(visitor->replacementVariable, var, stack);
                            f->instructions.insert(f->instructions.begin() + i + 1, instruction2);
                            i +=1;

                        }
                    }
                }
                

                changed = true;
                visitor->spilled = false;
            }
        }
        return changed;

    }
};