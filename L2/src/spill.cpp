#include <map>
#include <set>
#include <string>
#include <stack>
#include <L2.h>
#include <graph_coloring.h>
#include <code_generator.h>
#include <interference_graph.h>

namespace L2{
    void spillForL1(Program &p, Variable* spilledVar){
        Function* f = p.functions[0]; 
        std::string temp = "%S";
        int count = 0;
        std::string result = temp + std::to_string(count);
        Variable* tempVar = new Variable(result);
        Number* stack = new Number(0);
        SpillVisitor * visitor = new SpillVisitor(spilledVar,tempVar,0);
        for (size_t i = 0; i < f->instructions.size(); ++i) {
            auto instruction = f->instructions[i];
            instruction->accept(visitor);
            if (tempVar->name != visitor->replacementVariable->name) {
                Variable* var = f->variable_allocator.allocate_variable("rsp", VariableType::reg);
                Instruction* instruction1 = new Memory_assignment_store(var, tempVar, stack);
                Instruction* instruction2 = new Memory_assignment_load(visitor->replacementVariable, var, stack);
                f->instructions.insert(f->instructions.begin() + i + 1, instruction1);
                f->instructions.insert(f->instructions.begin() + i + 2, instruction2);
                i += 2;
                tempVar = visitor->replacementVariable;
            }
        }

    }
};