#include <string>
#include <iostream>
#include <fstream>

#include <code_generator.h>
#include "L1.h"

using namespace std;

// use 1 for debug statements, 0 for no printing
// int debug = 1;

namespace L1{

  /*
  Assembly generating methods
  */
  void Instruction_ret::gen(Program &p, std::ofstream &outputFile) {
    // return translates to retq

    if (debug) std::cerr << "gen method called for an Instruction_ret instance!" << std::endl;

    outputFile << "retq\n";
  }

  void Instruction_assignment::gen(Program &p, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for an Instruction_assignment class!" << std::endl;
    std::string dest = this->d->translate();
    std::string src = this->s->translate();
      
    outputFile << "movq " << src << ", " << dest << "\n";
  }

  void incdec_instruction::gen(Program &p, std::ofstream &outputFile) {

  }

  void label_Instruction::gen(Program &p, std::ofstream &outputFile) {

  }

  void goto_label_instruction::gen(Program &p, std::ofstream &outputFile) {

  }

  // void Call_Instruction::gen(Program &p, std::ofstream &outputFile) {

  // }

  void Call_tenserr_Instruction::gen(Program &p, std::ofstream &outputFile) {

  }

  void Call_uN_Instruction::gen(Program &p, std::ofstream &outputFile) {

  }

  void Call_print_Instruction::gen(Program &p, std::ofstream &outputFile) {

  }

  void Call_input_Instruction::gen(Program &p, std::ofstream &outputFile) {

  }

  void Call_allocate_Instruction::gen(Program &p, std::ofstream &outputFile) {

  }

  void Call_tuple_Instruction::gen(Program &p, std::ofstream &outputFile) {

  }

  void w_increment_decrement::gen(Program &p, std::ofstream &outputFile) {

  }

  void w_atreg_assignment::gen(Program &p, std::ofstream &outputFile) {

  }

  void Memory_assignment::gen(Program &p, std::ofstream &outputFile) {

  }

  void Memory_arithmetic::gen(Program &p, std::ofstream &outputFile) {

  }

  void cmp_Instruction::gen(Program &p, std::ofstream &outputFile) {

  }

  void cjump_cmp_Instruction::gen(Program &p, std::ofstream &outputFile) {

  }

  void AOP_assignment::gen(Program &p, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for an AOP_assignment instruction class!" << std::endl;

    std::string op = this->method->translate();
    if (debug) std::cerr << "op = " << op << std::endl;
    std::string dest = this->d->translate();
    if (debug) std::cerr << "dest = " << dest << std::endl;
    std::string src = this->s->translate();
    if (debug) std::cerr << "src = " << src << std::endl;

    outputFile << op << " " << src << ", " << dest << "\n";
  }

  void SOP_assignment::gen(Program &p, std::ofstream &outputFile) {
    
  }


  void generate_code(Program p){

    /* 
     * Open the output file.
     */ 
    std::ofstream outputFile;
    outputFile.open("prog.S");
   
    /* 
     * Generate target code
     */ 
    // boilerplate
    outputFile << ".text\n.globl go\ngo:\npushq %rbx\npushq %rbx\npushq %r12\npushq %r13\npushq %r14\npushq %r15\n";
    std::string entry_lab = p.entryPointLabel;
    outputFile << "call " << entry_lab.replace(0, 1, "_") << "\n";
    outputFile << "popq %r15\npopq %r14\npopq %r13\npopq %r12\npopq %rbp\npopq %rbx\nretq\n";

    // main loop
    for (Function *fptr : p.functions) {
      std::string fname = fptr->name;

      std::cout << "Currently generating for function " << fname << std::endl;

      outputFile << fname.replace(0, 1, "_") << ":\n";

      for (Instruction *iptr : fptr->instructions) {
        std::cout << "Currently generating an instruction:" << std::endl;

        iptr->gen(p, outputFile);
      }
    }

    /* 
     * Close the output file.
     */ 
    outputFile.close();
   
    return ;
  }
}
