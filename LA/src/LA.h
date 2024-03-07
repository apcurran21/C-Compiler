#pragma once 

#include <set>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <variant>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <tuple>

namespace LA {



/*
Terminal tokens.
*/
class Item {
    public:
        virtual std::string print() const = 0;
};

class Number : public Item {
    public:
        std::string print() const override;
        int64_t value;
};

class Variable : public Item {
    public:
        std::string print() const override;
        std::string value;
}


/*
Instruction interface and classes
*/
class Instruction {
    public:
        // virtual void accept(Visitor *visitor) = 0;
};

class Instruction_type_declaration : public Instruction {
    public:
        // void accept(Visitor *visitor) override;
        
}








}