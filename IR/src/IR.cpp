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
    Utility dictionaries.
    */
    std::map<std::string, TypeEnum> stringToTypeEnum = {
        {"int64", TypeEnum::int64},
        {"tuple", TypeEnum::tuple},
        {"code", TypeEnum::code},
        {"void", TypeEnum::voidt},
        {"[]", TypeEnum::bracks}
    };
    std::map<std::string, OperatorEnum> stringToOperatorEnum = {
        {">", OperatorEnum::gt},
        {">=", OperatorEnum::geq},
        {"=", OperatorEnum::eq},
        {"<=", OperatorEnum::leq},
        {"*", OperatorEnum::times},
        {"-", OperatorEnum::minus},
        {"+", OperatorEnum::plus},
        {"<", OperatorEnum::lt},
        {"<<", OperatorEnum::left},
        {">>", OperatorEnum::right},
        {"&", OperatorEnum::amp}
    };

    void Block::appendInstruction(Instruction *i){
        this->instructionBody.push_back(i);
    }
    void newArray::calculate_array(Function *f, std::ofstream &outputFile){
        for (auto num:this->args){
            auto number = dynamic_cast<Number *>(num);
            this->variableDimensions.push_back(number->value+"D");
            outputFile <<"%"<< "D"<< number->value << "<- " << number->value << " >> 1" << "\n\t";
        }
        auto number = dynamic_cast<Number*>(args[0]);
        outputFile<<"%v0 <- "<<"%D"<<number->value<<"\n\t";
        for (int i =1;i < args.size();i++){
            auto number = dynamic_cast<Number*>(args[i]);
            outputFile<<"%v0 <- %v0 * %D" << number->value<<"\n\t";
        }
        outputFile << "%v0 <- %v0 +" << this->args.size()<<"\n\t";
        outputFile<< "%v0 <- %v0 << 1"<<"\n\t";
        outputFile << "%v0 <- %v0 + 1"<<"\n\t";
        outputFile << this->dst->name<<" <- call allocate(%v0,1)"<<"\n\t";
        int count = 2;
        for (auto num:this->args){
            auto number = dynamic_cast<Number *>(num);
            outputFile<<"%v" << count <<" <- "<< this->dst->name <<" + " << (count-1)* 8 << "\n\t";
            outputFile<<"store %v" << count<<" <- "<< number->value << "\n\t";
            count++;
        }
        
        
    }

    /*
    Token/Item constructors
    */
    Type::Type(TypeEnum type) :
        type(type),
        dims(0)
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

    userFuncName::userFuncName(const std::string& name) :
        name(name)
    {
    }
    std::string userFuncName::print() const {
        return name;
    }

    Operator::Operator(OperatorEnum id) : 
        id(id)
    {
    }
    std::string Operator::print() const  {
        std::string res;
        switch (id) {
            case OperatorEnum::plus:
                res = "+";
                break;
            case OperatorEnum::minus:
                res = "-";
                break;
            case OperatorEnum::times:
                res = "*";
                break;
            case OperatorEnum::amp:
                res = "&";
                break;
            case OperatorEnum::left:
                res = "<<";
                break;
            case OperatorEnum::right:
                res = ">>";
                break;
            case OperatorEnum::lt:
                res = "<";
                break;
            case OperatorEnum::leq:
                res = "<=";
                break;
            case OperatorEnum::eq:
                res = "=";
                break;
            case OperatorEnum::geq:
                res = ">=";
                break;
            case OperatorEnum::gt:
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
        callee(callee)
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

    NonVoidCallInstruction::NonVoidCallInstruction(Variable *dest, Item *callee) :
        nonVoidInstruction(dest),
        callee(callee)
    {
    }

    newArray::newArray(Variable *dst, int64_t counter) :
        nonVoidInstruction(dst),
        count(counter)
    {
    }

    newTuple::newTuple(Variable *dst, Item *size,int64_t counter) :
        nonVoidInstruction(dst),
        size(size),
        count(counter)
    {
    }

    /*
    Terminator instructions.
    */
    oneSuccBranch::oneSuccBranch(Label *label) :
        label(label)
    {
    }

    twoSuccBranch::twoSuccBranch(Item *t, Label *labelTrue, Label *labelFalse) :
        t(t),
        labelTrue(labelTrue),
        labelFalse(labelFalse)
    {
    }

    falseReturn::falseReturn() {}

    trueReturn::trueReturn(Item *returnVal) :
        returnVal(returnVal)
    {
    }


    /*
    Function/Program methods.
    */

    Function::Function(userFuncName* functionName, Type* returnType) :
        functionName(functionName),
        returnType(returnType)
    {
    }


    userFuncName* Program::getFunctionName(const std::string& name) {
        userFuncName* res;
        auto it = functionNames.find(name);
        if (it != functionNames.end()) {
            res = it->second;
        } else {
            std::cerr << "could not find " << name << " in the map of function names.\n";
        }
        return res;
    }

}
