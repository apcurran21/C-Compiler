#pragma once
#include <set>
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <tuple>

#include "variable_allocator.h"
#include "interference_graph.h"
#include "liveness_analysis.h"
#include "graph_coloring.h"
#include "spill.h"

namespace L2 {

  extern int const debug;

  // Forward declarations
  class Function;
  class Program;
  class Item;
  class Instruction;
  class Variable;
  class Visitor;
  // class Node;
  // class Graph;

  /*
  Code Analysis.
  */
  Graph* analyze_L2(Function*);
  
  /*
  Register Allocation.
  */
  Function* allocate_registers(Function*);

  /*
  Object Classes
  */
  class Item {
    public:
      virtual std::string translate() = 0;    // returns string with the x86 conventions attached
      virtual std::string print() = 0;        // returns the value as is
  };
  class Variable : public Item {
    public:
      Variable (std::string name);
      std::string translate() override;
      virtual std::string print() override;
      std::string name;
  };
  class Register : public Variable {
    public:
      Register (std::string value);
      std::string print() override;
      std::string name;
  };

  class Number : public Item {
    public:
      Number (int64_t n);
      std::string translate() override;
      std::string print() override;
      int64_t value;
  };

  class Name : public Item {
    public:
      Name (const std::string &value);
      std::string translate() override;
      std::string print() override;
    private:
      std::string value;
  };

  class Label : public Item {
    public:
      Label (const std::string &value);
      std::string translate() override;
      std::string print() override;
      std::string getLabel() const {
        return value;
      };
      std::string value;
  };

  class Operator : public Item {
    public:
      Operator (const std::string &sign);
      std::string translate() override;
      std::string print() override;
      bool operator==(const Operator &other) const {
        return this->sign == other.sign;
      }
    private:
      std::string sign;
  };

  /*
   * Instruction interface.
   */
  class Instruction{
    public:
      virtual void accept(Visitor *visitor) = 0; 
      virtual void gen(Function *f, std::ofstream &outputFile) = 0;
      virtual void spill_gen(Function *f, std::ofstream &outputFile) = 0;
      virtual void printMe() = 0;

      std::set<Instruction *> predecessors;
      std::set<Instruction *> successors;
      std::set<Variable *> used; //all variables being read (right side of the operand)
      std::set<Variable *> defined; //all variables being written (left side of the operand )
  };

  /*
   * Instructions.
   */
  class Instruction_ret : public Instruction{
    public:
      Instruction_ret ();
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      void accept(Visitor *visitor) override;
  };

  class Instruction_assignment : public Instruction{
    public:
      Instruction_assignment (Item *d, Item *s);
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      void accept(Visitor *visitor) override;
      Item *s;
      Item *d;
  };
  class stackarg_assignment: public Instruction {
    public:
      stackarg_assignment(Item *w, Item *M);
      void accept(Visitor *visitor) override;
      void gen(Function *f, std::ofstream &outputFile) override;
      void insert(Function *f, std::ofstream &outputFile, int i);
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      Item *w;
      Item *M;
  };


 // OUR OWN CLASSES 
  class label_Instruction : public Instruction{
    public:
      label_Instruction(Item *label);
      void accept(Visitor *visitor) override;
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      std::string getLabel() {
          Label *labelPtr = dynamic_cast<Label*>(label);
          return labelPtr->getLabel();
      }
      Item *label; 
  };

  class goto_label_instruction : public label_Instruction {
    public:
      void accept(Visitor *visitor) override;
      goto_label_instruction(Item *label);
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
  };

  class Call_tenserr_Instruction: public Instruction {
    public:
      void accept(Visitor *visitor) override;
      Call_tenserr_Instruction(Item *F);
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      Item *F;
  };
  
