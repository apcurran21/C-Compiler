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
#include "LA.h"

namespace LA {

    /*
    Utilities for the Operation enums and other strings
    */
    OperationEnum stringToOperation(const std::string& str) {
        static const std::map<std::string, OperationEnum> OperationMap = {
            {"+", OperationEnum::plus},
            {"-", OperationEnum::minus},
            {"*", OperationEnum::times},
            {"&", OperationEnum::bwand},
            {"<<", OperationEnum::lshift},
            {">>", OperationEnum::rshift},
            {"<", OperationEnum::less},
            {"<=", OperationEnum::lesseq},
            {"=", OperationEnum::eq},
            {">=", OperationEnum::greatereq},
            {">", OperationEnum::greater}
        };

        auto it = OperationMap.find(str);
        if (it != OperationMap.end()) {
            return it->second;
        } else {
            throw std::invalid_argument("Invalid string");
        }
    }

    TypeEnum stringToType(const std::string& str) {
        static const std::map<std::string, TypeEnum> TypeMap = {
            {"int64", TypeEnum::int64},
            {"tuple", TypeEnum::tuple},
            {"code", TypeEnum::code},
            {"void", TypeEnum::voidt},
            {"[]", TypeEnum::bracks}
        };

        auto it = TypeMap.find(str);
        if (it != TypeMap.end()) {
            return it->second;
        } else {
            throw std::invalid_argument("Invalid string");
        }
    }

    std::string removeAtSymbol(const std::string& str) {
        if (!str.empty() && str[0] == '@') {
            return str.substr(1);
        }
        return str;
    }
    
    Item* popAndGrabBack(std::vector<Item*>& stack) {
        if (stack.empty()) {
            // throw std::runtime_error("stack object is empty");
            if (debug) std::cerr << "stack object is empty\n";
        }
        Item* item = stack.back();
        stack.pop_back();
        return item;
    }

    Item* popAndGrabFront(std::vector<Item*>& stack) {
        if (stack.empty()) {
            // throw std::runtime_error("stack object is empty");
            if (debug) std::cerr << "stack object is empty\n";
        }
        Item* item = stack.front();
        stack.erase(stack.begin());
        return item;
    }


    /*
    LA data types.
    */
   
    /*
    Number
    */
    Number::Number(int64_t n) :
        value(n)
    {
    }

    std::string Number::print() const {
        return std::to_string(value);
    }

    /*
    Name
    */
    Name::Name(std::string val) : 
        value(val) 
    {
    }

    std::string Name::print() const {
        return value;
    }

    /*
    Operation
    */
    Operation::Operation(OperationEnum val) :
        value(val) 
    {
    }

    std::string Operation::print() const {
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
            case OperationEnum::bwand:
                res = "&";
                break;
            case OperationEnum::lshift:
                res = "<<";
                break;
            case OperationEnum::rshift:
                res = ">>";
                break;
            case OperationEnum::less:
                res = "<";
                break;
            case OperationEnum::lesseq:
                res = "<=";
                break;
            case OperationEnum::eq:
                res = "=";
                break;
            case OperationEnum::greatereq:
                res = ">=";
                break;
            case OperationEnum::greater:
                res = ">";
                break;
        }

        return res;
    }

    OperationEnum Operation::get_operation() const {
        return value;
    }

    /*
    Type
    */
    Type::Type(TypeEnum type) :
        value(type)
    {
    }

    std::string Type::print() const {
        std::string res;

        switch (value) {
            case TypeEnum::int64:
                res = "int64";
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

    TypeEnum Type::get_type() const {
        return value;
    }

    int64_t Type::get_dims() const {
        return dims;
    }

    void Type::set_dims(int64_t new_dim) {
        dims = new_dim;
    }

    /*
    Label
    */
    Label::Label(std::string value) :
        value(value)
    {
    }

    std::string Label::print() const {
        return value;
    }


    /*
    Instructions
    */
    Instruction_type_declaration::Instruction_type_declaration(Item *type, Item *name) :
        type(type),
        name(name)
    {
    }

    Instruction_assignment::Instruction_assignment(Item *dest, Item *src) :
        dest(dest),
        src(src)
    {
    }

    Instruction_length::Instruction_length(Item *name1, Item *name2, Item *t) :
        Instruction_assignment(name1, name2),
        t(t)
    {
    }

    Instruction_call_function::Instruction_call_function(Item *name1) :
        callee(name1)
    {
    }

    void Instruction_call_function::addArg(Item* arg) {
        args.push_back(arg);
    }

    Instruction_call_function_assignment::Instruction_call_function_assignment(Item *name1, Item *name2) :
        dest(name1),
        Instruction_call_function(name2)
    {
    }

    Instruction_initialization::Instruction_initialization(Item *name, CollectionEnum type) :
        dest(name),
        type(type)
    {
    }

    void Instruction_initialization::addArg(Item* arg) {
        args.push_back(arg);
    }

    Instruction_store::Instruction_store (Item *name, Item *t) :
        Instruction_assignment(name, t)
    {
    }

    void Instruction_store::addArg(Item* arg) {
        args.push_back(arg);
    }

    Instruction_load::Instruction_load (Item *name1, Item *name2) :
        Instruction_assignment(name1, name2)
    {
    }

    void Instruction_load::addArg(Item* arg) {
        args.push_back(arg);
    }

    Instruction_operation::Instruction_operation(Item *name, Item *t1, Item *op, Item *t2) :
        name(name),
        t1(t1),
        op(op),
        t2(t2)
    {
    }

    Instruction_branch_single::Instruction_branch_single (Item *label1) :
        label1(label1)
    {
    }   

    Instruction_branch_double::Instruction_branch_double (Item *t, Item *label1, Item *label2) :
        t(t),
        Instruction_branch_single(label1),
        label2(label2)
    {
    }

    Instruction_return::Instruction_return ()
    {
    }

    Instruction_return_value::Instruction_return_value (Item *t) :
        t(t)
    {
    }


    /*
    Function
    */
    Function::Function(Item *functionName, Item *returnType) :
        functionName(functionName),
        returnType(returnType)
    {
    }

    void Function::addInstruction(Instruction *new_instruction) {
        instructions.push_back(new_instruction);
    }

    void Function::addParameter(Item *param) {
        parameters.push_back(param);
    }

    
    /*
    Program
    */
    void Program::addFunction(Function *new_function) {
        functions.push_back(new_function);
    }

    Function* Program::getLastFunction() {
        return functions.back();
    }

    int64_t Program::getSize() {
        return functions.size();
    }



}