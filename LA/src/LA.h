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

    extern int const debug;

    /*
    Forward declarations.
    */
    class Function; 
    class Program;

    /*
    Enums for operations/comparision tokens, which we store in an Action class
    */
    enum class OperationType {
        plus,
        minus,
        times,
        bwand,
        lshift,
        rshift,
        less,
        lesseq,
        eq,
        greatereq,
        greater
    };
    
    /*
    Utilities for the above enums and name cleaning
    */
    OperationType stringToOperation(const std::string& str);

    std::string removeAtSymbol(const std::string& str);


    /*
    Terminal tokens.
    */
    /*
    Item interface
    */
    class Item {
        public:
            /*
            Returns the value of the item as a string.
            Will likely be used in code generation and debug printing.
            */
            virtual std::string print() const = 0;
    };

    class Number : public Item {
        public:
            Number (int64_t n);
            std::string print() const override;
        private:
            int64_t value;
    };

    class Name : public Item {
        public:
            Name (std::string value);
            std::string print() const override;
        private:
            std::string value;
    };

    class Operation : public Item {
        public:
            Operation (OperationType);
            std::string print() const override;
            OperationType get_operation() const;
        private:
            OperationType value;
    };


    /*
    Instruction interface and classes
    */
    // class Instruction {
    //     public:
    //         // virtual void accept(Visitor *visitor) = 0;
    // };

    // class Instruction_assignment : public Instruction {
    //         // var <- s
    //         public:
    //             Instruction_assignment (Item *dest, Item *src);
    //             void accept(Visitor *visitor) override;
    //             Item* getDest() const;
    //             Item* getSrc() const;
    //         protected:
    //             Item* dest;
    //             Item* src;
    //     };


    // class Instruction_type_declaration : public Instruction {
    //     public:
    //         // void accept(Visitor *visitor) override;

    //     private:

        
    // }



    /*
    Function / Program.
    */
    class Program {
        public:
            // void accept(ProgramVisitor *v);
            // std::vector<Function *> functions;
            // userFuncName *getFunctionName(const std::string& name);
            // std::unordered_map<std::string, userFuncName *> functionNames;
    };
    






}