  class Call_uN_Instruction : public Instruction {
    public:
      Call_uN_Instruction(Item *u, Item *N);
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      void accept(Visitor *visitor) override;
      Item *u;
      Item *N;
  };
  class Call_print_Instruction : public Instruction {
    // call print 1 
    public:
      void accept(Visitor *visitor) override;
      Call_print_Instruction();
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
  };
  class Call_input_Instruction : public Instruction {
    // call input 0 
    public:
      Call_input_Instruction();
      void accept(Visitor *visitor) override;
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
  };
  class Call_allocate_Instruction : public Instruction {
    // call allocate 2
    public:
      Call_allocate_Instruction();
      void accept(Visitor *visitor) override;
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
  };
  class Call_tuple_Instruction : public Instruction {
    // call tuple-error 3
    public:
      Call_tuple_Instruction();
      void accept(Visitor *visitor) override;
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
  };

  class w_increment_decrement : public Instruction {
    public:
      w_increment_decrement(Item *r, Item *symbol);
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      void accept(Visitor *visitor) override;
      Item *r;
      Item *symbol;
  };

  class w_atreg_assignment : public Instruction {
    // w1 @ w2 w3 E   
    public:
      w_atreg_assignment(Item *r1, Item *r2, Item *r3, Item *E);
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      void accept(Visitor *visitor) override;
      Item *r1;
      Item *r2; 
      Item *r3; 
      Item *E; 
  };

  class Memory_assignment_store : public Instruction {
    public:
      Memory_assignment_store(Item *dst, Item *s, Item *M);
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      void accept(Visitor *visitor) override;
      Item *dst;
      Item *s;
      Item *M;
  };


  class Memory_assignment_load : public Instruction {
    public:
      Memory_assignment_load(Item *dst, Item *x, Item *M);
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      void accept(Visitor *visitor) override;
      Item *dst;
      Item *x;
      Item *M;
  };

  class Memory_arithmetic_load : public Instruction {
    public:
      Memory_arithmetic_load(Item *dst, Item *x, Item *instruction, Item *M);
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      void accept(Visitor *visitor) override;
      Item *dst;  // w
      Item *x;
      Item *instruction;
      Item *M;
  };

  class Memory_arithmetic_store : public Instruction {
    public:
      Memory_arithmetic_store(Item *dst, Item *t, Item *instruction, Item *M);
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      void accept(Visitor *visitor) override;
      Item *dst;
      Item *t;
      Item *instruction;
      Item *M;
  };

  class cmp_Instruction : public Instruction {
    // w <- t2 cmp t1
    public:
      cmp_Instruction(Item *dst, Item *t2, Item *method, Item *t1);
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      void accept(Visitor *visitor) override;
      Item *dst;
      Item *t1;
      Item *method;
      Item *t2;
  };

  class cjump_cmp_Instruction : public Instruction {
    public:
      cjump_cmp_Instruction(Item *t2, Item *cmp, Item *t1, Item *label);
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      void accept(Visitor *visitor) override;
      std::string getLabel() const {
          const Label *labelPtr = dynamic_cast<const Label*>(label);
          if (labelPtr) {
              return labelPtr->getLabel();
          }
          return ""; // Or handle the error as appropriate
      }
      Item *t2;
      Item *cmp;
      Item *t1;
      Item *label;
  };

  // class stackarg_assignment: public Instruction_assignment {
  //   public:
  //     stackarg_assignment(Item *w,Item *op, Item *M);
  //     virtual void accept(Visitor *visitor) = 0; // Accept a visitor
  //     void gen(Function *f, std::ofstream &outputFile) override;
  //     void printMe() override;
  //     Item *w;
  //     Item *op;
  //     Item *M;
  // };
  class AOP_assignment : public Instruction {
    public:
      AOP_assignment(Item *method, Item *dst, Item *src);
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      void accept(Visitor *visitor) override;
      Item *method;
      Item *dst;
      Item *src;
  };

  class SOP_assignment : public Instruction {
    public:
      SOP_assignment(Item *method, Item *dst, Item *src);
      void gen(Function *f, std::ofstream &outputFile) override;
      void spill_gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      void accept(Visitor *visitor) override;
      Item *method;
      Item *dst;
      Item *src;
  };
  
// OUR OWN FUNCTIONs

