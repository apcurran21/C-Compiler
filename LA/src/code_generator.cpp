#include "code_generator.h"
using namespace std;

// use 1 for debug statements, 0 for no printing
// int debug = 1;

namespace LA {

  void GenVisitor::visit(Instruction_type_declaration* i, std::ofstream &outputFile) {
    outputFile << i->type->gen() << " " << i->name->gen() << "\n";
  }

  void GenVisitor::visit(Instruction_assignment* i, std::ofstream &outputFile) {
    outputFile << i->dest->gen() << " <- " << i->src->gen() << "\n";
  }

  void GenVisitor::visit(Instruction_length* i, std::ofstream &outputFile) {
    outputFile << i->dest->gen() << " <- length " << i->src->gen();
    if (i->t) outputFile << " " << i->t->gen();
    outputFile << "\n";
  }

  void GenVisitor::visit(Instruction_call_function* i, std::ofstream &outputFile) {
    outputFile << "call " << i->callee->gen() << " (";
    for (int j = 0; j < i->args.size(); j++) {
      outputFile << " " << i->args[j]->gen();
      if (j < (i->args.size() - 1)) outputFile << ",";
    }
    outputFile << " )\n";
  }

  void GenVisitor::visit(Instruction_call_function_assignment* i, std::ofstream &outputFile) {
    outputFile << i->dest->gen() << " <- call " << i->callee->gen() << " (";
    for (int j = 0; j < i->args.size(); j++) {
      outputFile << " " << i->args[j]->gen();
      if (j < (i->args.size() - 1)) outputFile << ",";
    }
    outputFile << " )\n";
  }

  void GenVisitor::visit(Instruction_initialization* i, std::ofstream &outputFile) {
    outputFile << i->dest->gen() << " <- new ";
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
      outputFile << " " << i->args[j]->gen();
      if (j < (i->args.size() - 1)) outputFile << ",";
    }
    outputFile << " )\n";
  }

  void GenVisitor::visit(Instruction_operation* i, std::ofstream &outputFile) {
    outputFile << i->name->gen() << " <- " << i->t1->gen() << " " << i->op->gen() << " " << i->t2->gen() << "\n";
  }

  void GenVisitor::visit(Instruction_store* i, std::ofstream &outputFile) {
    outputFile << i->dest->gen();
    for (auto arg : i->args) {
      outputFile << "[" << arg->gen() << "]";
    }
    outputFile << " <- " << i->src->gen() << "\n";
  }

  void GenVisitor::visit(Instruction_load* i, std::ofstream &outputFile) {
    outputFile << i->dest->gen() << " <- " << i->src->gen();
    for (auto arg : i->args) {
      outputFile << "[" << arg->gen() << "]";
    }
    outputFile << "\n";
  }

  void GenVisitor::visit(Instruction_branch_single* i, std::ofstream &outputFile) {
    outputFile << "br " << i->label1->gen() << "\n";
  }

  void GenVisitor::visit(Instruction_branch_double* i, std::ofstream &outputFile) {
    outputFile << "br " << i->t->gen() << " " << i->label1->gen() << " " << i->label2->gen() << "\n";
  }

  void GenVisitor::visit(Instruction_return* i, std::ofstream &outputFile) {
    outputFile << "return\n";
  }

  void GenVisitor::visit(Instruction_return_value* i, std::ofstream &outputFile) {
    outputFile << "return " << i->t->gen() <<"\n";
  }

  void GenVisitor::visit(Instruction_label* i, std::ofstream &outputFile) {
    outputFile << i->label->gen() <<"\n";
  }

  void GenVisitor::visit(Instruction_error* i, std::ofstream &outputFile) {
    outputFile << "call " << i->type << " (";
    for (int j = 0; j < i->args.size(); j++) {
      outputFile << " " << i->args[j]->gen();
      if (j < (i->args.size() - 1)) outputFile << ",";
    }
    outputFile << ")\n";
  }

  /*
  IR code generation.
  */
  void generate_code(Program& p) {
    std::ofstream outputFile;
    outputFile.open("prog.IR");
    auto gen_visitor = new GenVisitor();


    for (auto f: p.getFunctions()) {
      outputFile << "define " << f->returnType->gen() << " " << f->functionName->gen() << " (";
      
      for (int j = 0; j < f->parameters.size(); j++) {
        outputFile << " " << f->parameters[j]->gen();
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


