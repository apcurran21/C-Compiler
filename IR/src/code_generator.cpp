#include "code_generator.h"
using namespace std;

// use 1 for debug statements, 0 for no printing
// int debug = 1;
int global_counter = 0;
namespace IR{

    void tupleLength::gen(Function *f, std::ofstream &outputFile){
      outputFile<<this->dst->print() << " <- load "<<this->tuple->print()<<"\n\t";
      outputFile << this->dst->print() << " <- "<< this->dst->print()<<" << 1"<<"\n\t";
      outputFile << this->dst->print() << " <- "<< this->dst->print() <<" +1"<<"\n\t";
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
        outputFile<<"%offsetPERSONAL <-"<<offset_val<<"\n\t";
        outputFile<<"%address <- "<< array->print() <<" + %offsetPERSONAL"<<"\n\t";
        outputFile<<this->dst->name<<" <- load %address"<<"\n\t";
    }
    void Assignment::gen(Function *f,std::ofstream &outputFile){
        outputFile <<this->dst->print()<< " <- "<<this->src->print()<<"\n\t";
    }

    void loadInstruction::gen(Function *f, std::ofstream &outputFile){
      auto is_integer = [](const std::string& str) -> bool {
        try {
            size_t pos;
            int num = std::stoi(str, &pos);
            return pos == str.length();  // Ensure entire string is consumed
        } catch (std::invalid_argument& e) {
            // Not an integer
            return false;
        } catch (std::out_of_range& e) {
            // Not an integer or out of range
            return false;
        }
      };
      if (index_args_vec.size() > 0 && is_integer(index_args_vec[0]->print())) {
        if (std::stoi(index_args_vec[0]->print())<0){
          outputFile<< "%newVar" <<global_counter << " <- "<< index_args_vec[0]->print()<< " * 8"<<"\n\t";
          global_counter++;
          outputFile<< "%newVar" <<global_counter << " <- "<< "%newVar"<<global_counter - 1<< " + 8"<<"\n\t";
          global_counter++;
          outputFile<<"%newVar"<<global_counter<<" <- "<<var->print()<< " + %newVar"<< global_counter - 1<<"\n\t"; 
          outputFile<<dst->print()<< " <- load %newVar"<<global_counter<<"\n\t";
          global_counter++;
          return;
        }
      }
      auto key = this->var->print();
      auto key_var = f->variableNameToPointer[key];
      // if (f->variableToTypeMapping[key_var]->type == TypeEnum::int64){
      if (f->variableNameToType[key]->type == TypeEnum::int64) {
        int iter = 0;
        std::vector<std::string> toMultiply;
        for (int i =0;i<index_args_vec.size();i++){
            outputFile<<"%newVar"<<iter<<" <- " << key<<" +"<<(i+1)*8<<"\n\t"; //gets to the first param
            iter++;
            outputFile<<"%newVar"<<iter<<" <- load %newVar"<<iter-1<<"\n\t"; // this gets first val
            iter++;
            outputFile<<"%newVar"<<iter << " <- %newVar"<<iter-1<<" >> 1"<<"\n\t";
            toMultiply.push_back("%newVar"+std::to_string(iter));
            iter++;
        }

        outputFile << "%offsetPERSONAL <- "<<0<<"\n\t";
        for (int i =0;i<toMultiply.size();i++){
          outputFile<< "%offset_temp <- "<<index_args_vec[i]->print()<<"\n\t";
          for (int j = i+1;j<toMultiply.size();j++){
            outputFile << "%offset_temp <- %offset_temp * "<<toMultiply[j]<<"\n\t";
          }
          outputFile<<"%offsetPERSONAL <- %offsetPERSONAL + %offset_temp"<<"\n\t";
        }
        outputFile << "%tempOFFSET <- %offsetPERSONAL * 8"<<"\n\t";
        outputFile<<"%tempOFFSET <- %tempOFFSET + "<<8 * (1+toMultiply.size())<< "\n\t";
        outputFile << "%addr"<< "<- "<< key << " + %tempOFFSET"<<"\n\t";
        outputFile << this->dst->print()<< "<- load %addr"<<"\n\t";
      } else {
        // we need to iterate the count somehow 
        auto tuple = f->variableNameToTuple[this->var->print()];
        if (index_args_vec.size() > 0 && is_integer(index_args_vec[0]->print()) && index_args_vec[0]) {
          outputFile << "%newVar" << global_counter << "<- "<< var->print()<<" + "<<8 * (std::stoi(index_args_vec[0]->print())+1)<<"\n\t";
        } else {
          outputFile << "%addTemp" <<global_counter<< " <- "<<index_args_vec[0]->print() << " * 8"<<"\n\t";
          global_counter++;
          outputFile << "%addTemp" << global_counter << " <- "<<"%addTemp"<<global_counter-1<< " + 8"<<"\n\t";
          outputFile << "%newVar" << global_counter << "<- "<< var->print()<<" + %addTemp"<< global_counter <<"\n\t";
        }        
        outputFile << this->dst->print()<< "<- load "<<"%newVar"<<global_counter<< "\n\t";
        global_counter++;
      }  
     }
    void storeInstruction::gen(Function *f,std::ofstream &outputFile){
      auto is_integer = [](const std::string& str) -> bool {
        try {
            size_t pos;
            int num = std::stoi(str, &pos);
            return pos == str.length();  // Ensure entire string is consumed
        } catch (std::invalid_argument& e) {
            // Not an integer
            return false;
        } catch (std::out_of_range& e) {
            // Not an integer or out of range
            return false;
        }
      };
      auto key = this->dst->print();
      auto key_var = f->variableNameToPointer[key];
      // if (f->variableToTypeMapping[key_var]->type == TypeEnum::int64){
      if (f->variableNameToType[key]->type == TypeEnum::int64) {
        int iter = 0;
        std::vector<std::string> toMultiply;
        for (int i =0;i<index_args_vec.size();i++){
            outputFile<<"%newVar"<<iter<<" <- " << key<<" +"<<(i+1)*8<<"\n\t"; //gets to the first param
            iter++;
            outputFile<<"%newVar"<<iter<<" <- load %newVar"<<iter-1<<"\n\t"; // this gets first val
            iter++;
            outputFile<<"%newVar"<<iter << " <- %newVar"<<iter-1<<" >> 1"<<"\n\t";
            toMultiply.push_back("%newVar"+std::to_string(iter));
            iter++;
        }

        outputFile << "%offsetPERSONAL <- "<<0<<"\n\t";
        for (int i =0;i<toMultiply.size();i++){
          outputFile<< "%offset_temp <- "<<index_args_vec[i]->print()<<"\n\t";
          for (int j = i+1;j<toMultiply.size();j++){
            outputFile << "%offset_temp <- %offset_temp * "<<toMultiply[j]<<"\n\t";
          }
          outputFile<<"%offsetPERSONAL <- %offsetPERSONAL + %offset_temp"<<"\n\t";
        }
        
        outputFile << "%tempOFFSET <- %offsetPERSONAL * 8"<<"\n\t";
        outputFile<<"%tempOFFSET <- %tempOFFSET + "<<8 * (1+toMultiply.size())<< "\n\t";
        outputFile << "%addr"<< "<- "<< dst->print() << " + %tempOFFSET"<<"\n\t";
        outputFile << "store %addr"<<"<- "<<var->print()<<"\n\t";
      } else {
        auto tuple = f->variableNameToTuple[this->dst->print()];
        if (index_args_vec.size() > 0 && is_integer(index_args_vec[0]->print())) {
          outputFile << "%newVar" << global_counter << "<- "<< dst->print()<<" + "<<8 * (std::stoi(index_args_vec[0]->print())+1)<<"\n\t";
        } else {
          outputFile << "%addTemp" <<global_counter<< " <- "<<index_args_vec[0]->print() << " * 8"<<"\n\t";
          global_counter++;
          outputFile << "%addTemp" << global_counter << " <- "<<"%addTemp"<<global_counter-1<< " + 8"<<"\n\t";
          outputFile << "%newVar" << global_counter << "<- "<< dst->print()<<" + %addTemp"<< global_counter <<"\n\t";
        }
        outputFile << "store %newVar" << global_counter << " <- " << this->var->print()<<"\n\t";
        global_counter++;
      } 
      
    }
    void Error::gen(Function *f, std::ofstream &outputFile) {
      if (dest){
          outputFile<<dest->print()<< " <- ";
      }
      outputFile<< "call " << error_type<<" (";
      int last_i = 0;
      if (args.size()>1){
        for (int i =0;i<args.size()-1;i++){
        outputFile << args[i]->print()<<",";
        last_i = i+1;
        }
      }
        if (args.size()>0) {
          outputFile << args[last_i]->print()<<")"<<"\n\t";
        } else {
          outputFile << ")"<<"\n\t";
        }
    }
    void twoSuccBranch::gen(Function *f,std::ofstream &outputFile){
      outputFile <<"br "<<t->print()<<" "<<labelTrue->print()<<"\n\t";
      outputFile <<"br "<<labelFalse->print()<<"\n\t";
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
      outputFile << "return " << returnVal->print()<<"\n\t";
    }
    void VoidCallInstruction::gen(Function *f, std::ofstream &outputFile){
      outputFile << "call "<< callee->print() << " (";
      int last_i = 0;
      if (args.size()>1){
        for (int i =0;i<args.size()-1;i++){
        outputFile << args[i]->print()<<",";
        last_i = i+1;
        }
      }
        if (args.size()>0) {
          outputFile << args[last_i]->print()<<")"<<"\n\t";
        } else {
          outputFile << ")"<<"\n\t";
        }
    }
    void NonVoidCallInstruction::gen(Function *f, std::ofstream &outputFile){
      outputFile << dst->print()<<" <- call "<< callee->print() << " (";
      int last_i = 0;
      if (args.size()>1){
        for (int i =0;i<args.size()-1;i++){
        outputFile << args[i]->print()<<",";
        last_i = i+1;
        }
      }
        if (args.size()>0) {
          outputFile << args[last_i]->print()<<")"<<"\n\t";
        } else {
          outputFile << ")"<<"\n\t";
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
      if (fptr->parameters.size()!=0){
          for (int i = 0;i<fptr->parameters.size()-1;i++){
          outputFile<<fptr->parameters[i]->print()<<", ";
        }
        outputFile<<fptr->parameters[fptr->parameters.size()-1]->print();
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
        outputFile<<"}\n";

      }
  }
}


