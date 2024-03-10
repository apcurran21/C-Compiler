#include "check_memory.h"

using namespace std;

namespace LA {

    /*
    Checks that a tuple or tensor has been allocated, not just declared.
    */
    std::vector<Instruction*> create_allocation_check(Instruction* i) {
        std::vector<Instruction*> output;
        auto store_ptr = dynamic_cast<Instruction_store*>(i);
        auto load_ptr = dynamic_cast<Instruction_load*>(i);

        int64_t line_n;
        if (store_ptr) line_n = store_ptr->line_number;
        else if (load_ptr) line_n = load_ptr->line_number;

        Item* array_variable;
        if (store_ptr) array_variable = store_ptr->dest;
        else if (load_ptr) array_variable = load_ptr->src;

        /*
        Create the check instructions.
        */
        auto line_number_var = new Name(UniqueNameTracker::getUniqueName() + "_line_number"); 
        auto line_number = new Number(line_n);
        auto int64_type = new Type(TypeEnum::int64);
        auto i0 = new Instruction_type_declaration(int64_type, line_number_var);
        output.push_back(i0);
        auto i1 = new Instruction_assignment(line_number_var, line_number);    
        output.push_back(i1);
        auto number_zero = new Number(0);
        auto temp_var = new Name(UniqueNameTracker::getUniqueName());
        auto i2 = new Instruction_type_declaration(int64_type, temp_var);
        output.push_back(i2);
        auto equals_op = new Operation(OperationEnum::eq);
        auto i3 = new Instruction_operation(temp_var, array_variable, equals_op, number_zero);
        output.push_back(i3);
        auto error_label = new Name(UniqueNameTracker::getUniqueName() + "_ERROR"); 
        auto correct_label = new Name(UniqueNameTracker::getUniqueName() + "_CORRECT"); 
        auto i4 = new Instruction_branch_double(temp_var, error_label, correct_label);
        output.push_back(i4);
        auto i5 = new Instruction_label(error_label);
        output.push_back(i5);
        auto i6 = new Instruction_error();
        i6->type = "tensor";
        i6->args = {line_number_var};
        output.push_back(i6);
        auto i7 = new Instruction_label(correct_label);
        output.push_back(i7);

        return output;
    }

    std::vector<Instruction*> create_index_check(Function* f, Instruction* i, Item* index, int64_t dimension_index) {
        std::vector<Instruction*> output;
        auto store_ptr = dynamic_cast<Instruction_store*>(i);
        auto load_ptr = dynamic_cast<Instruction_load*>(i);

        /*
        Extract info from the accessing instructions.
        */
        int64_t line_n;
        Item* array_variable;
        if (store_ptr) {
            line_n = store_ptr->line_number;
            array_variable = store_ptr->dest;
        } else if (load_ptr) {
            line_n = load_ptr->line_number;
            array_variable = load_ptr->src;
        }

        Type* array_variable_type;
        auto it = f->variableNameToType.find(array_variable->print());
        if (it != f->variableNameToType.end()) {
            array_variable_type = it->second;
        } else {
            if (debug) std::cerr << "something went wrong, variable not found in type dict.\n";
        }

        /*
        Check if the array is a tuple.
        */
        bool isTuple = (array_variable_type->get_type() == TypeEnum::tuple);

        /*
        Check if the array is a 1D tensor.
        */
        bool is1dTensor = ((array_variable_type->get_type() == TypeEnum::int64) && array_variable_type->get_dims() == 1);

        /*
        Constants and other useful objects. 
        */
        Number* number_zero = new Number(0);
        Name* line_number_var = new Name(UniqueNameTracker::getUniqueName() + "_line_number"); 
        Number* line_number = new Number(line_n);
        Name* length_var = new Name(UniqueNameTracker::getUniqueName() + "_length");
        Operation* geq_op = new Operation(OperationEnum::greatereq);
        Operation* less_op = new Operation(OperationEnum::less);
        Number* array_dimension_index = new Number(dimension_index);

        /*
        Negative index check
        */
        auto i0 = new Instruction_length(length_var, array_variable);
        if (!isTuple) {
            i0->t = array_dimension_index;
        }
        output.push_back(i0);

        auto temp_var0 = new Name(UniqueNameTracker::getUniqueName());
        auto i1 = new Instruction_operation(temp_var0, index, geq_op, number_zero);
        output.push_back(i1);

        auto error_label = new Name(UniqueNameTracker::getUniqueName() + "_ERROR"); 
        auto correct_label0 = new Name(UniqueNameTracker::getUniqueName() + "_CORRECT"); 
        auto i2 = new Instruction_branch_double(temp_var0, correct_label0, error_label);
        output.push_back(i2);

        auto i3 = new Instruction_label(error_label);
        output.push_back(i3);

        auto i4 = new Instruction_error();
        if (isTuple) {
            i4->type = "tuple-error";
            i4->args = {line_number_var, length_var, index};
        } else {
            i4->type = "tensor-error";
            if (is1dTensor) {
                i4->args = {line_number_var, length_var, index};
            } else {
                i4->args = {line_number_var, array_dimension_index, length_var, index};
            }
        }
        output.push_back(i4);

        auto i5 = new Instruction_label(correct_label0);
        output.push_back(i5);

        /*
        Length checks
        */
        auto temp_var1 = new Name(UniqueNameTracker::getUniqueName());
        auto i6 = new Instruction_operation(temp_var1, index, less_op, length_var);
        output.push_back(i6);
        auto correct_label1 = new Name(UniqueNameTracker::getUniqueName() + "_CORRECT");
        auto i7 = new Instruction_branch_double(temp_var1, correct_label1, error_label);
        output.push_back(i7);
        auto i8 = new Instruction_label(correct_label1);
        output.push_back(i8);

        return output;
    }

