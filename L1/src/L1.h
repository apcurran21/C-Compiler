#pragma once

#include <vector>
#include <string>
#include <variant>
#include <iostream>

namespace L1 {

  // Forward declaration of the Function class
  class Function;


  enum RegisterID {   // this list currently corresponds with L1 grammar definition 'x' 
    rdi,
    rsi,
    rdx,
    rcx,
    r8,
    r9,
    rax,
    rbx,
    rbp,
    r10,
    r11,
    r12,
    r13,
    r14,
    r15,
    rsp   // note - i'm not sure if the stack pointer register should belong here
  };
  using ItemValue = std::variant<int, std::string, RegisterID>; // Example using variant

  class Item {
    public:
      virtual ~Item() {}  // Virtual destructor
      virtual ItemValue getValue() const { return value; }
      virtual void setValue(const ItemValue& newValue) { value = newValue; }
    protected:
      ItemValue value;
      virtual void print() = 0;
  };

  class Register : public Item {
    public:
      Register (RegisterID r);
      ~Register();
      void print() override;
    private:
      RegisterID ID;
  };

  class Integer : public Item {
    public:
      Integer(int value);
      ~Integer();
      void print() override;
    private:
      int value;
  };

  class String : public Item {
    public:
      String(const std::string& value);
      ~String();
      void print() override;
    private:
      std::string value;
  };
  // We honestly should write classes for methods/instructions that can be inherited from Item instead of using std::string

  /*
   * Instruction interface.
   */
  class Instruction{
  };

  /*
   * Instructions.
   */
  class Instruction_ret : public Instruction{
  };

  class Instruction_assignment : public Instruction{
    public:
      Instruction_assignment (Item *dst, Item *src);

    private:
      Item *s;
      Item *d;
  };


 // OUR OWN CLASSES 

  class incdec_instruction : public Instruction{
    public:
      incdec_instruction(Item *reg, Item *method);
    private:
      Item *reg; 
      Item *method;
  };

  class label_Instruction : public Instruction{
    public:
      label_Instruction(Item *label);
    private:
      Item *label; 
  };

  class goto_label_instruction : public label_Instruction {
    public:
      goto_label_instruction(Item *method, Item *label);
    private:
      Item *method;
  };

  class Call_Instruction : public Instruction {
    // // all call functions except call u N and call tensor-erro
    // public:
    //   Call_Instruction(String method,String instruction, String symbol);
    // private:
    //   String method;
    //   String instruction;
    //   String symbol;
    public:
      Call_Instruction(Item *method);
    private:
      Item *method;
  };

  class Call_tenserr_Instruction: public Instruction {
    public:
      Call_tenserr_Instruction(Item *F);
    private:
      Item *F;
  };
  
  class Call_uN_Instruction : public Instruction {
    public:
      Call_uN_Instruction(Item *u, Item *N);
    private:
      Item *u;
      Item *N;
  };
  class Call_print_Instruction : public Instruction {
    // call print 1 
    public:
      Call_print_Instruction();
  };
  class Call_input_Instruction : public Instruction {
    // call input 0 
    public:
      Call_input_Instruction();
  };
  class Call_allocate_Instruction : public Instruction {
    // call allocate 2
    public:
      Call_allocate_Instruction();
  };
  class Call_tuple_Instruction : public Instruction {
    // call tuple-error 3
    public:
      Call_tuple_Instruction();
  };

  class w_increment_decrement : public Instruction {
    public:
      w_increment_decrement(Item *r, Item *symbol);
    private:
      Item *r;
      Item *symbol;
  };

  class w_atreg_assignment : public Instruction {
    public:
      w_atreg_assignment(Item *r1, Item *r2, Item *r3, Item *E);
    private:
      Item *r1;
      Item *r2; 
      Item *r3; 
      Item *E; 
  };

  class Memory_assignment : public Instruction {
    public:
      Memory_assignment(Item *dst, Item *method, Item *x, Item *M);
    private:
      Item *dst;
      Item *method;
      Item *x;
      Item *M;
  };

  class Memory_arithmetic : public Instruction {
    public:
      Memory_arithmetic(Item *dst, Item *method, Item *x, Item *instruction, Item *M);
    private: 
      Item *dst;
      Item *method;
      Item *x;
      Item *instruction;
      Item *M;
  };

  class cmp_Instruction : public Instruction {
    // w <- t cmp t 
    public:
      cmp_Instruction(Item *dst, Item *t1, Item *method, Item *t2);
    private:
      Item *dst;
      Item *t1;
      Item *method;
      Item *t2;
  };

  class cjump_cmp_Instruction : public Instruction {
    public:
      cjump_cmp_Instruction(Item *t1, Item *method, Item *t2, Item *label);
    private:
      Item *t1;
      Item *method;
      Item *t2;
      Item *label;
  };

  
  class AOP_assignment : public Instruction_assignment {
    public:
      AOP_assignment(Item *method, Item *dst, Item *src);
    private:
      Item *method;
  };

  class SOP_assignment : public Instruction_assignment {
    public:
      SOP_assignment(Item *method, Item *dst, Item *src);
    private:
      Item *method;
  };
  
  // class String_Instruction_Assignment : public Instruction_assignment {
  //   public:
  //     String_Instruction_Assignment(String method, Item *dst, Item *src);
    
  //   private:
  //     Item *s;
  //     Item *d;
  //     String method;
  // };

  // class AOP_assignment : public String_Instruction_Assignment {
  //   public:
  //     AOP_assignment(Item *method, Item *dst, Item *src);
  // };

  // class SOP_assignment : public String_Instruction_Assignment {
  //   public:
  //     SOP_assignment(Item *method, Item *dst, Item *src);
  // };


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
