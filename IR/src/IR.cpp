#pragma once 

#include <set>
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <tuple>
#include "IR.h"

namespace IR { 
    void newArray::calculate_array(Function *f, std::ofstream &outputFile){
        for (auto num:this->args){
            auto number = dynamic_cast<Number *>(num);
            outputFile << number->value << "D <- " << number->value << " >> 1" << "\n\t";
        }
        outputFile<<"%v0 <- ";
        auto it = args.begin(); // Iterator to the start of the vector
        auto end = args.end() - 1;
        while (it != end) {
            auto number = dynamic_cast<Number*>(*it);
            outputFile << number->value << "D * ";
            ++it;
        }
        auto number = dynamic_cast<Number*>(*it);
        outputFile << number->value <<"D" << "\n\t";
        outputFile << "%v0 <- %v0 +" << this->args.size();
        outputFile<< "%v0 <- %v0 << 1";
        outputFile << "%v0 <- %v0 + 1";
        outputFile << "%a <- call allocate(%v0,1)";
        int count = 2;
        for (auto num:this->args){
            auto number = dynamic_cast<Number *>(num);
            outputFile<<"%v" << count<<" <- %a + " << (count-1)* 8<<"\n\t";
            outputFile<<"store %v" << count<<" <- "<<"%"<<number->value<<"\n\t";
        }
    }
}
