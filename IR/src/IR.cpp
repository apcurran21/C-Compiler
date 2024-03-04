#include <set>
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <tuple>
#include "IR.h"


namespace IR { 


    void newArray::calculate_array(Function *f, std::ofstream &outputFile){
        for (auto num:this->args){
            auto number = dynamic_cast<Number *>(num);
            this->variableDimensions.push_back(number->value+"D");
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
        /*
        These should be instructions to access vals
        int count = 2;
        for (auto num:this->args){
            auto number = dynamic_cast<Number *>(num);
            outputFile<<"%v" << count <<" <- "<< "%a + " << (count-1)* 8 << "\n\t";
            outputFile<<"store %v" << count<<" <- "<< "%" << number->value << "\n\t";
        }
        */
        
    }

/*
Token/Item constructors
*/
Type::Type(TypeEnum type) :
    type(type)
{
}
std::string Type::print() const {
    std::string res;
    switch (type) {
        case TypeEnum::int64:
            res = "int64";
            for (int i = 0; i < dims; i++) {
                res += "[]";
            }
            break;
        case TypeEnum::tuple:
            res = "tuple";
            break;
        case TypeEnum::code:
            res = "code";
            break;
        case TypeEnum::voidt:
            res = "void";
            break;
        case TypeEnum::bracks:
            res = "[]";
            break;
    }
    return res;
}

Label::Label(std::string name) :
    name(name)
{
}
std::string Label::print() const  {
    return name;
}

Number::Number(int64_t value) :
    value(value)
{
}
std::string Number::print() const  {
    return std::to_string(value);
}

Variable::Variable(std::string name) :
    name(name)
{
}
std::string Variable::print() const  {
    return name;
}

Operator::Operator(OperatorEnum id) : 
    id(id)
{
}
std::string Operator::print() const  {
    std::string res;
    switch (value) {
        case OperationEnum::plus:
            res = "+";
            break;
        case OperationEnum::minus:
            res = "-";
            break;
        case OperationEnum::times:
            res = "*";
            break;
        case OperationEnum::amp:
            res = "&";
            break;
        case OperationEnum::left:
            res = "<<";
            break;
        case OperationEnum::right:
            res = ">>";
            break;
        case OperationEnum::lt:
            res = "<";
            break;
        case OperationEnum::leq:
            res = "<=";
            break;
        case OperationEnum::eq:
            res = "=";
            break;
        case OperationEnum::geq:
            res = ">=";
            break;
        case OperationEnum::gt:
            res = ">";
            break;
    }
    return res;
}

Block::Block(std::string label) :
    label(label)
{
}


/*
Instruction constructors.
*/

/*
Void
*/
declarationInstruction::declarationInstruction(Type *type, Variable *var) :
    type(type),
    var(var)
{
}

labelInstruction::labelInstruction(Label *label) :
    label(label)
{
}

VoidCallInstruction::VoidCallInstruction(Item *callee) :
    callee(callee),
{
}

/*
Non-Void
*/
nonVoidInstruction::nonVoidInstruction(Variable *dst) :
    dst(dst)
{
}

Assignment::Assignment(Variable *dst, Item *src) :
    nonVoidInstruction(dst),
    src(src)
{
}

operationInstruction::operationInstruction(Variable *dst, Item *t1, Operator *op, Item *t2) :
    nonVoidInstruction(dst),
    t1(t1),
    op(op),
    t2(t2)
{
}

loadInstruction::loadInstruction(Variable *dst Item *var) :
    nonVoidInstruction(dst),
    var(var)
{
}

storeInstruction::storeInstruction(Variable *dst, Item *var) :
    nonVoidInstruction(dst),
    var(var)
{
}

arrLength::arrLength(Variable *dst, Variable *arr, Item *dim) :
    nonVoidInstruction(dst),
    arr(arr),
    dim(dim)
{
}

tupleLength::tupleLength(Variable *dst, Variable *tuple) :
    nonVoidInstruction(dst),
    tuple(tuple)
{
}

NonVoidCallInstruction::NonVoidCallInstruction(Variable *dest, Item *callee) :
    nonVoidInstruction(dest),
    callee(callee),
{
}

newArray::newArray(Variable *dest, int64_t counter) :
    nonVoidInstruction(dest),
    count(counter)
{
}

newTuple::newTuple(Variable *dest, Item *size) :
    nonVoidInstruction(dest),
    size(size)
{
}





}
