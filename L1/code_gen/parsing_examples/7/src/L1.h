#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace L1 {

  // forward declaration of Program
  class Program;

  enum RegisterID {rdi, rax};

  class Item {
    public:
      virtual int translate() = 0;
  };

  /*
  Register = 0
  Number = 1
  Name = 2
  Label = 3
  */

  class Register : public Item {
    public:
      Register (std::string r);
      int translate() override;
      std::string get_ID();
    private:
      std::string ID;
  };

  class Number : public Item {
    public:
      Number (int n);
      int translate() override;
      int get_value();
    private:
      int value;
  };

  class Name : public Item {
    public:
      Name (const std::string &value);
      int translate() override;
      std::string get_value();
    private:
      std::string value;
  };

  class Label : public Item {
    public:
      Label (const std::string &value);
      int translate() override;
      std::string get_value();
    private:
      std::string value;
  };

  /*
   * Instruction interface.
   */
  class Instruction{
    public:
      virtual void gen(Program &p, std::ofstream &outputFile) = 0;
  };

  /*
   * Instructions.
   */
  class Instruction_ret : public Instruction{
    public:
      void gen(Program &p, std::ofstream &outputFile) override;
  };

  class Instruction_assignment : public Instruction{
    public:
      Instruction_assignment (Item *dst, Item *src);
      void gen(Program &p, std::ofstream &outputFile) override;
    private:
      Item *s;
      Item *d;
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
