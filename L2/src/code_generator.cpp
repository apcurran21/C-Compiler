#include <string>
#include <iostream>
#include <fstream>
#include "L2.h"
#include <code_generator.h>

using namespace std;

// use 1 for debug statements, 0 for no printing
// int debug = 1;

namespace L2{

  /*
  Assembly generating methods
  */
  void Instruction_ret::gen(Function *f, std::ofstream &outputFile) {
    outputFile << "return\n\t";
  }

  void Instruction_assignment::gen(Function *f, std::ofstream &outputFile) {
    outputFile << this->d->print() << " <- " << this->s->print() << "\n\t";
  }

  void label_Instruction::gen(Function *f, std::ofstream &outputFile) {
    outputFile << ":" << this->label->print()<<"\n\t";
  }

  void goto_label_instruction::gen(Function *f, std::ofstream &outputFile) {
    outputFile << "goto" << this->label->print() << "\n\t";
  }

  void Call_tenserr_Instruction::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a Call_tenserr_instruction instance!" << std::endl;
    long long num = std::stoll(this->F->print());
    outputFile << "call tensor-error "<< this->F->print()<<"\n\t";
  }

  void Call_uN_Instruction::gen(Function *f, std::ofstream &outputFile) {
    outputFile << "call "<< this->u->print() << " "<< this->N->print()<<"\n\t";
  }

  void Call_print_Instruction::gen(Function *f, std::ofstream &outputFile) {
    outputFile << "call print 1\n\t";
  }

  void Call_input_Instruction::gen(Function *f, std::ofstream &outputFile) {
    outputFile << "call input 0\n\t";
  }

  void Call_allocate_Instruction::gen(Function *f, std::ofstream &outputFile) {
    outputFile << "call allocate 2\n\t";
  }

  void Call_tuple_Instruction::gen(Function *f, std::ofstream &outputFile) {
    outputFile << "call tuple_error 3\n\t";
  }

  void w_increment_decrement::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a w_increment_decrement instance!" << std::endl;
    outputFile << this->r->print() << this->symbol->print() << "\n\t";
  }

  void w_atreg_assignment::gen(Function *f, std::ofstream &outputFile) {
    // w1 @ w2 w3 E   
    outputFile << this->r1->print() << " @ "<<this->r2->print() <<" "<<this->r3->print()<<" "<<this->E->print()<<"\n\t";
  }

  void Memory_assignment_store::gen(Function *f, std::ofstream &outputFile) {
    outputFile << "mem "<<this->s->print()<<" "<<this->M->print()<<" <- "<<this->s->print()<<"\n\t";
  }

  void Memory_assignment_load::gen(Function *f, std::ofstream &outputFile) {
    outputFile << this->dst->print() <<" <- "<<"mem "<<this->x->print()<<" "<<this->M->print()<<"\n\t";
  }

  void Memory_arithmetic_load::gen(Function *f, std::ofstream &outputFile) {
    outputFile << this->dst->print()<<" "<< this->instruction->print()<<" mem "<<this->x->print()<<" "<<this->M->print()<<"\n\t";  
  }

  void Memory_arithmetic_store::gen(Function *f, std::ofstream &outputFile) {
    outputFile << "mem "<<this->dst->print()<<" "<<this->M->print()<<" "<<this->instruction->print()<<" "<<this->t->print()<<"\n\t";
  }

  void cmp_Instruction::gen(Function *f, std::ofstream &outputFile) {
    outputFile << this->dst->print()<<" <- "<<this->t2->print()<<" "<<this->method->print()<<" "<<this->t1->print()<<"\n\t";
  }

  void cjump_cmp_Instruction::gen(Function *f, std::ofstream &outputFile) {
    // cjump t2 cmp t1 label
    outputFile << "cjump "<<this->t2->print()<<" "<<this->cmp->print()<<" "<<this->t1->print()<<" "<<this->label->print()<<"\n\t";
  }

  void AOP_assignment::gen(Function *f, std::ofstream &outputFile) {
    outputFile << this->dst->print() << " "<<this->method->print()<<" "<<this->src->print()<<"\n\t";
  }

  void SOP_assignment::gen(Function *f, std::ofstream &outputFile) {
    outputFile << this->dst->print() << " "<<this->method->print()<<" "<<this->src->print()<<"\n\t";
  }

  void stackarg_assignment::gen(Function *f, std::ofstream &outputFile) {
    outputFile << this->w->print()<<" <- stack-arg"<<this->M->print()<<"\n\t";
  }

  void generate_code(Program p, bool changed){

    /* 
     * Open the output file.
     */ 
    std::ofstream outputFile;
    outputFile.open("prog.S");

    // main loop
    for (Function *fptr : p.functions) {
      std::string fname = fptr->name;

      std::cout << "Currently generating for function " << fname << std::endl;

      outputFile << "("<<fname<<"\n\t";
      int variables = 0;
      if (changed){
        variables = 1;
      }
      outputFile << fptr->arguments<<" "<<std::to_string(variables)<<"\n\t";
      for (Instruction *iptr : fptr->instructions) {
        std::cout << "Currently generating an instruction:" << std::endl;
        iptr->gen(fptr, outputFile);
      }
    }
    outputFile<<")";

    if (debug) std::cerr << "Finished code generator!" << std::endl;

    /* 
     * Close the output file.
     */ 
    outputFile.close();
   
    return ;
  }
}
