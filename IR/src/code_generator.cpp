#include "code_generator.h"

using namespace std;

// use 1 for debug statements, 0 for no printing
// int debug = 1;

namespace IR{
    void newArray::gen(Function *f, std::ofstream &outputFile){

    }
    void arrLength::gen(Function *f,std::ofstream &outputFile){
        auto array = f->variableNameToArray[this->arr->name];
        auto number = dynamic_cast<Number *>(this->dim);
        int offset_val = 8*(std::stoi(number->value)+1);
        outputFile<<"%offset <-"<<offset_val<<'\n\t';
        outputFile<<"%address <-"<<"%m + %offset"<<"\n\t";
        outputFile<<this->dst->name<<" <- load %address"<<"\n\t";
    };


  void generate_code(Program& p) {
    // /* 
    //  * Open the output file.
    //  */ 
    // std::ofstream outputFile;
    // outputFile.open("prog.L3");

    /*
    Gen the entry point label
    */
    // outputFile << "" << entry_lab << "\n";
 
    // for (Function *fptr : p.functions) {

    //   std::string fname = fptr->functionName;

    //   outputFile << "define @" << fname << " (";
    //   for (auto var:fptr->parameters){
    //     outputFile<<var->name<<" ";
    //   }
    //   outputFile<<") {";
 
    //    for (Instruction *iptr : fptr->instructions) {
    //     // iptr->accept(myColorVisitor);
    //       iptr->gen(fptr, outputFile);
    //     }
    //   }
    //   outputFile<<")\n";
    // }
    // outputFile << ")\n";

    // if (debug) std::cerr << "Finished code generation!" << std::endl;
    // outputFile.close();
   
    return ;
  }
}

