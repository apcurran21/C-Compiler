// ColorVisitor.h
#pragma once

#include "L2.h"
#include "interference_graph.h"
namespace L2 {
    class ColorVariablesVisitor: public Visitor {
    public:
      ColorVariablesVisitor(Graph *graph, Function *func) :
            color_graph(graph), current_function(func) {}
      void visit(Instruction_ret *instruction) override;
      void visit(Instruction_assignment *instruction) override;
      void visit(label_Instruction *instruction) override;
      void visit(goto_label_instruction *instruction) override;
      void visit(Call_tenserr_Instruction *instruction) override;
      void visit(Call_uN_Instruction *instruction) override;
      void visit(Call_print_Instruction *instruction) override;
      void visit(Call_input_Instruction *instruction) override;
      void visit(Call_allocate_Instruction *instruction) override;
      void visit(Call_tuple_Instruction *instruction) override;
      void visit(w_increment_decrement *instruction) override;
      void visit(w_atreg_assignment *instruction) override;
      void visit(Memory_assignment_store *instruction) override;
      void visit(Memory_assignment_load *instruction) override;
      void visit(Memory_arithmetic_load *instruction) override;
      void visit(Memory_arithmetic_store *instruction) override;
      void visit(cmp_Instruction *instruction) override;
      void visit(cjump_cmp_Instruction *instruction) override;
      void visit(stackarg_assignment *instruction) override;
      void visit(AOP_assignment *instruction) override;
      void visit(SOP_assignment *instruction) override;  
      void colorVar(Variable *&var);
      Graph *color_graph; // Member variable for the graph
      Function *current_function; 
  };
}