    /*
    Checks that all of indices used to access an array are within bounds.
    */
    std::vector<Instruction*> create_indices_check(Function* f, Instruction* i) {
        std::vector<Instruction*> output;
        auto store_ptr = dynamic_cast<Instruction_store*>(i);
        auto load_ptr = dynamic_cast<Instruction_load*>(i);

        /*
        Extract info from the accessing instructions.
        */
        Item* array_variable;
        std::vector<Item*> array_indices;
        if (store_ptr) {
            array_variable = store_ptr->dest;
            array_indices = store_ptr->args;
        } else if (load_ptr) {
            array_variable = load_ptr->src;
            array_indices = load_ptr->args;
        }

        Type* array_variable_type;
        auto it = f->variableNameToType.find(array_variable->print());
        if (it != f->variableNameToType.end()) {
            array_variable_type = it->second;
        } else {
            if (debug) std::cerr << "something went wrong, variable not found in type dict.\n";
        }

        /*
        Get the number of dimension's we'll need to check.
        */
        int64_t total_dimensions = array_variable_type->get_dims();

        /*
        Iterate these number of dims, since we'll need to check the object in each dimension.
        */
        int64_t dimension_index = 0;
        do {
            std::vector<Instruction*> curr_output = create_index_check(f, i, array_indices[dimension_index], dimension_index);
            output.insert(output.end(), curr_output.begin(), curr_output.end());
            dimension_index++;
        } while (dimension_index < total_dimensions);

        return output;
    }


    /*
    Checks the memory access for each instruction within a function, returning a new set of instructions.
    */
    Function* check_function(Function *f) {
        Item* functionName_copy = new Name(f->functionName->print());
        Item* returnType_copy = new Type(stringToType(f->returnType->print()));
        Function* new_f = new Function(functionName_copy, returnType_copy);
        new_f->parameters = f->parameters;
        new_f->variableNameToType = f->variableNameToType;

        std::vector<Instruction*> new_instructions;

        /*
        Iterate the old instructions and check for memory accesses etc.
        */
        for (auto i : f->instructions) {
            auto store_inst = dynamic_cast<Instruction_store*>(i);
            auto load_inst = dynamic_cast<Instruction_load*>(i);
            if (store_inst || load_inst) {
                std::vector<Instruction*> curr_instructions;
                /*
                Check for initialization
                */
                std::vector<Instruction*> allocation_instructions = create_allocation_check(i);
                curr_instructions.insert(curr_instructions.end(), allocation_instructions.begin(), allocation_instructions.end());
                /*
                Check for index
                */
                std::vector<Instruction*> access_instructions = create_indices_check(f, i);
                curr_instructions.insert(curr_instructions.end(), access_instructions.begin(), access_instructions.end());
                /*
                Place all the new check instructions into the main instructions vector
                */
                new_instructions.insert(new_instructions.end(), curr_instructions.begin(), curr_instructions.end());
            }
            new_instructions.push_back(i);
        }
        new_f->instructions = new_instructions;
        return new_f;
    }


    /*
    Creates the memory checking instructions for each function in the program.
    */
    void check_program(Program& p) {
        std::vector<Function*> new_functions;

        for (auto f : p.functions) {
            Function* new_f = check_function(f);
            new_functions.push_back(new_f);
        }

        p.functions = new_functions;
    }





}
