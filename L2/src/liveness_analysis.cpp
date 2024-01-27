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

    /*
    In and Out Sets
    */
    In_Out_Store::In_Out_Store(int num_functions, int num_instructions) : 
        In_Set(num_functions, std::vector<std::set<Item*>>(num_instructions)),
        Out_Set(num_functions, std::vector<std::set<Item*>>(num_instructions));
    {};

    void liveness_analysis(Program p){

        /*
        Run the liveness analysis algorithm
        */
        for (auto *fptr : p.functions) {
            if (debug) std::cerr << "Running liveness analysis on a new function..." << std::endl;


            /*
            Do CFG to compute the Gen and Kill sets for each instruction
            */

            /*
            Probably don't need to initialize the In and Out sets to empty here, can just do this in the Instruction constructor
            */

            /*
            Compute the In and Out sets for each instruction
            */
            bool changed;
            do {
                changed = false;
                for (int i = 0; i < fptr->instructions.size(); i++) {
                    if (debug) std::cerr << "computing In and Out sets for the current instruction..." << std::endl;
                    auto iptr = fptr->instructions[i];

                    /*
                    Action depends on how we store the In, Out sets
                    */

                }
            } while (changed);
            
        }




        /*
        Print the contents of our freshly computed In, Out set to the output file
        */
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