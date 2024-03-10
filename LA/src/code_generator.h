#pragma once

#include "LA.h"

namespace LA {

    class GenVisitor : public FileVisitor {
        public:
          void visit(Instruction_type_declaration* i, std::ofstream &outputFile) override;
          void visit(Instruction_assignment* i, std::ofstream &outputFile) override;
          void visit(Instruction_length* i, std::ofstream &outputFile) override;
          void visit(Instruction_call_function* i, std::ofstream &outputFile) override;
          void visit(Instruction_call_function_assignment* i, std::ofstream &outputFile) override;
          void visit(Instruction_initialization* i, std::ofstream &outputFile) override;
          void visit(Instruction_operation* i, std::ofstream &outputFile) override;
          void visit(Instruction_store* i, std::ofstream &outputFile) override;
          void visit(Instruction_load* i, std::ofstream &outputFile) override;
          void visit(Instruction_branch_single* i, std::ofstream &outputFile) override;
          void visit(Instruction_branch_double* i, std::ofstream &outputFile) override;
          void visit(Instruction_return* i, std::ofstream &outputFile) override;
          void visit(Instruction_return_value* i, std::ofstream &outputFile) override;
          void visit(Instruction_label* i, std::ofstream &outputFile) override;
          void visit(Instruction_error* i, std::ofstream &outputFile) override;
    };


  void generate_code(Program& p);

}
