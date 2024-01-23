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

  // enum RegisterID {   // this list currently corresponds with L1 grammar definition 'x' 
  //   rdi,
  //   rsi,
  //   rdx,
  //   rcx,
  //   r8,
  //   r9,
  //   rax,
  //   rbx,
  //   rbp,
  //   r10,
  //   r11,
  //   r12,
  //   r13,
  //   r14,
  //   r15,
  //   rsp   // note - i'm not sure if the stack pointer register should belong here
  // };
  // using ItemValue = std::variant<int, std::string, RegisterID>; // Example using variant

  class Item {
    public:

      virtual std::string translate() = 0;    // returns string with the x86 conventions attached
      virtual std::string print() = 0;        // returns the value as is

      // virtual ~Item() {};  // Virtual destructor
      // virtual ItemValue getValue() const { return value; }
      // virtual void setValue(const ItemValue& newValue) { value = newValue; }
      
      // each derived class returns a unique integer which we can condition check in the code generator
    //   virtual int give_status();
    // protected:
    //   ItemValue value;
    //   virtual void print() = 0;
  };

  // Register = 0
  // Integer = 1
  // String = 2

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

      // ~Register();
      // void print() override;
      // int give_status() override;
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

  // class Integer : public Item {
  //   // for things like 21
  //   public:
  //     Integer(int value);
  //     ~Integer();
  //     void print() override;
  //     int give_status() override;
  //   private:
  //     int value;
  // };

  // class String : public Item {
  //   // for things like @name
  //   public:
  //     String(const std::string& value);
  //     ~String();
  //     void print() override;
  //     int give_status() override;
  //   private:
  //     std::string value;
  // };
  // We honestly should write classes for methods/instructions that can be inherited from Item instead of using std::string

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


 // OUR OWN CLASSES 

  // // I don't think this instruction is being used
  // class incdec_instruction : public Instruction{
  //   public:
  //     incdec_instruction(Item *reg, Item *method);
  //     void gen(Function *f, std::ofstream &outputFile) override;
  //     void printMe() override;
  //   private:
  //     Item *reg; 
  //     Item *method;
  // };

  class label_Instruction : public Instruction{
    public:
      label_Instruction(Item *label);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
      // void gen(Function *f, std::ofstream &outputFile) override;
    protected:
      Item *label; 
  };

  class goto_label_instruction : public label_Instruction {
    public:
      goto_label_instruction(Item *label);
      void gen(Function *f, std::ofstream &outputFile) override;
      void printMe() override;
  };

  // class goto_label_instruction : public label_Instruction {
  //   public:
  //     goto_label_instruction(Item *method, Item *label);
  //     void gen(Function *f, std::ofstream &outputFile) override;
  //   private:
  //     Item *method;
  // };

  // // note that this class doesn't seem to be used anywhere
  // class Call_Instruction : public Instruction {
  //   // // all call functions except call u N and call tensor-error
  //   // public:
  //   //   Call_Instruction(String method,String instruction, String symbol);
  //   // private:
  //   //   String method;
  //   //   String instruction;
  //   //   String symbol;
  //   public:
  //     Call_Instruction(Item *method);
  //     void gen(Function *f, std::ofstream &outputFile) override;
  //     void printMe() override;
  //   private:
  //     Item *method;
  // };

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
    // w <- t cmp t 
    public:
      cmp_Instruction(Item *dst, Item *t1, Item *method, Item *t2);
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
  };

  class Program{
    public:
      std::string entryPointLabel;
      std::vector<Function *> functions;
  };

}