#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <liveness_analysis.h>
#include "L2.h"


using namespace std;

// use 1 for debug statements, 0 for no printing
int debug = 0;

namespace L2{

    /*
    Utility vectors for calling convention checks
    */

    std::vector<std::string> arguments_vec{
            "rdi",
            "rsi",
            "rdx",
            "rcx",
            "r8",
            "r9"
    };
    std::vector<std::string> caller_save_vec{
            "r10",
            "r11",
            "r8",
            "r9",
            "rax",
            "rcx",
            "rdi",
            "rdx",
            "rsi"
    };
    std::vector<std::string> callee_save_vec{
            "r12",
            "r13",
            "r14",
            "r15",
            "rbp",
            "rbx"
    };

    /*
    In and Out Set Storage
    */
    In_Out_Store::In_Out_Store(Program *p) {
        for (auto functionptr : p->functions) {
            std::unordered_map<Instruction*, std::set<Variable*>> in_set_map;
            std::unordered_map<Instruction*, std::set<Variable*>> out_set_map;
            for (auto instructionptr : functionptr->instructions) {
                in_set_map[instructionptr] = std::set<Variable*>();
                out_set_map[instructionptr] = std::set<Variable*>();
            }
            In_Set.push_back(in_set_map);
            Out_Set.push_back(out_set_map);
        }
    }
    void In_Out_Store::print_sets(int function_index, Instruction* instruction_ptr) {
        std::cerr << "In Set: ";
        for (auto variable_ptr : In_Set[function_index][instruction_ptr]) {
            std::cerr << variable_ptr->print() << ", ";
        }
        std::cerr << std::endl << "Out Set: ";
        for (auto variable_ptr : Out_Set[function_index][instruction_ptr]) {
            std::cerr << variable_ptr->print() << ", ";
        }
        std::cerr << std::endl;
    }

    /*
    Gen and Kill Set Storage
    */
    Gen_Kill_Store::Gen_Kill_Store(Program *p) {
        for (auto functionptr : p->functions) {
            std::unordered_map<Instruction*, std::set<Variable*>> gen_set_map;
            std::unordered_map<Instruction*, std::set<Variable*>> kill_set_map;
            for (auto instructionptr : functionptr->instructions) {
                gen_set_map[instructionptr] = std::set<Variable*>();
                kill_set_map[instructionptr] = std::set<Variable*>();
            }
            Gen_Set.push_back(gen_set_map);
            Kill_Set.push_back(kill_set_map);
        }
    }
    void Gen_Kill_Store::print_sets(int function_index, Instruction* instruction_ptr) {
        std::cerr << "Gen Set: ";
        for (auto variable_ptr : Gen_Set[function_index][instruction_ptr]) {
            std::cerr << variable_ptr->print() << ", ";
        }
        std::cerr << std::endl << "Kill Set: ";
        for (auto variable_ptr : Kill_Set[function_index][instruction_ptr]) {
            std::cerr << variable_ptr->print() << ", ";
        }
        std::cerr << std::endl;
    }
    

