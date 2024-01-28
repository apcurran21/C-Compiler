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
    // In_Out_Store::In_Out_Store(int num_functions, std::vector<int> nums_instructions) : 
    //     In_Set(num_functions),
    //     Out_Set(num_functions)
    // {
    //     for (int i = 0; i < num_functions; i++) {
    //         In_Set[i].resize(nums_instructions[i]);
    //         Out_Set[i].resize(nums_instructions[i]);
    //     }
    // };
    // int In_Out_Store::get_size(SetType from_where, int function_index, int instruction_index) {
    //     switch (from_where) {
    //         case in:
    //             return In_Set[function_index][instruction_index].size();
    //             break;
    //         case out:
    //             return Out_Set[function_index][instruction_index].size();
    //             break;
    //     }
    // }

    /*
    New In and Out Set Storage
    */
    In_Out_Store::In_Out_Store(Program *p) {
        for (auto fptr : p->functions) {
            std::unordered_map<Instruction*>, std::set<Variable*> in_set_map;
            std::unordered_map<Instruction*>, std::set<Variable*> out_set_map;
            for (auto iptr : fptr->instructions) {
                in_set_map[iptr] = std::set<Variable*>();
                out_set_map[iptr] = std::set<Variable*>();
            }
            In_Set.push_back(in_set_map);
            Out_Set.push_back(out_set_map);
        }
    }
    

    /* 
    Gen and Kill Sets - Note that we aren't really using this class anymore
    */
    // Gen_Kill_Store::Gen_Kill_Store(int num_functions, std::vector<int> nums_instructions) : 
    //     Gen_Set(num_functions),
    //     Kill_Set(num_functions)
    // {
    //     for (int i = 0; i < num_functions; i++) {
    //         Gen_Set[i].resize(nums_instructions[i]);
    //         Kill_Set[i].resize(nums_instructions[i]);
    //     }
    // };
    // int Gen_Kill_Store::get_size(SetType from_where, int function_index, int instruction_index) {
    //     switch (from_where) {
    //         case in:
    //             return Gen_Set[function_index][instruction_index].size();
    //             break;
    //         case out:
    //             return Kill_Set[function_index][instruction_index].size();
    //             break;
    //     }
    // }


    void liveness_analysis(Program *p){


        /*
        Create objects to store the Gen and Kill sets for our program.
        */
        // std::vector<int> num_instructions_per_function(p.functions.size());
        // for (int i = 0; i < p.functions.size(); i++) {
        //     num_instructions_per_function[i] = p.functions[i]->instructions.size();
        // }
        // Gen_Kill_Store gen_kill_sets = Gen_Kill_Store(p.functions.size(), num_instructions_per_function);
        /*
        Create objects to store the In and Out sets for our program.
        */
        // In_Out_Store in_out_sets = In_Out_Store(p.functions.size(), num_instructions_per_function);

        In_Out_Store in_out_sets = In_Out_Store();

        /*
        Run the liveness analysis algorithm
        */
        for (int i = 0; i < p.functions.size(); i++) {
            auto fptr = p.functions[i];
            if (debug) std::cerr << "Running liveness analysis on a new function..." << std::endl;

            bool changed;
            do {
                changed = false;
                // for (int j = 0; j < fptr->instructions.size(); j++) {
                for (auto iptr : fptr->instructions) {
                    // note that iptr should be of type Instruction*
                    // auto iptr = fptr->instructions[j];
                    if (debug) std::cerr << "computing In and Out sets for the current instruction..." << std::endl;

                    /*
                        Define the Gen and Kill sets for the current instruction
                    */
                    std::set<Variable*> Gen_Set = iptr->used;
                    std::set<Variable*> Kill_Set = iptr->defined;

                    /*
                        Define state of the sets before any potential changes are made
                    */
                    // std::set<Variable*> in_set_prev = in_out_sets.In_Set[i][j];
                    // std::set<Variable*> out_set_prev = in_out_sets.Out_Set[i][j];
                    std::set<Variable*> in_set_prev = in_out_sets.In_Set[i][iptr];
                    std::set<Variable*> out_set_prev = in_out_sets.Out_Set[i][iptr];

                    /*
                        Get pointers to the sets so that we don't have to keep array accessing
                    */
                    // std::set<Variable>* in_ptr = &in_out_sets.In_Set[i][j];
                    // std::set<Variable>* out_ptr = &in_out_sets.Out_Set[i][j];
                    std::set<Variable>* in_ptr = &in_out_sets.In_Set[i][iptr];
                    std::set<Variable>* out_ptr = &in_out_sets.Out_Set[i][iptr];

                    /*
                        Do the set operations
                    */
                    std::set<Variable*> In_Result;
                    std::set<Variable*> Out_Kill_Diff;
                    std::set_difference(
                        out_ptr->begin(), out_ptr->end(),
                        Kill_Set.begin(), Kill_Set->end(),
                        std::inserter(Out_Kill_Diff, Out_Kill_Diff.begin())
                    );
                    std::set_union(
                        Gen_Set.begin(), Gen_Set.end(),
                        Out_Kill_Diff.begin(), Out_Kill_Diff.end(),
                        std::inserter(In_Result, In_Result.begin())
                    );

                    std::set<Variable*> Out_Result;
                    for (auto successor : iptr->successors) {
                        // note that successor should be of type Instruction*
                        std::set<Variable*> successor_in_set = in_out_sets.In_Set[i][successor];
                        std::set<Variable*> temp_union_set;
                        std::set_union(
                            Out_Union_Result.begin(), Out_Union_Result.end(),
                            successor_in_set.begin(), successor_in_set.end(),
                            std::inserter(temp_union_set, temp_union_set.begin());
                        )
                        Out_Union_Result = std::move(temp_union_set);
                    }

                    *in_ptr = In_Result;
                    *out_ptr = Out_Result;

                    /*
                        Check against the initial state after performing the operations.
                    */

                    changed = (in_set_prev != *in_ptr) || (out_set_prev != *out_ptr);
                }
            } while (changed);
            
        }




        /*
        Print the contents of our freshly computed In and Out sets to the file
        */

        for (int f = 0; p->functions.size(); i++) {
            std::cout << "(\n";
            Function* fptr = p->functions[f];
            std::unordered_map<Instruction*, Variable*> in_map = in_out_sets.In_Set[f];
            std::cout << "(in\n";
            for (auto iptr : fptr->instructions) {
                std::cout << "(";
                for (auto variable = in_map[iptr].begin(); variable != in_map[iptr].end(); variable++) {
                    std::cout << *variable << " ";
                }
                std::cout << ")";
            }
            std::cout << ")\n\n";

            std::unordered_map<Instruction*, Variable*> out_map = in_out_sets.Out_Set[f];
            std::cout << "(out\n";
            for (auto iptr : fptr->instructions) {
                std::cout << "(";
                for (auto variable = out_map[iptr].begin(); variable != out_map[iptr].end(); variable++) {
                    std::cout << *variable << " ";
                }
                std::cout << ")"
            }
            std::cout << ")\n";
            
            std::cout << ")\n"
        }
    }

}