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
Label::Label(std::string name) :
    name(name)
{
}

Number::Number(int64_t value) :
    value(value)
{
}

Variable::Variable(std::string name) :
    name(name)
{
}

Operator::Operator(OperatorEnum id) : 
    id(id)
{
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
declarationInstruction::declarationInstruction()

labelInstruction::labelInstruction(Label *label) :
    label(label)
{
}

VoidCallInstruction::VoidCallInstruction(Item *callee, std::vector<Item *> args) :
    callee(callee),
    args(args)
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

NonVoidCallInstruction::NonVoidCallInstruction(Variable *dest, Item *callee, std::vector<Item *> args) :
    nonVoidInstruction(dest),
    callee(callee),
    args(args)
{
}

newArray::newArray(Variable *dest, std::vector<Item *> args) :
    nonVoidInstruction(dest),
    args(args)
{
}

newTuple::newTuple(Variable *dest, Item *size) :
    nonVoidInstruction(dest),
    size(size)
{
}








}
