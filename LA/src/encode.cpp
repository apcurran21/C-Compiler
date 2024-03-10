#include "encode.h"

using namespace std;

namespace LA {

/*
Encoding Scheme Functions
*/
Function* encode_function(Function *f) {
    Item* functionName_copy = new Name(f->functionName->print());
    Item* returnType_copy = new Type(stringToType(f->returnType->print()));
    Function* new_f = new Function(functionName_copy, returnType_copy);
    new_f->parameters = f->parameters;

    /*
    Encode the constants by modifying current function's instruction vector
    */
    EncodeConstants* constant_encoder = new EncodeConstants();
    for (auto i : f->instructions) {
        i->accept(constant_encoder);
    }

    /*
    Encode the function as a whole. We reassign the vector that the Visitor builds up.
    */
    EncodingVisitor* encoding_visitor = new EncodingVisitor();
    for (auto i : f->instructions) {
        i->accept(encoding_visitor);
    }
    new_f->instructions = encoding_visitor->instructions;

    return new_f;
}

void encode_program(Program& p) {
    std::vector<Function*> new_functions;

    for (auto f : p.functions) {
        Function* new_f = encode_function(f);
        new_functions.push_back(new_f);
    }

    p.functions = new_functions;
}


/*
Visitor Methods
*/

/*
EncodeConstants
*/
void EncodeConstants::visit(Instruction_type_declaration* i) {
    // nothing
}

void EncodeConstants::visit(Instruction_assignment* i) {
    auto n = dynamic_cast<Number*>(i->src);
    if (n) n->encode();
}

void EncodeConstants::visit(Instruction_length* i) {
    // nothing
}

void EncodeConstants::visit(Instruction_call_function* i) {
    for (auto arg : i->args) {
        auto n = dynamic_cast<Number*>(arg);
        if (n) n->encode();
    }
}

void EncodeConstants::visit(Instruction_call_function_assignment* i) {
    for (auto arg : i->args) {
        auto n = dynamic_cast<Number*>(arg);
        if (n) n->encode();
    }
}

void EncodeConstants::visit(Instruction_initialization* i) {
    for (auto arg : i->args) {
        auto n = dynamic_cast<Number*>(arg);
        if (n) n->encode();
    }
}

void EncodeConstants::visit(Instruction_operation* i) {
    auto n1 = dynamic_cast<Number*>(i->t1);
    if (n1) n1->encode();
    auto n2 = dynamic_cast<Number*>(i->t2);
    if (n2) n2->encode();
}

void EncodeConstants::visit(Instruction_store* i) {
    auto n = dynamic_cast<Number*>(i->src);
    if (n) n->encode();
}

void EncodeConstants::visit(Instruction_load* i) {
    // nothing
}

void EncodeConstants::visit(Instruction_branch_single* i) {
    // nothing
}

void EncodeConstants::visit(Instruction_branch_double* i) {
    auto n = dynamic_cast<Number*>(i->t);
    if (n) n->encode();
}

void EncodeConstants::visit(Instruction_return* i) {
    // nothing
}

void EncodeConstants::visit(Instruction_return_value* i) {
    auto n = dynamic_cast<Number*>(i->t);
    if (n) n->encode();
}

void EncodeConstants::visit(Instruction_label* i) {
    // nothing
}



/*
EncodingVisitor
*/
void EncodingVisitor::visit(Instruction_type_declaration* i) {
    instructions.push_back(i);
    auto n = new Number(1);
    auto i0 = new Instruction_assignment(i->name, n);
    instructions.push_back(i0);
}

void EncodingVisitor::visit(Instruction_assignment* i) {
    instructions.push_back(i);
}

void EncodingVisitor::visit(Instruction_length* i) {
    // early return if this is a tuple length instruction
    if (!i->t) return;
    std::vector<Item*> encoded = { i->t };
    std::vector<Item*> decoded = decodeItems(encoded);

    if (decoded.size() != 1) {
        if (debug) std::cerr << "Something went wrong in the decoding step, " << encoded.size() << " items should be decoded for an Instruction_operation but only " << decoded.size() << " were returned.\n";
    }
    auto i_new = new Instruction_length(i->dest, i->src);
    i_new->t = decoded[0];
    instructions.push_back(i_new);

    // auto var = dynamic_cast<Name*>(i->t);
    // if (var) {
    //     // 2.A.I
    //     auto v_prime = new Name(UniqueNameTracker::getUniqueName());
    //     auto type_v_prime = new Type(TypeEnum::int64);
    //     auto i0 = new Instruction_type_declaration(type_v_prime, v_prime);

    //     // 2.A.II
    //     auto i1_op = new Operation(OperationEnum::rshift);
    //     auto i1_n = new Number(1);
    //     auto i1 = new Instruction_operation(v_prime, i->t, i1_op, i1_n);

    //     // 2.A.III
    //     auto i2 = new Instruction_length(i->dest, i->src);
    //     i2->t = v_prime;

    //     // Append new instructions to the output vector
    //     instructions.push_back(i0);
    //     instructions.push_back(i1);
    //     instructions.push_back(i2);
    // }
}

void EncodingVisitor::visit(Instruction_call_function* i) {
    instructions.push_back(i);
}

void EncodingVisitor::visit(Instruction_call_function_assignment* i) {
    instructions.push_back(i);
}

void EncodingVisitor::visit(Instruction_initialization* i) {
    instructions.push_back(i);
}

void EncodingVisitor::visit(Instruction_operation* i) {
    std::vector<Item*> encoded = { i->t1, i->t2 };
    std::vector<Item*> decoded = decodeItems(encoded);
    // 2.A.III
    if (decoded.size() != 2) {
        if (debug) std::cerr << "Something went wrong in the decoding step, " << std::to_string(encoded.size()) << " items should be decoded for an Instruction_operation but only " << std::to_string(decoded.size()) << " were returned.\n";
    }
    auto i_new = new Instruction_operation(i->name, decoded[0], i->op, decoded[1]);
    instructions.push_back(i_new);

    /*
    Note - we also need to encode after this instruction.
    - Currently we are using the same Name and Number instances in multiple instructions, not 100% if this is ok
    */
    auto lshift = new Operation(OperationEnum::lshift);
    auto plus = new Operation(OperationEnum::plus);
    auto n = new Number(1);
    auto i0 = new Instruction_operation(i->name, i->name, lshift, n);
    auto i1 = new Instruction_operation(i->name, i->name, plus, n);
    instructions.push_back(i0);
    instructions.push_back(i1);
}

void EncodingVisitor::visit(Instruction_store* i) {
    std::vector<Item*> decoded = decodeItems(i->args);
    if (decoded.size() != i->args.size()) {
        if (debug) std::cerr << "Something went wrong in the decoding step, " << std::to_string(i->args.size()) << " items should be decoded for an Instruction_operation but only " << std::to_string(decoded.size()) << " were returned.\n";
    }
    auto i_new = new Instruction_store(i->dest, i->src);
    i_new->args = i->args;
    instructions.push_back(i_new);
}

void EncodingVisitor::visit(Instruction_load* i) {
    std::vector<Item*> decoded = decodeItems(i->args);
    if (decoded.size() != i->args.size()) {
        if (debug) std::cerr << "Something went wrong in the decoding step, " << std::to_string(i->args.size()) << " items should be decoded for an Instruction_operation but only " << std::to_string(decoded.size()) << " were returned.\n";
    }
    auto i_new = new Instruction_load(i->dest, i->src);
    i_new->args = i->args;
    instructions.push_back(i_new);
}

void EncodingVisitor::visit(Instruction_branch_single* i) {
    instructions.push_back(i);
}

void EncodingVisitor::visit(Instruction_branch_double* i) {
    std::vector<Item*> encoded = { i->t };
    std::vector<Item*> decoded = decodeItems(encoded);
    if (decoded.size() != 1) {
        if (debug) std::cerr << "Something went wrong in the decoding step, " << std::to_string(encoded.size()) << " items should be decoded for an Instruction_operation but only " << std::to_string(decoded.size()) << " were returned.\n";
    }
    auto i_new = new Instruction_branch_double(decoded[0], i->label1, i->label2);
    instructions.push_back(i_new);
}

void EncodingVisitor::visit(Instruction_return* i) {
    instructions.push_back(i);
}

void EncodingVisitor::visit(Instruction_return_value* i) {
    instructions.push_back(i);
}

void EncodingVisitor::visit(Instruction_label* i) {
    instructions.push_back(i);
}


std::vector<Item*> EncodingVisitor::decodeItems(std::vector<Item*>& items) {
    std::vector<Item*> out;
    for (auto item : items) {
        // 2.A.I
        auto v_prime = new Name(UniqueNameTracker::getUniqueName());
        auto type_v_prime = new Type(TypeEnum::int64);
        auto i0 = new Instruction_type_declaration(type_v_prime, v_prime);

        // we already encoded constants at the stage where this function is called,
        // so we need to manually initialize new variables to zero (1 in IR)
        auto i1_n = new Number(1);
        auto i1 = new Instruction_assignment(v_prime, i1_n);

        auto i2 = new Instruction_assignment(v_prime, item);

        auto i3_op = new Operation(OperationEnum::rshift);
        auto i3_n = new Number(1);
        auto i3 = new Instruction_operation(v_prime, v_prime , i3_op, i3_n);

        // append new instructions to the new vector
        instructions.push_back(i0);
        instructions.push_back(i1);
        instructions.push_back(i2);
        instructions.push_back(i3);

        // append the new variable to the output vector
        out.push_back(v_prime);
    }
    return out;
}

}