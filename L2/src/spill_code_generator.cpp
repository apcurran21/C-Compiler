#include <string>
#include <iostream>
#include <fstream>
#include "L2.h"
#include <code_generator.h>

using namespace std;

// use 1 for debug statements, 0 for no printing
// int debug = 1;

namespace L2{


  void Instruction_ret::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << "return\n";
  }

  void Instruction_assignment::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << this->d->print() << " <- " << this->s->print() << "\n\t";
  }

  void label_Instruction::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << this->label->print()<<"\n\t";
  }

  void goto_label_instruction::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << "goto " << this->label->print() << "\n\t";
  }

  void Call_tenserr_Instruction::spill_gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a Call_tenserr_instruction instance!" << std::endl;
    long long num = std::stoll(this->F->print());
    std::cout << "call tensor-error "<< this->F->print()<<"\n\t";
  }

  void Call_uN_Instruction::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << "call "<< this->u->print() << " "<< this->N->print()<<"\n\t";
  }

  void Call_print_Instruction::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << "call print 1\n\t";
  }

  void Call_input_Instruction::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << "call input 0\n\t";
  }

  void Call_allocate_Instruction::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << "call allocate 2\n\t";
  }

  void Call_tuple_Instruction::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << "call tuple_error 3\n\t";
  }

  void w_increment_decrement::spill_gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a w_increment_decrement instance!" << std::endl;
    std::cout << this->r->print() << this->symbol->print() << "\n\t";
  }

  void w_atreg_assignment::spill_gen(Function *f, std::ofstream &outputFile) {
    // w1 @ w2 w3 E   
    std::cout << this->r1->print() << " @ "<<this->r2->print() <<" "<<this->r3->print()<<" "<<this->E->print()<<"\n\t";
  }

  void Memory_assignment_store::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << "mem "<<this->dst->print()<<" "<<this->M->print()<<" <- "<<this->s->print()<<"\n\t";
  }

  void Memory_assignment_load::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << this->dst->print() <<" <- "<<"mem "<<this->x->print()<<" "<<this->M->print()<<"\n\t";
  }

  void Memory_arithmetic_load::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << this->dst->print()<<" "<< this->instruction->print()<<" mem "<<this->x->print()<<" "<<this->M->print()<<"\n\t";  
  }

  void Memory_arithmetic_store::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << "mem "<<this->dst->print()<<" "<<this->M->print()<<" "<<this->instruction->print()<<" "<<this->t->print()<<"\n\t";
  }

  void cmp_Instruction::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << this->dst->print()<<" <- "<<this->t2->print()<<" "<<this->method->print()<<" "<<this->t1->print()<<"\n\t";
  }

  void cjump_cmp_Instruction::spill_gen(Function *f, std::ofstream &outputFile) {
    // cjump t2 cmp t1 label
    std::cout << "cjump "<<this->t2->print()<<" "<<this->cmp->print()<<" "<<this->t1->print()<<" "<<this->label->print()<<"\n\t";
  }

  void AOP_assignment::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << this->dst->print() << " "<<this->method->print()<<" "<<this->src->print()<<"\n\t";
  }

  void SOP_assignment::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << this->dst->print() << " "<<this->method->print()<<" "<<this->src->print()<<"\n\t";
  }

  void stackarg_assignment::spill_gen(Function *f, std::ofstream &outputFile) {
    std::cout << this->w->print()<<" <- stack-arg"<<this->M->print()<<"\n\t";
  }

  // void generate_spill_code(Program p, bool changed,Graph *color_graph){
  void generate_spill_code(Program &p, bool changed) {
    /* 
     * Open the output file.
     */ 
    std::ofstream outputFile;
    outputFile.open("test0.L2f.out2.tmp");

    // main loop
    for (Function *fptr : p.functions) {
      std::string fname = fptr->name;

      // std::cout << "Currently generating for function " << fname << std::endl;

      std::cout << "("<<fname<<"\n\t";
      int variables = 0;
      if (changed){
        variables = 1;
      }
      // ColorVariablesVisitor* myColorVisitor = new ColorVariablesVisitor(color_graph,fptr);
      std::cout << fptr->arguments<<" "<<std::to_string(variables)<<"\n\t";
      for (Instruction *iptr : fptr->instructions) {
        // iptr->accept(myColorVisitor);
        iptr->spill_gen(fptr, outputFile);
      }
    }
    std::cout<<")\n";

    if (debug) std::cerr << "Finished spill code generation!" << std::endl;

    /* 
     * Close the output file.
     */ 
    outputFile.close();
   
    return ;
  }
}
