#include "create_basicblocks.h"

using namespace std;

namespace LA {

    /*
    Returns true or false based on it the given instruction is a terminator.
    */
    bool isTerminator(Instruction* i) {
        return dynamic_cast<Instruction_branch_single*>(i) ||
               dynamic_cast<Instruction_branch_double*>(i) ||
               dynamic_cast<Instruction_return*>(i) ||
               dynamic_cast<Instruction_return_value*>(i) ||
               dynamic_cast<Instruction_error*>(i);
    }


    /*
    Places all type declarations at the beginning of the function.
    */
    Function* move_declarations(Function *f) {
        Item* functionName_copy = new Name(f->functionName->print());
        Item* returnType_copy = new Type(stringToType(f->returnType->print()));
        Function* new_f = new Function(functionName_copy, returnType_copy);
        new_f->parameters = f->parameters;
        new_f->variableNameToType = f->variableNameToType;

        std::vector<Instruction*> new_instructions;
        std::vector<Instruction*> declarations;

        /*
        Iterate the old instructions and check for type declarations.
        */
        for (auto i : f->instructions) {
            auto declaration = dynamic_cast<Instruction_type_declaration*>(i);
            if (declaration) {
                declarations.push_back(declaration);
            } else {
                new_instructions.push_back(i);
            }
        }
        /*
        Insert the declarations at the start of the first basic block.
        - we go plus 1 since they need to go after the first label.
        */
        new_instructions.insert(new_instructions.begin() + 1, declarations.begin(), declarations.end());
        
        new_f->instructions = new_instructions;
        return new_f;
    }


    /*
    Creates a basic block structure within a given function.
    */
    Function* create_structure(Function *f) {
        Item* functionName_copy = new Name(f->functionName->print());
        Item* returnType_copy = new Type(stringToType(f->returnType->print()));
        Function* new_f = new Function(functionName_copy, returnType_copy);
        new_f->parameters = f->parameters;
        new_f->variableNameToType = f->variableNameToType;

        std::vector<Instruction*> new_instructions;
        bool startBB = true;

        for (auto i : f->instructions) {
            auto inst_label_ptr = dynamic_cast<Instruction_label*>(i);
            if (startBB) {
                if (!inst_label_ptr){
                    Label* label0 = new Label(UniqueNameTracker::getUniqueName());
                    Instruction_label* i0 = new Instruction_label(label0);
                    new_instructions.push_back(i0);
                }
                startBB = false;
            } else if (inst_label_ptr) {
                auto label1 = inst_label_ptr->label;
                Instruction_branch_single* i1 = new Instruction_branch_single(label1);
                new_instructions.push_back(i1);
            }
            new_instructions.push_back(i);
            if (isTerminator(i)) {
                startBB = true;
            }
        }
        if (!startBB) {
            if (f->returnType->print() == "void") { // bruh strcompare
                auto r = new Instruction_return();
                new_instructions.push_back(r);
            } else {
                auto zero = new Number(0);
                auto r = new Instruction_return_value(zero);
                new_instructions.push_back(r);
            }
        }
        new_f->instructions = new_instructions;

        return new_f;
    }


    /*
    The big function, converts the program into IR compatible basic blocks.
    */
    void create_basicblocks(Program& p) {
        std::vector<Function*> new_functions;

        for (auto f : p.functions) {
            Function* new_f = create_structure(f);
            Function* newer_f = move_declarations(new_f);
            new_functions.push_back(newer_f);
        }

        p.functions = new_functions;
    }








}