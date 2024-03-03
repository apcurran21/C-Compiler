#pragma once

#include <IR.h>

namespace IR{

  // void generate_code(Program p, Graph color_graph);
  // void generate_code(Program p, std::map<Function*, Graph*> all_graphs);
    void calculate_array(Function *f, std::ofstream &outputFile, newArray *iptr){

        for (auto num:iptr->args){
            auto number = dynamic_cast<Number *>(num);
            outputFile << number->value << "D <- " << number->value << " >> 1" << "\n\t";
        }
    };

}
