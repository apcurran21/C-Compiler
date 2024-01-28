#pragma once
#include <set>
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>
#include <iostream>

namespace L2 {

  extern const int debug;

  // Forward declarations
  class Function;
  class Program;
  class Item;
  class Instruction;
  class Variable;


  // class In_Out_Store {
  //   public:
  //     In_Out_Store(int num_functions, std::vector<int> nums_instructions);
  //     int get_size(SetType from_where, int function_index, int instruction_index);
  //   private:
  //     std::vector<std::vector<std::set<Variable*>>> In_Set;
  //     std::vector<std::vector<std::set<Variable*>>> Out_Set;
  // };

  // class Gen_Kill_Store {
  //   public:
  //     Gen_Kill_Store(int num_functions, std::vector<int> nums_instructions);
  //     int get_size(SetType from_where, int function_index, int instruction_index);
  //   private:
  //     std::vector<std::vector<std::set<Variable*>>> Gen_Set;
  //     std::vector<std::vector<std::set<Variable*>>> Kill_Set;
  // };

  /*
  CFG Class
  */
  class CFG {
    public:
        struct Node {
            Instruction* instr;
            std::set<int> predecessors;
            std::set<int> successors;
        };

        Function* function; // Reference to the function the CFG belongs to.
        std::vector<Node> nodes; // Nodes of the CFG, could correspond to instructions or basic blocks.

        CFG(Function* f);
        void buildCFG();
        
  };

