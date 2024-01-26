#pragma once

#include <vector>
#include <string>
#include <variant>
#include <iostream>

namespace L1 {

  extern const int debug;


  // Forward declarations
  class Function;
  class Program;

  class Item {
    public:

      virtual std::string translate() = 0;    // returns string with the x86 conventions attached
      virtual std::string print() = 0;        // returns the value as is

  };
  /*
  Register = 0
  Number = 1
  Name = 2
  Label = 3
  */

  class Register : public Item {
    public:
      Register (const std::string &value);
      std::string translate() override;
      std::string print() override;
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
    private:
      std::string value;
  };

  class Operator : public Item {
    public:
      Operator (const std::string &sign);
      std::string translate() override;
      std::string print() override;
    private:
      std::string sign;
  };

  /*
   * Instruction interface.
   */
  class Instruction{
    public:
      virtual void gen(Function *f, std::ofstream &outputFile) = 0;
      virtual void printMe() = 0;
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

  class label_Instruction : public Instruction{
    public:
      label_Instruction(Item *label);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
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
    private:
      Item *t2;
      Item *cmp;
      Item *t1;
      Item *label;
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

  /*
   * Function.
   */
  class Function{
    public:
      std::string name;
      int64_t arguments;
      int64_t locals;
      std::vector<Instruction *> instructions;
  };

  class Program{
    public:
      std::string entryPointLabel;
      std::vector<Function *> functions;
  };

}