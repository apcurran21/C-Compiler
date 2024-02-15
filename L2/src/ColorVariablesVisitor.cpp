#include "ColorVariablesVisitor.h"
namespace L2{
    void ColorVariablesVisitor::colorVar(Variable * &var) {
        Node* correspondingNode = color_graph->nodes[var];
        if (correspondingNode) {
            std::string color = correspondingNode->color;
            Variable* new_var = current_function->variable_allocator.allocate_variable(color, VariableType::reg);
            *var = *new_var;
        } else {
            // The variable was not found in the graph.
            // theoretically shouldn't get here...
        }
    }

    void ColorVariablesVisitor::visit(Instruction_assignment *instruction) {
        auto s = dynamic_cast<Variable*>(instruction->s);
        auto d = dynamic_cast<Variable*>(instruction->s);
        colorVar(s);
        colorVar(d);
    }

    void ColorVariablesVisitor::visit(label_Instruction *instruction) {
        auto label = dynamic_cast<Variable*>(instruction->label);
        colorVar(label);
    }
    void ColorVariablesVisitor::visit(goto_label_instruction *instruction) {
    }
    void ColorVariablesVisitor::visit(Call_tenserr_Instruction *instruction) {
    }
    void ColorVariablesVisitor::visit(Call_uN_Instruction *instruction) {
    }
    void ColorVariablesVisitor::visit(Call_print_Instruction *instruction) {
    }
    void ColorVariablesVisitor::visit(Call_input_Instruction *instruction) {
    }
    void ColorVariablesVisitor::visit(Call_allocate_Instruction *instruction) {
    }
    void ColorVariablesVisitor::visit(Call_tuple_Instruction *instruction) {
    }
    void ColorVariablesVisitor::visit(w_increment_decrement *instruction) {
        auto r = dynamic_cast<Variable*>(instruction->r);
        colorVar(r);
    }
    void ColorVariablesVisitor::visit(w_atreg_assignment *instruction) {
        auto r1 = dynamic_cast<Variable*>(instruction->r1);
        auto r2 = dynamic_cast<Variable*>(instruction->r2);
        auto r3 = dynamic_cast<Variable*>(instruction->r3);
        colorVar(r1);
        colorVar(r2);
        colorVar(r3);

    }
    void ColorVariablesVisitor::visit(Memory_assignment_store *instruction) {
        auto dst = dynamic_cast<Variable*>(instruction->dst);
        auto s = dynamic_cast<Variable*>(instruction->s);
        colorVar(dst);
        colorVar(s);
    }
    void ColorVariablesVisitor::visit(Memory_assignment_load *instruction) {
        auto dst = dynamic_cast<Variable*>(instruction->dst);
        auto x = dynamic_cast<Variable*>(instruction->x);
        colorVar(dst);
        colorVar(x);

    }
    void ColorVariablesVisitor::visit(Memory_arithmetic_load *instruction) {
        auto dst = dynamic_cast<Variable*>(instruction->dst);
        auto x = dynamic_cast<Variable*>(instruction->x);
        colorVar(dst);
        colorVar(x);
    }
    void ColorVariablesVisitor::visit(Memory_arithmetic_store *instruction) {
        auto dst = dynamic_cast<Variable*>(instruction->dst);
        auto t = dynamic_cast<Variable*>(instruction->t);
        colorVar(dst);
        colorVar(t);
    }
    void ColorVariablesVisitor::visit(cmp_Instruction *instruction) {
        auto dst = dynamic_cast<Variable*>(instruction->dst);
        auto t1 = dynamic_cast<Variable*>(instruction->t1);
        auto t2 = dynamic_cast<Variable*>(instruction->t2);
        colorVar(dst);
        colorVar(t1);
        colorVar(t2);

    }
    void ColorVariablesVisitor::visit(cjump_cmp_Instruction *instruction) {
        auto label = dynamic_cast<Variable*>(instruction->label);
        auto t1 = dynamic_cast<Variable*>(instruction->t1);
        auto t2 = dynamic_cast<Variable*>(instruction->t2);
        colorVar(label);
        colorVar(t1);
        colorVar(t2);
    }
    void ColorVariablesVisitor::visit(stackarg_assignment *instruction) {
        auto w = dynamic_cast<Variable*>(instruction->w);
        colorVar(w);
    }
    void ColorVariablesVisitor::visit(AOP_assignment *instruction) {
        auto dst = dynamic_cast<Variable*>(instruction->dst);
        auto src = dynamic_cast<Variable*>(instruction->src);
        colorVar(dst);        
        colorVar(src);
    }
    void ColorVariablesVisitor::visit(SOP_assignment *instruction) {
        auto dst = dynamic_cast<Variable*>(instruction->dst);
        auto src = dynamic_cast<Variable*>(instruction->src);
        colorVar(dst);        
        colorVar(src);
    }
}
