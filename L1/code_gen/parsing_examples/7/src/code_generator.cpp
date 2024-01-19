#include <string>
#include <iostream>
#include <fstream>

#include <code_generator.h>
#include "L1.h"

using namespace std;

namespace L1{

  /*
    Assembly generating methods
  */
  void Instruction_ret::gen(Program &p, std::ofstream &outputFile) {
    // return translates to retq

    std::cout << "gen method called for an Instruction_ret instance!" << std::endl;

    outputFile << "retq\n";
  }

  void Instruction_assignment::gen(Program &p, std::ofstream &outputFile) {
    std::cout << "gen method called for an Instruction_assignment class!" << std::endl;

    std::string dreg = this->d->translate();
    std::string sreg = this->s->translate();
    
    outputFile << "movq " << sreg << ", " << dreg << "\n";
  }


  void generate_code(Program p){

    std::cout << "Beginning the code generation process." << std::endl;

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
