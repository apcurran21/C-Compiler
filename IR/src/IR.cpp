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
    
/*
Token/Item constructors
*/
Type::Type(TypeEnum type) :
    type(type)
{
}
std::string Type::print() {
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
std::string Label::print() {
    return name;
}

Number::Number(int64_t value) :
    value(value)
{
}
std::string Number::print() {
    return std::to_string(value);
}

Variable::Variable(std::string name) :
    name(name)
{
}
std::string Variable::print() {
    return name;
}

Operator::Operator(OperatorEnum id) : 
    id(id)
{
}
std::string Operator::print() {
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

loadInstruction::loadInstruction(Variable *dst, Item *var) :
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


/*
Terminator constructors.
*/
oneSuccBranch::oneSuccBranch(Label *label) :
    label(label)
{
}

twoSuccBranch::twoSuccBranch(Item *t, Label *label1, Label *label2) :
    t(t),
    label1(label1),
    label2(label2)
{
}


trueReturn::trueReturn(Item *returnVal) :
    returnVal(returnVal)
{
}

falseReturn::falseReturn() : {}








}
