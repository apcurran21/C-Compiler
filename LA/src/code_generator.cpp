#include "code_generator.h"
using namespace std;

// use 1 for debug statements, 0 for no printing
// int debug = 1;

namespace LA {

  void GenVisitor::visit(Instruction_type_declaration* i, std::ofstream &outputFile) {
    outputFile << i->type->print() << " " << i->name->print() << "\n";
  }

  void GenVisitor::visit(Instruction_assignment* i, std::ofstream &outputFile) {
    outputFile << i->dest->print() << " <- " << i->src->print() << "\n";
  }

  void GenVisitor::visit(Instruction_length* i, std::ofstream &outputFile) {
    outputFile << i->dest->print() << " <- length " << i->src->print();
    if (i->t) outputFile << " " << i->t->print();
    outputFile << "\n";
  }

  void GenVisitor::visit(Instruction_call_function* i, std::ofstream &outputFile) {
    outputFile << "call " << i->callee->print() << " (";
    for (int j = 0; j < i->args.size(); j++) {
      outputFile << " " << i->args[j]->print();
      if (j < (i->args.size() - 1)) outputFile << ",";
    }
    outputFile << " )\n";
  }

  void GenVisitor::visit(Instruction_call_function_assignment* i, std::ofstream &outputFile) {
    outputFile << i->dest->print() << " <- call " << i->callee->print() << " (";
    for (int j = 0; j < i->args.size(); j++) {
      outputFile << " " << i->args[j]->print();
      if (j < (i->args.size() - 1)) outputFile << ",";
    }
    outputFile << " )\n";
  }

  void GenVisitor::visit(Instruction_initialization* i, std::ofstream &outputFile) {
    outputFile << i->dest->print() << " <- new ";
    switch (i->type) {
      case CollectionEnum::Array:
        outputFile << "Array";
        break;
      case CollectionEnum::Tuple:
        outputFile << "Tuple";
        break;
    }
    outputFile << "(";
    for (int j = 0; j < i->args.size(); j++) {
      outputFile << " " << i->args[j]->print();
      if (j < (i->args.size() - 1)) outputFile << ",";
    }
    outputFile << " )\n";
  }

  void GenVisitor::visit(Instruction_operation* i, std::ofstream &outputFile) {
    outputFile << i->name->print() << " <- " << i->t1->print() << " " << i->op->print() << " " << i->t2->print() << "\n";
  }

  void GenVisitor::visit(Instruction_store* i, std::ofstream &outputFile) {
    outputFile << i->dest->print();
    for (auto arg : i->args) {
      outputFile << "[" << arg->print() << "]";
    }
    outputFile << " <- " << i->src->print() << "\n";
  }

  void GenVisitor::visit(Instruction_load* i, std::ofstream &outputFile) {
    outputFile << i->dest->print() << " <- " << i->src->print();
    for (auto arg : i->args) {
      outputFile << "[" << arg->print() << "]";
    }
    outputFile << "\n";
  }

  void GenVisitor::visit(Instruction_branch_single* i, std::ofstream &outputFile) {
    outputFile << "br " << i->label1->print() << "\n";
  }

  void GenVisitor::visit(Instruction_branch_double* i, std::ofstream &outputFile) {
    outputFile << "br " << i->t->print() << " " << i->label1->print() << " " << i->label2->print() << "\n";
  }

  void GenVisitor::visit(Instruction_return* i, std::ofstream &outputFile) {
    outputFile << "return\n";
  }

  void GenVisitor::visit(Instruction_return_value* i, std::ofstream &outputFile) {
    outputFile << "return " << i->t->print() <<"\n";
  }

  void GenVisitor::visit(Instruction_label* i, std::ofstream &outputFile) {
    outputFile << i->label->print() <<"\n";
  }

  /*
  IR code generation.
  */
  void generate_code(Program& p) {
    std::ofstream outputFile;
    outputFile.open("prog.IR");
    auto gen_visitor = new GenVisitor();


    for (auto f: p.getFunctions()) {
      outputFile << "define " << f->returnType->print() << " " << f->functionName->print() << " (";
      
      for (int j = 0; j < f->parameters.size(); j++) {
        outputFile << " " << f->parameters[j]->print();
        if (j < (f->parameters.size() - 1)) outputFile << ",";
      }
      
      outputFile << " ) {\n";

      for (auto i: f->instructions) {
        i->accept(gen_visitor, outputFile);
      }

      outputFile << "}\n\n";
    }
  }
}


