#include <string>
#include <iostream>
#include <fstream>
#include "L2.h"
#include <code_generator.h>
#include <calculateArray.h>
using namespace std;

// use 1 for debug statements, 0 for no printing
// int debug = 1;

namespace IR{
    void newArray::gen(Function *f, std::ofstream &outputFile){

    }
    void arrLength::gen(Function *f,std::ofstream &outputFile){
        auto array = f->variableNameToArray[this->arr->name];
        auto number = dynamic_cast<Number *>(this->dim);
        int offset_val = 8*(number->value+1)
        outputFile<<"%offset <-"<<offset_val<<'\n\t';
        outputFile<<"%address <-"<<"%m + %offset"<<"\n\t";
        outputFile<<this->dst->name<<" <- load %address"<<"\n\t";
    };


  void generate_code(Program& p) {
    /* 
     * Open the output file.
     */ 
    std::ofstream outputFile;
    outputFile.open("prog.L3");

    /*
    Gen the entry point label
    */
    outputFile << "" << entry_lab << "\n";
 
    for (Function *fptr : p.functions) {

      std::string fname = fptr->functionName;

      outputFile << "define @" << fname << " (";
      for (auto var:fptr->parameters){
        outputFile<<var->name<<" ";
      }
      outputFile<<") {";
 
       for (Instruction *iptr : fptr->instructions) {
          auto array_instruction = dynamic_cast<newArray*>(iptr)
          if (array_instruction){
            array_instruction->calculate_array(f,outputFile);
          } else {
            iptr->gen(fptr, outputFile);
          }    
        }
      }
      outputFile<<")\n";
    }
    outputFile << ")\n";

    if (debug) std::cerr << "Finished code generation!" << std::endl;
    outputFile.close();
   
    return ;
  }

