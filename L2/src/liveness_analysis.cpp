#include <string>
#include <iostream>
#include <fstream>

#include <liveness_analysis.h>
#include "L2.h"

using namespace std;

// use 1 for debug statements, 0 for no printing
// int debug = 1;

namespace L2{
    void LiveAnalysisVisitor::visit(Function &function){};

    void LiveAnalysisVisitor::visit(Instruction &instruction){};

    void LiveAnalysisVisitor::visit(Instruction_ret &instruction){};

    void LiveAnalysisVisitor::visit(Instruction_assignment &instruction){};

    void LiveAnalysisVisitor::visit(label_Instruction &instruction){};

    void LiveAnalysisVisitor::visit(goto_label_instruction &instruction){};

    void LiveAnalysisVisitor::visit(Call_tenserr_Instruction &instruction){};

    void LiveAnalysisVisitor::visit(Call_uN_Instruction &instruction){};

    void LiveAnalysisVisitor::visit(Call_print_Instruction &instruction){};

    void LiveAnalysisVisitor::visit(Call_input_Instruction &instruction){};

    void LiveAnalysisVisitor::visit(Call_allocate_Instruction &instruction){};

    void LiveAnalysisVisitor::visit(Call_tuple_Instruction &instruction){};

    void LiveAnalysisVisitor::visit(w_increment_decrement &instruction){};

    void LiveAnalysisVisitor::visit(w_atreg_assignment &instruction){};

    void LiveAnalysisVisitor::visit(Memory_assignment_store &instruction){};

    void LiveAnalysisVisitor::visit(Memory_assignment_load &instruction){};

    void LiveAnalysisVisitor::visit(Memory_arithmetic_load &instruction){};

    void LiveAnalysisVisitor::visit(Memory_arithmetic_store &instruction){};

    void LiveAnalysisVisitor::visit(cmp_Instruction &instruction){};

    void LiveAnalysisVisitor::visit(cjump_cmp_Instruction &instruction){};

    void LiveAnalysisVisitor::visit(stackarg_assignment &instruction){};

    void LiveAnalysisVisitor::visit(AOP_assignment &instruction){};

    void LiveAnalysisVisitor::visit(SOP_assignment &instruction){};

    void liveness_analysis(){
        std::cout << "(in\n";
        for (auto &inSet : IN) {
            std::cout << "(";
            for (auto &reg : inSet) {
                std::cout << reg << " ";
            }
            std::cout << ")\n";
        }
        std::cout << ")\n\n(out\n";
        for (auto &outSet : OUT) {
            std::cout << "(";
            for (auto &reg : outSet) {
                std::cout << reg << " ";
            }
            std::cout << ")\n";
        }
        std::cout << ")\n\n";
    }

}