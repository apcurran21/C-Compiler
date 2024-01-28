#include <string>
#include <iostream>
#include <fstream>

#include <code_generator.h>
#include "L2.h"

using namespace std;

// use 1 for debug statements, 0 for no printing
// int debug = 1;

namespace L2{

  /*
  Helper functions
  */
  std::string convert_reg(std::string r) {
    std::string res = "STOP";

    if (r == "r10") {res = "r10b";}
    else if (r == "r11") {res = "r11b";}
    else if (r == "r12") {res = "r12b";}
    else if (r == "r13") {res = "r13b";}
    else if (r == "r14") {res = "r14b";}
    else if (r == "r15") {res = "r15b";}
    else if (r == "r8") {res = "r8b";}
    else if (r == "r9") {res = "r9b";}
    else if (r == "rax") {res = "al";}
    else if (r == "rbp") {res = "bpl";}
    else if (r == "rbx") {res = "bl";}
    else if (r == "rcx") {res = "cl";}
    else if (r == "rdi") {res = "dil";}
    else if (r == "rdx") {res = "dl";}
    else if (r == "rsi") {res = "sil";}
    else {std::cerr << "Could recognize register " << r << std::endl;}

    return res;
  }

  /*
  Assembly generating methods
  */
  void Instruction_ret::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for an Instruction_ret instance!" << std::endl;
    int req_bytes = f->locals;
    if (f->arguments > 6) {
      req_bytes += (f->arguments-6);
    }
    if (req_bytes > 0) {
      outputFile << "addq $" << (req_bytes * 8) << ", %rsp\n";
    }
    outputFile << "retq\n";
  }

  void Instruction_assignment::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for an Instruction_assignment instance!" << std::endl;
    outputFile << "movq ";
    if (dynamic_cast<Name*>(this->s) || dynamic_cast<Label*>(this->s)) {
      outputFile << "$";
    }
    outputFile << this->s->translate() << ", " << this->d->translate() << "\n";
  }


  void label_Instruction::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a label_Instruction instance!" << std::endl;
    std::string new_label = this->label->print().replace(0, 1, "_");
    outputFile << new_label << ":\n";
  }

  void goto_label_instruction::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a goto_label_instruction instance!" << std::endl;
    std::string new_label = this->label->print().replace(0, 1, "_");
    outputFile << "jmp " << new_label << "\n";
  }

  void Call_tenserr_Instruction::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a Call_tenserr_instruction instance!" << std::endl;
    long long num = std::stoll(this->F->print());
    switch (num) {
      case 1:
        outputFile << "call array_tensor_error_null\n";
        break;
      case 3:
        outputFile << "call array_error\n";
        break;
      case 4:
        outputFile << "call tensor_error\n";
        break;
      default:
        std::cerr << "Didn't recognize the following value as a valid F: " << num << std::endl;
        break;
    }
  }

  void Call_uN_Instruction::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a Call_uN_Instruction instance!" << std::endl;
    int64_t space = 8;
    int64_t num_args = std::stoll(this->N->print());
    if (num_args > 6) space += ((num_args - 6) * 8);
    Number stack_space = Number(space);
    outputFile << "subq " << stack_space.translate() << ", %rsp\n";
    outputFile << "jmp ";
    if (dynamic_cast<Register*>(this->u)) {
      outputFile << "*";
    }
    outputFile << this->u->translate() << "\n";
  }

  void Call_print_Instruction::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a Call_print_instruction instance!" << std::endl;
    outputFile << "call print\n";
  }

  void Call_input_Instruction::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a Call_input_instruction instance!" << std::endl;
    outputFile << "call input\n";
  }

  void Call_allocate_Instruction::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a Call_allocate_instruction instance!" << std::endl;
    outputFile << "call allocate\n";
  }

  void Call_tuple_Instruction::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a Call_tuple_instruction instance!" << std::endl;
    outputFile << "call tuple_error\n";
  }

  void w_increment_decrement::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a w_increment_decrement instance!" << std::endl;
    outputFile << this->symbol->translate() << " " << this->r->translate() << "\n";
  }

  void w_atreg_assignment::gen(Function *f, std::ofstream &outputFile) {
    // w1 @ w2 w3 E   
    if (debug) std::cerr << "gen method called for a w_atreg_assignment instance!" << std::endl;
    outputFile << "lea (" << this->r2->translate() << ", " << this->r3->translate() << ", " << this->E->print() << "), " << this->r1->translate() << "\n";
  }

  void Memory_assignment_store::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std:cerr << "gen method called for a Memory_assignment_store instance!" << std::endl;
    outputFile << "movq ";
    if (dynamic_cast<Label*>(this->s)) {
      outputFile << "$";
    }
    outputFile << this->s->translate() << ", " << this->M->print() << "(" << this->dst->translate() << ")\n";
  }

  void Memory_assignment_load::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a Memory_assignment_load instance!" << std::endl;
    outputFile << "movq " << this->M->print() << "(" << this->x->translate() << "), " << this->dst->translate() << "\n"; 
  }

  void Memory_arithmetic_load::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a Memory_arithmetic_load instance!" << std::endl;
    outputFile << this->instruction->translate() << " " << this->M->print() << "(" << this->x->translate() << "), " << this->dst->translate() << "\n";
  }

  void Memory_arithmetic_store::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a Memory_arithmetic_store instance!" << std::endl;
    outputFile << this->instruction->translate() << " " << this->t->translate() << ", " << this->M->print() << "(" << this->dst->translate() << ")\n";
  }

  void cmp_Instruction::gen(Function *f, std::ofstream &outputFile) {
    // w <- t2 cmp t1
    // also note - I don't 
    if (debug) std::cerr << "gen method called for a cmp_Instruction instance!" << std::endl;
    
    if (dynamic_cast<Number*>(this->t2)) {
      if (dynamic_cast<Number*>(this->t1)) {
        long long t1_val = std::stoll(this->t1->print());
        long long t2_val = std::stoll(this->t2->print());
        int64_t res = 0;
        if (this->method->print() == "<") {res = t2_val < t1_val; }
        else if (this->method->print() == "<=") {res = t2_val <= t1_val; }
        else if (this->method->print() == "=") {res = t2_val == t1_val; }
        else {std::cerr << "Didn't recognize as a valid operator: " << this->method->print() << std::endl; }
        Number ans = Number(res);
        Number *ansptr = &ans;
        outputFile << "movq " << ansptr->translate() << ", " << this->dst->translate() << "\n";
      }
      else {
        // t2 is a number, so we need to flip the positions of t1 and t2 in the cmpq
        outputFile << "cmpq " << this->t2->translate() << ", " << this->t1->translate() << "\n";
        std::string c = this->method->print();
        std::string res = "STOP";
        if (c == "<") {res = "setg";}
        if (c == "<=") {res = "setge";}
        if (c == "=") {res = "sete";}
        else {std::cerr << "Didn't recognize as a valid operator: " << this->method->print() << std::endl; }
        outputFile << res << " %" << convert_reg(this->dst->print()) << "\n";
        outputFile << "movzbq %" << convert_reg(this->dst->print()) << ", " << this->dst->translate() << "\n";
      }
    }
    else {
      outputFile << "cmpq " << t1->translate() << ", " << this->t2->translate() << "\n";
      outputFile << this->method->translate() << " %" << convert_reg(this->dst->print()) << "\n";
      outputFile << "movzbq %" << convert_reg(this->dst->print()) << ", " << this->dst->translate() << "\n";
    }
  }

  void cjump_cmp_Instruction::gen(Function *f, std::ofstream &outputFile) {
    // cjump t2 cmp t1 label
    if (debug) std::cerr << "gen method called for a cjump_cmp_Instruction instance!" << std::endl;

    if (dynamic_cast<Number*>(this->t2)) {
      if (dynamic_cast<Number*>(this->t1)) {
        long long t1_val = std::stoll(this->t1->print());
        long long t2_val = std::stoll(this->t2->print());
        int64_t res = 0;
        if (this->cmp->print() == "<") {res = t2_val < t1_val; }
        else if (this->cmp->print() == "<=") {res = t2_val <= t1_val; }
        else if (this->cmp->print() == "=") {res = t2_val == t1_val; }
        else {std::cerr << "Didn't recognize as a valid operator: " << this->cmp->print() << std::endl; }
        if (res) {
          outputFile << "jmp " << this->label->translate() << "\n";
        }
      }
      else {
        // t2 is a number, so we need to flip the positions of t1 and t2 in the cmpq
        outputFile << "cmpq " << this->t2->translate() << ", " << this->t1->translate() << "\n";
        std::string c = this->cmp->print();
        std::string res = "STOP";
        if (c == "<") {res = "jg";}
        if (c == "<=") {res = "jge";}
        if (c == "=") {res = "je";}
        else {std::cerr << "Didn't recognize as a valid operator: " << this->cmp->print() << std::endl; }
        outputFile << res << " " << this->label->translate() << "\n";
      }
    }
    else {
      std::string res1 = "STOP";
      std::string c1 = this->cmp->print();
      if (c1 == "<") {res1 = "jl";}
      if (c1 == "<=") {res1 = "jle";}
      if (c1 == "=") {res1 = "je";}
      else {std::cerr << "Didn't recognize as a valid operator: " << this->cmp->print() << std::endl; }
      outputFile << "cmpq " << t1->translate() << ", " << this->t2->translate() << "\n";
      outputFile << res1 << " " << this->label->translate() << "\n";
    }
  }

  void AOP_assignment::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for an AOP_assignment instruction class!" << std::endl;

    std::string op = this->method->translate();
    if (debug) std::cerr << "op = " << op << std::endl;
    std::string dest = this->d->translate();
    if (debug) std::cerr << "dest = " << dest << std::endl;
    std::string src = this->s->translate();
    if (debug) std::cerr << "src = " << src << std::endl;

    outputFile << op << " " << src << ", " << dest << "\n";
  }

  void SOP_assignment::gen(Function *f, std::ofstream &outputFile) {
    if (debug) std::cerr << "gen method called for a SOP_assignment instance!" << std::endl;
    outputFile << this->method->translate() << " ";
    if (dynamic_cast< Register* >(this->s)) {
      outputFile << "%" << convert_reg(this->s->print());
    } else {
      outputFile << this->s->translate();
    }
    outputFile << ", " << this->d->translate() << "\n";
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
    outputFile << ".text\n.globl go\ngo:\npushq %rbx\npushq %rbp\npushq %r12\npushq %r13\npushq %r14\npushq %r15\n";
    std::string entry_lab = p.entryPointLabel;
    outputFile << "call " << entry_lab.replace(0, 1, "_") << "\n";
    outputFile << "popq %r15\npopq %r14\npopq %r13\npopq %r12\npopq %rbp\npopq %rbx\nretq\n";

    // main loop
    for (Function *fptr : p.functions) {
      std::string fname = fptr->name;

      std::cout << "Currently generating for function " << fname << std::endl;

      outputFile << fname.replace(0, 1, "_") << ":\n";
      bool c = fptr->locals > 0;
      if (c) {
        outputFile << "subq $" << (fptr->locals * 8) << ", %rsp\n";
      }

      for (Instruction *iptr : fptr->instructions) {
        std::cout << "Currently generating an instruction:" << std::endl;
        iptr->gen(fptr, outputFile);
      }
    }

    if (debug) std::cerr << "Finished code generator!" << std::endl;

    /* 
     * Close the output file.
     */ 
    outputFile.close();
   
    return ;
  }
}
