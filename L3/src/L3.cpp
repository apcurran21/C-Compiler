#include "L3.h"

namespace L3 {

    /*
    L3 Program Data Types.
    */
    
    /*
    Number
    */
    Number::Number(int n) : value(n) {}

    std::string Number::print() const {
        return std::to_string(value);
    }

    /*
    Name
    */
    Name::Name(std::string val) : value(val) {}

    std::string Name::print() const {
        return value;
    }

    /*
    Symbol
    */
    Symbol::Symbol(std::string val) : value(val) {};

    std::string Symbol::print() const {
        return value;
    }


    /*
    Instructions
    */
    Instruction_assignment::Instruction_assignment(Item *dest, Item *src) :
        dest { dest },
        src { src }
    {
    }

    void Instruction_assignment::accept(Visitor *visitor) {
        visitor->visit(this);
    }


    Instruction_load::Instruction_load(Item *var1, Item *var2) :
        Instruction_assignment { var1, var2 }
    {
    }

    void Instruction_load::accept(Visitor *visitor) {
        visitor->visit(this);
    }


    void Instruction_store::Instruction_store(Item *var1, Item *var2) :
        Instruction_assignment { var1, var2 }
    {
    }

    void Instruction_store::accept(Visitor *visitor) {
        visitor->visit(this);
    }


    Instruction_action::Instruction_action(Item *var, Item *t1, Item *action, Item *t2) :
        var { var },
        t1 { t1 },
        action { action },
        t2 { t2 }
    {
    }

    void Instruction_action::accept(Visitor *visitor) {
        /*
        Dummmy implementation, Instruction_action is currently abstract.
        */
        // visitor->visit(this);
    }


    Instruction_operation::Instruction_operation (Item *var, Item *t1, Item *action, Item *t2) :
        Instruction_action { Item *var, Item *t1, Item *action, Item *t2 }
    {
    }

    void Instruction_operation::accept(Visitor *visitor) {
        visitor->visit(this);
    }


    Instruction_comparison::Instruction_comparison (Item *var, Item *t1, Item *action, Item *t2) :
        Instruction_action { Item *var, Item *t1, Item *action, Item *t2 }
    {
    }

    void Instruction_comparison::accept(Visitor *visitor) {
        visitor->visit(this);
    }


    Instruction_return::Instruction_return () 
    {
    }

    void Instruction_return::accept(Visitor *visitor) {
        visitor->visit(this);
    }


    Instruction_return_value::Instruction_return_value (Item* t) :
        t { t }
    {
    }

    Instruction_return_value::accept(Visitor *visitor) {
        visitor->visit(this);
    }


    Instruction_label::Instruction_label (Item *label) :
        label { label }
    {
    }

    Instruction_label::accept(Visitor *visitor) {
        visitor->visit(this);
    }


    Instruction_branch_label::Instruction_break_label (Item *label) :
        label { label }
    {
    }

    Instruction_branch_label::accept(Visitor *visitor) {
        visitor->visit(this);
    }


    Instruction_branch_label_conditional (Item *t, Item *label) :
        t { t },
        Instruction_branch_label { label }
    {
    }

    Instruction_branch_label_conditional::accept(Visitor *visitor) {
        visitor->visit(this);
    }


    Instruction_call_function::Instruction_call_function (Item *callee, std::vector<Item*>& args = {}) :
        callee { callee },
        args { args }
    {
    }

    Instruction_call_function::accept(Visitor *visitor) {
        visitor->visit(this);
    }


    Instruction_call_function_assignment::Instruction_call_function_assignment (Item *var, Item *callee, std::vector<Item*>& args) :
        var { var },
        Instruction_call_function { callee, args }
    {
    }

    Instruction_call_function_assignment::accept(Visitor *visitor) {
        visitor->visit(this);
    }


    /*
    Function / Program
    */
    void Function::print() const {
        /*
        Todo write a print visitor for the instructions.
        */
    }

    void Function::setFunctionName(std::string new_name) {
        name = new_name;
    }

    void Function::addParameter(Item *new_parameter) {
        parameters.push_back(new_parameter);
    }

    void Function::addInstruction(Item *new_instruction) {
        instructions.push_back(new_instruction);
    }

    
    /*
    Print the contents of the program to cerr.
    */
    void Program::print() const {
        for (auto function& : functions) {
            function.print();
            std::cerr << "\n\n";
        }
    }

    void Program::addFunction(Function *new_function) {
        functions.push_back(new_function);
    }

}