    /*
    Full Liveness Analysis
    */
    // LivenessResult liveness_analysis(Program *p, bool print){
    // Curr_F_Liveness liveness_analysis(Program *p, int function_index, Gen_Kill_Store gen_kill_sets, In_Out_Store in_out_sets, bool print) {
    Curr_F_Liveness liveness_analysis(Function* fptr, bool print) {
        if (debug) std::cerr << "Running Liveness Analysis..." << std::endl;

        /*
        Initialize sets to hold each instruction's gen, kill, in, and out.
        */
        std::unordered_map<Instruction*, std::set<Variable*>> gen_sets;
        std::unordered_map<Instruction*, std::set<Variable*>> kill_sets;
        std::unordered_map<Instruction*, std::set<Variable*>> in_sets;
        std::unordered_map<Instruction*, std::set<Variable*>> out_sets;

        /*
        Run the liveness analysis algorithm for the current function
        */
        // Function* fptr = p->functions[function_index];
        if (debug) std::cerr << "Running liveness analysis on a new function..." << std::endl;
        
        /*
        Calculate Uses and Defs sets for each instruction in the current function (calls UseDefs Visitor)
        */
        fptr->calculateUseDefs();

        /*
        Calcuate Gen and Kill sets for each instruction in the current function using the Uses/Defs sets and calling convention rules
        */
        for (auto instruction_ptr : fptr->instructions) {
            if (debug) std::cerr << "ENTERED" << std::endl;
            /*
            Define pointer references to the current instruction's Gen/Kill sets for convenience
            */
            // std::set<Variable*>* gen_set_ptr = &gen_kill_sets.Gen_Set[function_index][instruction_ptr];
            // std::set<Variable*>* kill_set_ptr = &gen_kill_sets.Kill_Set[function_index][instruction_ptr];
            std::set<Variable*>* gen_set_ptr = &gen_sets[instruction_ptr];
            std::set<Variable*>* kill_set_ptr = &kill_sets[instruction_ptr];

            /*
            Place Uses into Gen
            */
            for (auto variable_ptr : instruction_ptr->used) {
                gen_set_ptr->insert(variable_ptr);
            }
            /*
            Place Defs into Kill
            */
            for (auto variable_ptr : instruction_ptr->defined) {
                kill_set_ptr->insert(variable_ptr);
            }
            /*
            Dynamic cast to check for special calling convention cases
            */
            Call_uN_Instruction* call_uN_instruction_ptr = dynamic_cast<Call_uN_Instruction*>(instruction_ptr);
            if (call_uN_instruction_ptr) {
                /*
                --- call u N ---
                Gen <- {u, args used}
                Kill <- {caller-saved}
                */
                // Gen, finding 'u' 
                Variable* variable_ptr = dynamic_cast<Variable*>(call_uN_instruction_ptr->u);
                if (variable_ptr) {
                    Register* register_ptr = dynamic_cast<Register*>(variable_ptr);
                    if (register_ptr) {
                        gen_set_ptr->insert(fptr->variable_allocator.allocate_variable(register_ptr->name, VariableType::reg));
                    } else {
                        gen_set_ptr->insert(fptr->variable_allocator.allocate_variable(variable_ptr->name, VariableType::var));
                    }
                }
                // Gen, finding 'args used'
                Number* num = dynamic_cast<Number*>(call_uN_instruction_ptr->N);
                for (int i = 0; i < num->value; i++) {
                    if (i>5){
                        break;
                    }
                    gen_set_ptr->insert(fptr->variable_allocator.allocate_variable(arguments_vec[i], VariableType::reg));
                }
                // Kill, finding 'caller-saved'
                for (auto register_string : caller_save_vec) {
                    kill_set_ptr->insert(fptr->variable_allocator.allocate_variable(register_string, VariableType::reg));
                }
            }
            /*
            --- call RUNTIME N ---
            Gen <- {args used}
            Kill <- {caller-saved}
            */
            Call_print_Instruction* call_print_instruction_ptr = dynamic_cast<Call_print_Instruction*>(instruction_ptr);
            if (call_print_instruction_ptr) {
                /*
                call print 1
                */
                // Gen, finding 'args used'
                gen_set_ptr->insert(fptr->variable_allocator.allocate_variable(arguments_vec[0], VariableType::reg));
                // Kill, finding 'caller-saved'
                for (auto register_string : caller_save_vec) {
                    kill_set_ptr->insert(fptr->variable_allocator.allocate_variable(register_string, VariableType::reg));
                }
            }
            Call_input_Instruction* call_input_instruction_ptr = dynamic_cast<Call_input_Instruction*>(instruction_ptr);
            if (call_input_instruction_ptr) {
                /*
                call input 1
                */
                // Kill, finding 'caller-saved'
                for (auto register_string : caller_save_vec) {
                    kill_set_ptr->insert(fptr->variable_allocator.allocate_variable(register_string, VariableType::reg));
                }
            }
            Call_allocate_Instruction* call_allocate_instruction_ptr = dynamic_cast<Call_allocate_Instruction*>(instruction_ptr);
            if (call_allocate_instruction_ptr) {
                /*
                call allocate 2
                */
                // Gen, finding 'args used'
                for (int i = 0; i < 2; i++) {
                    gen_set_ptr->insert(fptr->variable_allocator.allocate_variable(arguments_vec[i], VariableType::reg));
                }
                // Kill, finding 'caller-saved'
                for (auto register_string : caller_save_vec) {
                    kill_set_ptr->insert(fptr->variable_allocator.allocate_variable(register_string, VariableType::reg));
                }
            }
            Call_tuple_Instruction* call_tuple_instruction_ptr = dynamic_cast<Call_tuple_Instruction*>(instruction_ptr);
            if (call_tuple_instruction_ptr) {
                /*
                call tuple-error 3
                */
                // Gen, finding 'args used'
                for (int i = 0; i < 3; i++) {
                    gen_set_ptr->insert(fptr->variable_allocator.allocate_variable(arguments_vec[i], VariableType::reg));
                }
                // Kill, finding 'caller-saved'
                for (auto register_string : caller_save_vec) {
                    kill_set_ptr->insert(fptr->variable_allocator.allocate_variable(register_string, VariableType::reg));
                }
            }
            Call_tenserr_Instruction* call_tenserr_instruction_ptr = dynamic_cast<Call_tenserr_Instruction*>(instruction_ptr);
            if (call_tenserr_instruction_ptr) {
                /*
                call tensor-error F
                */
                // Gen, finding 'args used'
                Number* number_ptr = dynamic_cast<Number*>(call_tenserr_instruction_ptr->F);
                if (number_ptr) {
                    for (int i = 0; i < number_ptr->value; i++) {
                        gen_set_ptr->insert(fptr->variable_allocator.allocate_variable(arguments_vec[i], VariableType::reg));
                    }
                }
                // Kill, finding 'caller-saved'
                for (auto register_string : caller_save_vec) {
                    kill_set_ptr->insert(fptr->variable_allocator.allocate_variable(register_string, VariableType::reg));
                }
            }
            Instruction_ret* return_instruction_ptr = dynamic_cast<Instruction_ret*>(instruction_ptr);
            if (return_instruction_ptr) {
                /*
                --- return ---
                Gen <- {rax, callee-saved}
                Kill <- {}
                */
                // Gen, finding 'rax'
                gen_set_ptr->insert(fptr->variable_allocator.allocate_variable("rax", VariableType::reg));
                // Gen, finding 'callee-saved'
                for (auto register_string : callee_save_vec) {
                    gen_set_ptr->insert(fptr->variable_allocator.allocate_variable(register_string, VariableType::reg));
                }
            }

            /*
            Verify Gen and Kill sets by printing
            */
            // if (debug) gen_kill_sets.print_sets(function_index, instruction_ptr);

        }   // finished with Gen and Kill
        
        /*
        Calcuate Predeccesors and Successors sets for each instruction in the current function with our algorithm
        */
        if (debug) std::cerr << "pre CFG brrrr" << std::endl;
        fptr->calculateCFG();
        if (debug) std::cerr << "CFG brrrr" << std::endl;

        int instruction_number;  
        bool changed;
        instruction_number = 0;
        bool tensor_error_encountered = false;
        std::set<Instruction*> sealed_instructions;
        do {
            changed = false;
            for (auto instruction_ptr : fptr->instructions) {
                instruction_number++;

                /*
                    Define pointers to the Gen, Kill, In, Out sets for the current instruction
                */
                // std::set<Variable*>* gen_set_ptr = &gen_kill_sets.Gen_Set[function_index][instruction_ptr];
                // std::set<Variable*>* kill_set_ptr = &gen_kill_sets.Kill_Set[function_index][instruction_ptr];
                // std::set<Variable*>* in_set_ptr = &in_out_sets.In_Set[function_index][instruction_ptr];
                // std::set<Variable*>* out_set_ptr = &in_out_sets.Out_Set[function_index][instruction_ptr];
                std::set<Variable*>* gen_set_ptr = &gen_sets[instruction_ptr];
                std::set<Variable*>* kill_set_ptr = &kill_sets[instruction_ptr];
                std::set<Variable*>* in_set_ptr = &in_sets[instruction_ptr];
                std::set<Variable*>* out_set_ptr = &out_sets[instruction_ptr];


                // if (debug) std::cerr << "computing In and Out sets for the current instruction..." << std::endl;

                /*
                    Define state of the In set before any potential changes are made
                */
                std::set<Variable*> in_set_prev = *in_set_ptr;

                /*
                    Do the In set operations
                */
                std::set<Variable*> In_Result;
                std::set<Variable*> Out_Kill_Diff;
                std::set_difference(
                    out_set_ptr->begin(), out_set_ptr->end(),
                    kill_set_ptr->begin(), kill_set_ptr->end(),
                    std::inserter(Out_Kill_Diff, Out_Kill_Diff.begin())
                );
                std::set_union(
                    gen_set_ptr->begin(), gen_set_ptr->end(),
                    Out_Kill_Diff.begin(), Out_Kill_Diff.end(),
                    std::inserter(In_Result, In_Result.begin())
                );

                /*
                    Define state of the Out set before any potential changes are made
                */
                std::set<Variable*> out_set_prev = *out_set_ptr;

                /*
                    Do the In set operations
                */
                //
                std::set<Variable*> Out_Result;
                for (auto successor : instruction_ptr->successors) {
                    // note that successor should be of type Instruction*
                    // std::set<Variable*> successor_in_set = in_out_sets.In_Set[function_index][successor];
                    std::set<Variable*> successor_in_set = in_sets[successor];
                    std::set<Variable*> temp_union_set;
                    std::set_union(
                        Out_Result.begin(), Out_Result.end(),
                        successor_in_set.begin(), successor_in_set.end(),
                        std::inserter(temp_union_set, temp_union_set.begin())
                    );
                    Out_Result = std::move(temp_union_set);
                }

                *in_set_ptr = In_Result;
                *out_set_ptr = Out_Result;
                changed = changed || ((in_set_prev != *in_set_ptr) || (out_set_prev != *out_set_ptr));
            }
        } while (changed);


        if (print) {
            /*
            Print the contents of our freshly computed In and Out sets to the file
            */
            std::cout << "(\n";
            // Function* function_ptr = p->functions[function_index];
            Function* function_ptr = fptr;
            std::cout << "(in\n";
            for (auto instruction_ptr : function_ptr->instructions) {
                std::cout << "(";
                // for (auto variable_ptr : in_out_sets.In_Set[function_index][instruction_ptr]) {
                for (auto variable_ptr : in_sets[instruction_ptr]) {
                    std::cout << variable_ptr->print() << " ";
                }
                std::cout << ")\n";
            }
            std::cout << ")\n\n";
            std::cout << "(out\n";
            for (auto instruction_ptr : function_ptr->instructions) {
                std::cout << "(";
                // for (auto variable_ptr : in_out_sets.Out_Set[function_index][instruction_ptr]) {
                for (auto variable_ptr : out_sets[instruction_ptr]) {
                    std::cout << variable_ptr->print() << " ";
                }
                std::cout << ")\n";
            }
            std::cout << ")\n\n";
            std::cout << ")\n\n";
        }

        /*
        Return the sets as a pair
        */
        // LivenessResult result = {gen_kill_sets, in_out_sets};

        Curr_F_Liveness result = {
            // gen_kill_sets.Gen_Set[function_index],
            // gen_kill_sets.Kill_Set[function_index],
            // in_out_sets.In_Set[function_index],
            // in_out_sets.Out_Set[function_index]
            gen_sets, kill_sets, in_sets, out_sets
        };
        return result;
    }

    

}