  /*
   * Function.
   */
  class Function{
    public:
      std::string name;
      int64_t arguments;
      int64_t locals;
      std::vector<Instruction *> instructions;
      VariableAllocator variable_allocator;
      std::set<Variable *> spilled_variables; // for original variables in the L2 program that need to be spilled
      std::set<Variable *> spill_variables_set;   // for our custom variables that we replace spilled variables with
      std::set<std::string> string_spill_variables_set;
      void calculateCFG();
      void calculateUseDefs();
  }; 

  class Program{
    public:
      std::string entryPointLabel;
      std::vector<Function *> functions;
      std::vector<Variable *> variables;
      void update_function(Function *oldFunction, Function *newFunction);
  };

  class Visitor {
    public:
      // virtual void visit(Function function) = 0;
      // virtual void visit(Instruction *instruction) = 0;
      virtual void visit(Instruction_ret *instruction) = 0;
      virtual void visit(Instruction_assignment *instruction) = 0;
      virtual void visit(label_Instruction *instruction) = 0;
      virtual void visit(goto_label_instruction *instruction) = 0;
      virtual void visit(Call_tenserr_Instruction *instruction) = 0;
      virtual void visit(Call_uN_Instruction *instruction) = 0;
      virtual void visit(Call_print_Instruction *instruction) = 0;
      virtual void visit(Call_input_Instruction *instruction) = 0;
      virtual void visit(Call_allocate_Instruction *instruction) = 0;
      virtual void visit(Call_tuple_Instruction *instruction) = 0;
      virtual void visit(w_increment_decrement *instruction) = 0;
      virtual void visit(w_atreg_assignment *instruction) = 0;
      virtual void visit(Memory_assignment_store *instruction) = 0;
      virtual void visit(Memory_assignment_load *instruction) = 0;
      virtual void visit(Memory_arithmetic_load *instruction) = 0;
      virtual void visit(Memory_arithmetic_store *instruction) = 0;
      virtual void visit(cmp_Instruction *instruction) = 0;
      virtual void visit(cjump_cmp_Instruction *instruction) = 0;
      virtual void visit(stackarg_assignment *instruction) = 0;
      virtual void visit(AOP_assignment *instruction) = 0;
      virtual void visit(SOP_assignment *instruction) = 0;
  };
  class UseDefVisitor: public Visitor {
    public:
      // void visit(Function function) override;
      // void visit(Instruction *instruction) override;
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
  };
  class SpillVisitor:public Visitor{
    public:
      SpillVisitor(Variable* spilledVar, Variable* replacementVar,int count = 0) :
        spilledVariable(spilledVar), replacementVariable(replacementVar){}
      bool replaceIfSpilled(Item*& item);
      void iterReplacementVariable();
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
      Variable* spilledVariable;
      Variable* replacementVariable;
      bool spilledLHS;
      bool spilledRHS; 
  };
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
  class PrintVisitor:  public Visitor {
    public:
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
  };

  /*
  Liveness Analysis Storage Classes
  */
  enum SetType {
    in,
    out,
    gen,
    kill
  };

  class In_Out_Store {
    public:
      In_Out_Store(Program *p);
      void print_sets(int function_index, Instruction* instruction_ptr);
      std::vector<std::unordered_map<Instruction*, std::set<Variable*>>> In_Set;
      std::vector<std::unordered_map<Instruction*, std::set<Variable*>>> Out_Set;
  };

  class Gen_Kill_Store {
    public:
      Gen_Kill_Store(Program *p);
      void print_sets(int function_index, Instruction* instruction_ptr);
      std::vector<std::unordered_map<Instruction*, std::set<Variable*>>> Gen_Set;
      std::vector<std::unordered_map<Instruction*, std::set<Variable*>>> Kill_Set;
  };

  struct LivenessResult {
    Gen_Kill_Store gen_kill_sets;
    In_Out_Store in_out_sets;
  };

  struct Curr_F_Liveness {
    std::unordered_map<Instruction*, std::set<Variable*>> gen;
    std::unordered_map<Instruction*, std::set<Variable*>> kill;
    std::unordered_map<Instruction*, std::set<Variable*>> in;
    std::unordered_map<Instruction*, std::set<Variable*>> out;
  };

  /*
  Utility Functions
  */
  void printFunction(Function* fptr);
  
}