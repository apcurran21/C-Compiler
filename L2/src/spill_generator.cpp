#include <string>
#include <iostream>
#include <fstream>

#include <spill_generator.h>
#include "L2.h"

using namespace std;

namespace L2{
void Instruction_ret::gen(Function *f, std::ofstream &outputFile) {
    
  }

  void Instruction_assignment::gen(Function *f, std::ofstream &outputFile) {

  }


  void label_Instruction::gen(Function *f, std::ofstream &outputFile) {

  }

  void goto_label_instruction::gen(Function *f, std::ofstream &outputFile) {

  }

  void Call_tenserr_Instruction::gen(Function *f, std::ofstream &outputFile) {

  }

  void Call_uN_Instruction::gen(Function *f, std::ofstream &outputFile) {

  }

  void Call_print_Instruction::gen(Function *f, std::ofstream &outputFile) {

  }

  void Call_input_Instruction::gen(Function *f, std::ofstream &outputFile) {

  }

  void Call_allocate_Instruction::gen(Function *f, std::ofstream &outputFile) {

  }

  void Call_tuple_Instruction::gen(Function *f, std::ofstream &outputFile) {

  }

  void w_increment_decrement::gen(Function *f, std::ofstream &outputFile) {

  }

  void w_atreg_assignment::gen(Function *f, std::ofstream &outputFile) {

  }

  void Memory_assignment_store::gen(Function *f, std::ofstream &outputFile) {

  }

  void Memory_assignment_load::gen(Function *f, std::ofstream &outputFile) {

  }

  void Memory_arithmetic_load::gen(Function *f, std::ofstream &outputFile) {

  }

  void Memory_arithmetic_store::gen(Function *f, std::ofstream &outputFile) {

  }

  void cmp_Instruction::gen(Function *f, std::ofstream &outputFile) {

  }

  void cjump_cmp_Instruction::gen(Function *f, std::ofstream &outputFile) {

  }

  void AOP_assignment::gen(Function *f, std::ofstream &outputFile) {

  }

  void SOP_assignment::gen(Function *f, std::ofstream &outputFile) {

  }

  void stackarg_assignment::gen(Function *f, std::ofstream &outputFile) {

  }
  
  void generate_spill_code(Program p){
    
  };

}