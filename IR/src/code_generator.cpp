#include "code_generator.h"
using namespace std;

// use 1 for debug statements, 0 for no printing
// int debug = 1;

namespace IR{

    void tupleLength::gen(Function *f, std::ofstream &outputFile){
      outputFile<<this->dst->print() << " <- load "<<this->tuple->print()<<"\n\t";
      outputFile << this->dst->print() << " <- "<< this->dst->print()<<" << 1"<<"\n\t";
    }
    void newArray::gen(Function *f, std::ofstream &outputFile){
      
    }
    void labelInstruction::gen(Function *f, std::ofstream &outputFile){
      outputFile<<this->label->print()<<"\n\t";
    }
    void declarationInstruction::gen(Function *f, std::ofstream &outputFile){

    }
    void newTuple::gen(Function *f, std::ofstream &outputFile){
      outputFile<<this->dst->print() <<" <- call allocate ("<< this->size->print()<<",1)"<<"\n\t";
    }
    void arrLength::gen(Function *f,std::ofstream &outputFile){
        auto array = this->arr;
        auto number = dynamic_cast<Number *>(this->dim);
        int offset_val = 8*(number->value+1);
        outputFile<<"%offset <-"<<offset_val<<"\n\t";
        outputFile<<"%address <-"<<"%m + %offset"<<"\n\t";
        outputFile<<this->dst->name<<" <- load %address"<<"\n\t";
    }
    void Assignment::gen(Function *f,std::ofstream &outputFile){
        outputFile <<this->dst->print()<< " <- "<<this->src->print()<<"\n\t";
    }
    
    void storeInstruction::gen(Function *f,std::ofstream &outputFile){
      auto key = this->dst->print();
      auto key_var = f->variableNameToPointer[key];
      if (f->variableToTypeMapping[key_var]->type == TypeEnum::int64){
        auto array = f->variableNameToArray[this->dst->print()];
        int offset_val = 8 + (array->args.size()*8);
        outputFile << "%offset <- " <<offset_val<<"\n\t"; 
        outputFile << "%offset <- %offset * (";
      // stop one before the last one in order to add the last offset value in check slide 63 if confused 
      // this is to add j value in 
        int last_i = 0;
        for (int i = 0; i<array->args.size();i++){
          outputFile<< this->index_args_vec[i]->print() << "*";
          int last_j = 0;
          for (int j = i+1;i<array->args.size();i++){
            last_j = j;
            outputFile << array->args[j] << "*";
          }
          outputFile<<array->args[last_j+1] << ") + (";
          last_i = i;
        }
        outputFile << this->index_args_vec[last_i+1]->print() <<") ) *8"<< "\n\t";
        outputFile << "%addr" << array->count<<"<- "<< array->dst->print()<< "+ %offset"<<"\n\t";
        outputFile << "store addr <- "<<this->dst->print()<<"\n\t";
        array->count++;
      } else {
        auto tuple = f->variableNameToTuple[this->dst->print()];
        outputFile << "%newVar" << tuple->count << "<- "<< tuple->dst<<" + 8"<<"\n\t";
        outputFile << "store %newVar" << tuple->count << " <- " << this->var->print()<<"\n\t";
        tuple->count++;
      } 
      
    }
    void twoSuccBranch::gen(Function *f,std::ofstream &outputFile){
      outputFile <<"br "<<t->print()<<" "<<labelTrue->print()<<"\n\t";
      outputFile <<"br "<< labelFalse->print()<<"\n\t";
    }
    void oneSuccBranch::gen(Function *f, std::ofstream &outputFile){
      outputFile << "br "<< label->print()<<"\n\t";
    }
    void operationInstruction::gen(Function *f, std::ofstream &outputFile){
      outputFile << dst->print() << " <- " << t1->print() << " "<< op->print()<<" "<<t2->print()<<"\n\t";
    }
    void falseReturn::gen(Function *f, std::ofstream &outputFile){
      outputFile << "return" << "\n\t";
    }
    void trueReturn::gen(Function *f, std::ofstream &outputFile){
      outputFile << "return" << returnVal->print()<<"\n\t";
    }
    void VoidCallInstruction::gen(Function *f, std::ofstream &outputFile){
      outputFile << "call "<< callee->print() << " (";
      int last_i = 0;
      for (int i =0;i<args.size()-1;i++){
        outputFile << args[i]->print()<<",";
        last_i = i+1;
      }
      outputFile << args[last_i]->print()<<")"<<"\n\t";
    }
    void NonVoidCallInstruction::gen(Function *f, std::ofstream &outputFile){
      outputFile << dest->print()<<" <- call "<< callee->print() << " (";
      int last_i = 0;
      for (int i =0;i<args.size();i++){
        outputFile << args[i]->print()<<",";
        last_i = i;
      }
      outputFile << args[last_i]->print()<<")"<<"\n\t";
    }
    void loadInstruction::gen(Function *f, std::ofstream &outputFile){
      auto key = this->var->print();
      auto key_var = f->variableNameToPointer[key];
      if (f->variableToTypeMapping[key_var]->type == TypeEnum::int64){
        auto array = f->variableNameToArray[this->var->print()];
        int offset_val = 8 + (array->args.size()*8);
        outputFile << "%offset <- " <<offset_val<<"\n\t";
        outputFile << "%offset <- %offset * (";
        // stop one before the last one in order to add the last offset value in check slide 63 if confused 
        // this is to add j value in 
        int last_i = 0;
        for (int i = 0; i<array->args.size();i++){
          outputFile<< this->index_args_vec[i]->print() << "*";
          int last_j = 0;
          for (int j = i+1;i<array->args.size();i++){
            last_j = j;
            outputFile << array->args[j] << "*";
          }
          outputFile<<array->args[last_j+1] << ") + (";
          last_i = i;
        }
        outputFile << this->index_args_vec[last_i+1]->print() <<") ) *8"<< "\n\t";
        outputFile << "%addr"<< array->count << "<- "<< array->dst->print()<< "+ %offset"<<"\n\t";
        array->count++;
        outputFile << this->dst->print()<< "<- load %addr"<<"\n\t";
      } else {
        // we need to iterate the count somehow 
        auto tuple = f->variableNameToTuple[this->var->print()];
        outputFile << "%newVar" << tuple->count << "<- "<< tuple->dst<<" + 8"<<"\n\t";
        outputFile << this->var->print()<< "<- load "<<"%newVar"<<tuple->count<< "\n\t";
      }  
     }


  void generate_code(Program& p) {
    // /* 
    //  * Open the output file.
    //  */ 
    std::ofstream outputFile;
    outputFile.open("prog.L3");
    for (Function *fptr : p.functions) {
      std::string fname = fptr->functionName->print();
      outputFile << "define " << fname << " (";
      for (auto var:fptr->parameters){
         outputFile<<var->name<<" ";
       }
      outputFile<<") {"<<"\n\t";
        for (Block *block: fptr->executionTraceOrder){
          for (Instruction *iptr : block->instructionBody) {
            auto arr_cast = dynamic_cast<newArray*>(iptr);
            auto tuple_cast = dynamic_cast<newTuple *>(iptr);
            if (arr_cast){
              arr_cast->calculate_array(fptr,outputFile);
              auto it = arr_cast->dst->print();
              fptr->variableNameToArray[it] = arr_cast;
            } else if (tuple_cast){
              iptr->gen(fptr, outputFile);
              fptr->variableNameToTuple[tuple_cast->dst->print()] = tuple_cast;
            } else {
              iptr->gen(fptr, outputFile);
            }
          }
        }
      }
      outputFile<<"}\n";
  }
}


