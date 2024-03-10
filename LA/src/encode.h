#pragma once

#include "LA.h"

namespace LA {

    /*
    Encoding Scheme Functions
    */
    void encode_program(Program& p);

    Function* encode_function(Function *f);

    /*
    Visitor for encoding all constants not used for array/tuple incides and 2nd parameter of length.
    - I think we can just do this in memory, no need to generate code for this.
    */
    class EncodeConstants : public Visitor {
        public:
            void visit(Instruction_type_declaration* i) override;
            void visit(Instruction_assignment* i) override;
            void visit(Instruction_length* i) override;
            void visit(Instruction_call_function* i) override;
            void visit(Instruction_call_function_assignment* i) override;
            void visit(Instruction_initialization* i) override;
            void visit(Instruction_operation* i) override;
            void visit(Instruction_store* i) override;
            void visit(Instruction_load* i) override;
            void visit(Instruction_branch_single* i) override;
            void visit(Instruction_branch_double* i) override;
            void visit(Instruction_return* i) override;
            void visit(Instruction_return_value* i) override;
            void visit(Instruction_label* i) override;
    };


    /*
    Visitor for carrying out step 2 of our encoding scheme algorithm.
    - another one of its responsibilities is to initialize all variables
        to zero (1 in IR) whenever it sees a variable declaration.
    */
    class EncodingVisitor : public Visitor {
        public:
            void visit(Instruction_type_declaration* i) override;
            void visit(Instruction_assignment* i) override;
            void visit(Instruction_length* i) override;
            void visit(Instruction_call_function* i) override;
            void visit(Instruction_call_function_assignment* i) override;
            void visit(Instruction_initialization* i) override;
            void visit(Instruction_operation* i) override;
            void visit(Instruction_store* i) override;
            void visit(Instruction_load* i) override;
            void visit(Instruction_branch_single* i) override;
            void visit(Instruction_branch_double* i) override;
            void visit(Instruction_return* i) override;
            void visit(Instruction_return_value* i) override;
            void visit(Instruction_label* i) override;

            std::vector<Item*> decodeItems(std::vector<Item*>& items);
            std::vector<Instruction*> instructions;
    };







        
}