  /*
  Liveness Analysis Visitor Class
  */
  // class LiveAnalysisVisitor : public Visitor {
  // public:
  //   void visit(Function &function) override {}
  //   void visit(Instruction &instruction) override {}
  //   void visit(Instruction_ret &instruction) override {}
  //   void visit(Instruction_assignment &instruction) override {}
  //   void visit(label_Instruction &instruction) override {}
  //   void visit(goto_label_instruction &instruction) override {}
  //   void visit(Call_tenserr_Instruction &instruction) override {}
  //   void visit(Call_uN_Instruction &instruction) override {}
  //   void visit(Call_print_Instruction &instruction) override {}
  //   void visit(Call_input_Instruction &instruction) override {}
  //   void visit(Call_allocate_Instruction &instruction) override {}
  //   void visit(Call_tuple_Instruction &instruction) override {}
  //   void visit(w_increment_decrement &instruction) override {}
  //   void visit(w_atreg_assignment &instruction) override {}
  //   void visit(Memory_assignment_store &instruction) override {}
  //   void visit(Memory_assignment_load &instruction) override {}
  //   void visit(Memory_arithmetic_load &instruction) override {}
  //   void visit(Memory_arithmetic_store &instruction) override {}
  //   void visit(cmp_Instruction &instruction) override {}
  //   void visit(cjump_cmp_Instruction &instruction) override {}
  //   void visit(stackarg_assignment &instruction) override {}
  //   void visit(AOP_assignment &instruction) override {}
  //   void visit(SOP_assignment &instruction) override {}
  //   void liveness_analysis();
  // };


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
      std::string print() override;
    private:
      std::string name;
  };
  class Register : public Variable {
    public:
      Register (const std::string &value);
      std::string getID() const {
        return ID;
      };
      bool operator==(const Register &other) const;
    private:
      std::string ID;
  };

  class Number : public Item {
    public:
      Number (int64_t n);
      std::string translate() override;
      std::string print() override;
    private:
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
    private:
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
      // virtual void accept(Visitor &visitor) = 0; // Accept a visitor
      virtual void gen(Function *f, std::ofstream &outputFile) = 0;
      virtual void printMe() = 0;
      std::set<Instruction *> predecessors;
      std::set<Instruction *> successors;
      std::set<Variable *> used;
      std::set<Variable *> defined;
  };

  /*
   * Instructions.
   */
  class Instruction_ret : public Instruction{
    public:
      Instruction_ret ();
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
  };

  class Instruction_assignment : public Instruction{
    public:
      Instruction_assignment (Item *dst, Item *src);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
    protected:
      Item *s;
      Item *d;
  };


 // OUR OWN CLASSES 

  class label_Instruction : public Instruction{
    public:
      label_Instruction(Item *label);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      std::string getLabel() const {
          const Label *labelPtr = dynamic_cast<const Label*>(label);
          if (labelPtr) {
              return labelPtr->getLabel();
          }
      }
    protected:
      Item *label; 
  };

  class goto_label_instruction : public label_Instruction {
    public:
      goto_label_instruction(Item *label);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
  };

  class Call_tenserr_Instruction: public Instruction {
    public:
      Call_tenserr_Instruction(Item *F);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
    private:
      Item *F;
  };
  
  class Call_uN_Instruction : public Instruction {
    public:
      Call_uN_Instruction(Item *u, Item *N);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
    private:
      Item *u;
      Item *N;
  };
  class Call_print_Instruction : public Instruction {
    // call print 1 
    public:
      Call_print_Instruction();
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
  };
  class Call_input_Instruction : public Instruction {
    // call input 0 
    public:
      Call_input_Instruction();
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
  };
  class Call_allocate_Instruction : public Instruction {
    // call allocate 2
    public:
      Call_allocate_Instruction();
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
  };
  class Call_tuple_Instruction : public Instruction {
    // call tuple-error 3
    public:
      Call_tuple_Instruction();
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
  };

  class w_increment_decrement : public Instruction {
    public:
      w_increment_decrement(Item *r, Item *symbol);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
    private:
      Item *r;
      Item *symbol;
  };

  class w_atreg_assignment : public Instruction {
    // w1 @ w2 w3 E   
    public:
      w_atreg_assignment(Item *r1, Item *r2, Item *r3, Item *E);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
    private:
      Item *r1;
      Item *r2; 
      Item *r3; 
      Item *E; 
  };

  class Memory_assignment_store : public Instruction {
    public:
      Memory_assignment_store(Item *dst, Item *s, Item *M);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
    private:
      Item *dst;
      Item *s;
      Item *M;
  };


  class Memory_assignment_load : public Instruction {
    public:
      Memory_assignment_load(Item *dst, Item *x, Item *M);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
    private:
      Item *dst;
      Item *x;
      Item *M;
  };

  class Memory_arithmetic_load : public Instruction {
    public:
      Memory_arithmetic_load(Item *dst, Item *x, Item *instruction, Item *M);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
    private: 
      Item *dst;  // w
      Item *x;
      Item *instruction;
      Item *M;
  };

  class Memory_arithmetic_store : public Instruction {
    public:
      Memory_arithmetic_store(Item *dst, Item *t, Item *instruction, Item *M);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
    private: 
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
      void printMe() override;
    private:
      Item *dst;
      Item *t1;
      Item *method;
      Item *t2;
  };

  class cjump_cmp_Instruction : public Instruction {
    public:
      cjump_cmp_Instruction(Item *t2, Item *cmp, Item *t1, Item *label);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      std::string getLabel() const {
          const Label *labelPtr = dynamic_cast<const Label*>(label);
          if (labelPtr) {
              return labelPtr->getLabel();
          }
          return ""; // Or handle the error as appropriate
      }
    private:
      Item *t2;
      Item *cmp;
      Item *t1;
      Item *label;
  };

  class stackarg_assignment: public Instruction_assignment {
    public:
      stackarg_assignment(Item *w,Item *op, Item *M);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
    private:
      Item *w;
      Item *op;
      Item *M;
  };
  class AOP_assignment : public Instruction_assignment {
    public:
      AOP_assignment(Item *method, Item *dst, Item *src);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
    private:
      Item *method;
  };

  class SOP_assignment : public Instruction_assignment {
    public:
      SOP_assignment(Item *method, Item *dst, Item *src);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
    private:
      Item *method;
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
      void calculateCFG();
  };

  class Program{
    public:
      std::string entryPointLabel;
      std::vector<Function *> functions;
  };

  class Visitor {
    public:
      virtual void visit(Function &function) = 0;
      virtual void visit(Instruction &instruction) = 0;
      virtual void visit(Instruction_ret &instruction) = 0;
      virtual void visit(Instruction_assignment &instruction) = 0;
      virtual void visit(label_Instruction &instruction) = 0;
      virtual void visit(goto_label_instruction &instruction) = 0;
      virtual void visit(Call_tenserr_Instruction &instruction) = 0;
      virtual void visit(Call_uN_Instruction &instruction) = 0;
      virtual void visit(Call_print_Instruction &instruction) = 0;
      virtual void visit(Call_input_Instruction &instruction) = 0;
      virtual void visit(Call_allocate_Instruction &instruction) = 0;
      virtual void visit(Call_tuple_Instruction &instruction) = 0;
      virtual void visit(w_increment_decrement &instruction) = 0;
      virtual void visit(w_atreg_assignment &instruction) = 0;
      virtual void visit(Memory_assignment_store &instruction) = 0;
      virtual void visit(Memory_assignment_load &instruction) = 0;
      virtual void visit(Memory_arithmetic_load &instruction) = 0;
      virtual void visit(Memory_arithmetic_store &instruction) = 0;
      virtual void visit(cmp_Instruction &instruction) = 0;
      virtual void visit(cjump_cmp_Instruction &instruction) = 0;
      virtual void visit(stackarg_assignment &instruction) = 0;
      virtual void visit(AOP_assignment &instruction) = 0;
      virtual void visit(SOP_assignment &instruction) = 0;
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
    private:
      std::vector<std::unordered_map<Instruction*, std::set<Variable*>> In_Set;
      std::vector<std::unordered_map<Instruction*, std::set<Variable*>> Out_Set;
  };
}