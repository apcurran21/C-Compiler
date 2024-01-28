#include <string>
#include <iostream>
#include <fstream>

#include <liveness_analysis.h>
#include "L2.h"

using namespace std;

// use 1 for debug statements, 0 for no printing
// int debug = 1;

namespace L2{

    /*
    Going to try not using the visitor pattern for liveness
    */

    // void LiveAnalysisVisitor::visit(Function &function){};
        
    // void LiveAnalysisVisitor::visit(Instruction &instruction){};

    // void LiveAnalysisVisitor::visit(Instruction_ret &instruction){};

    // void LiveAnalysisVisitor::visit(Instruction_assignment &instruction){};

    // void LiveAnalysisVisitor::visit(label_Instruction &instruction){};

    // void LiveAnalysisVisitor::visit(goto_label_instruction &instruction){};

    // void LiveAnalysisVisitor::visit(Call_tenserr_Instruction &instruction){};

    // void LiveAnalysisVisitor::visit(Call_uN_Instruction &instruction){};

    // void LiveAnalysisVisitor::visit(Call_print_Instruction &instruction){};

    // void LiveAnalysisVisitor::visit(Call_input_Instruction &instruction){};

    // void LiveAnalysisVisitor::visit(Call_allocate_Instruction &instruction){};

    // void LiveAnalysisVisitor::visit(Call_tuple_Instruction &instruction){};

    // void LiveAnalysisVisitor::visit(w_increment_decrement &instruction){};

    // void LiveAnalysisVisitor::visit(w_atreg_assignment &instruction){};

    // void LiveAnalysisVisitor::visit(Memory_assignment_store &instruction){};

    // void LiveAnalysisVisitor::visit(Memory_assignment_load &instruction){};

    // void LiveAnalysisVisitor::visit(Memory_arithmetic_load &instruction){};

    // void LiveAnalysisVisitor::visit(Memory_arithmetic_store &instruction){};

    // void LiveAnalysisVisitor::visit(cmp_Instruction &instruction){};

    // void LiveAnalysisVisitor::visit(cjump_cmp_Instruction &instruction){};

    // void LiveAnalysisVisitor::visit(stackarg_assignment &instruction){};

    // void LiveAnalysisVisitor::visit(AOP_assignment &instruction){};

    // void LiveAnalysisVisitor::visit(SOP_assignment &instruction){};

    /*
    In and Out Sets
    */
    In_Out_Store::In_Out_Store(int num_functions, std::vector<int> nums_instructions) : 
        In_Set(num_functions),
        Out_Set(num_functions)
    {
        for (int i = 0; i < num_functions; i++) {
            In_Set[i].resize(nums_instructions[i]);
            Out_Set[i].resize(nums_instructions[i]);
        }
    };
    int In_Out_Store::get_size(SetType from_where, int function_index, int instruction_index) {
        switch (from_where) {
            case in:
                return In_Set[function_index][instruction_index].size();
                break;
            case out:
                return Out_Set[function_index][instruction_index].size();
                break;
        }
    }

    void liveness_analysis(Program p){

        /*
        Create objects to store the In and Out sets for our program.
        */
        std::vector<int> num_instructions_per_function(p.functions.size());
        for (int i = 0; i < p.functions.size(); i++) {
            num_instructions_per_function[i] = p.functions[i]->instructions.size();
        }
        In_Out_Store sets = In_Out_Store(p.functions.size(), num_instructions_per_function);

        /*
        Run the liveness analysis algorithm
        */
        for (int i = 0; i < p.functions.size(); i++) {
            auto fptr = p.functions[i];
            if (debug) std::cerr << "Running liveness analysis on a new function..." << std::endl;

            /*
            Do CFG to compute the Gen and Kill sets for each instruction
            */

            /*
            Compute the In and Out sets for each instruction
            */
            bool changed;
            do {
                changed = false;
                for (int j = 0; j < fptr->instructions.size(); j++) {
                    auto iptr = fptr->instructions[j];
                    if (debug) std::cerr << "computing In and Out sets for the current instruction..." << std::endl;

                    int In_size_prev = sets.get_size(in, i, j);
                    int Out_size_prev = sets.get_size(out, i, j);

                    std::set<Variable*> In_union_set;
                    std::set_union(
                    )

                }
            } while (changed);
            
        }




        /*
        Print the contents of our freshly computed In and Out sets to the file
        */
        // std::cout << "(in\n";
        // for (auto &inSet : IN) {
        //     std::cout << "(";
        //     for (auto &reg : inSet) {
        //         std::cout << reg << " ";
        //     }
        //     std::cout << ")\n";
        // }
        // std::cout << ")\n\n(out\n";
        // for (auto &outSet : OUT) {
        //     std::cout << "(";
        //     for (auto &reg : outSet) {
        //         std::cout << reg << " ";
        //     }
        //     std::cout << ")\n";
        // }
        // std::cout << ")\n\n";
    }

}