#pragma once
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

namespace L3 {

    extern int const debug;

    /*
    Forward declarations for our program data types.
    */
    class Function; 
    class Program;
    class Item;
    class Visitor;

    /*
    Enums for operations/comparision tokens, which we store in an Action class
    - Todo: implement a print method for this.
    */
    enum class OperationType {
        plus,
        minus,
        times,
        bwand,
        lshift,
        rshift,
    };

    enum class ComparisonType {
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

    ComparisonType stringToComparison(const std::string& str);

    std::string removeAtSymbol(const std::string& str);


    /*
    Data types used in the L3 program's memory representation.
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
            Number (long long int n);
            std::string print() const override;
        private:
            long long int value;
    };

    // maybe this won't get used rn
    class Name : public Item {
        public:
            Name (std::string value);
            std::string print() const override;
        private:
            std::string value;
    };


    /*
    Base class for Labels, Function Names, Variables
    */
    class Symbol : public Item {
        public:
            Symbol (std::string value);
            std::string print() const override;
        private:
            std::string value;
    };

    /*
    Class for operations
    */
    class Operation : public Item {
        public:
            Operation (OperationType);
            std::string print() const override;
            OperationType get_operation() const;
        private:
            OperationType value;
    };

    /*
    Class for comparisons
    */
    class Comparison : public Item {
        public:
            Comparison (ComparisonType);
            std::string print() const override;
        private:
            ComparisonType value;
    };


    /*
    Instruction interface and classes
    */
    class Instruction {
        public:
            virtual void accept(Visitor *visitor) = 0;
    };

    class Instruction_assignment : public Instruction {
        // var <- s
        public:
            Instruction_assignment (Item *dest, Item *src);
            void accept(Visitor *visitor) override;
            Item* getDest() const;
            Item* getSrc() const;
        protected:
            Item* dest;
            Item* src;
    };

    class Instruction_load : public Instruction_assignment {
        // var1 <- load var2
        public:
            Instruction_load(Item *var1, Item *var2);
            void accept(Visitor *visitor) override;
    };

    class Instruction_store : public Instruction_assignment {
        // store var1 <- var2
        public:
            Instruction_store(Item *var1, Item *var2);
            void accept(Visitor *visitor) override;
    };


    class Instruction_action : public Instruction {
        // Sort of abstract class for:
        // var <- t1 op t2 | var <- t1 cmp t2
        // dest <- src1 op src2 | dest <- src1 comp src2
        public:
            Instruction_action (Item *var, Item *t1, Item *action, Item *t2);
            void accept(Visitor *visitor) override;
            Item* getDest() const;
            Item* getSrc1() const;
            Item* getAction() const;
            Item* getSrc2() const;
        protected:
            Item* var;
            Item* t1;
            Item* action;
            Item* t2;
    };

    class Instruction_operation : public Instruction_action {
        // var <- t1 op t2
        public:
            Instruction_operation (Item *var, Item *t1, Item *action, Item *t2);
            void accept(Visitor *visitor) override;
    };

    class Instruction_comparison : public Instruction_action {
        // var <- t1 cmp t2
        public:
            Instruction_comparison (Item *var, Item *t1, Item *action, Item *t2);
            void accept(Visitor *visitor) override;
    };

    class Instruction_return : public Instruction {
        // return
        public:
            Instruction_return ();
            void accept(Visitor *vistor) override;
    };

    class Instruction_return_value : public Instruction_return {
        // return t
        public:
            Instruction_return_value (Item* t);
            void accept(Visitor *visitor) override;
            Item* getT() const;
        private:
            Item* t;
    };

    class Instruction_label : public Instruction {
        // label
        public:
            Instruction_label (Item *label);
            void accept(Visitor *visitor) override;
            Item* getLabel() const;
        private:
            Item* label;
    };

    class Instruction_branch_label : public Instruction {
        // br label
        public:
            Instruction_branch_label (Item *label);
            void accept(Visitor *visitor) override;
            Item* getLabel() const;
        protected:
            Item* label;
    };

    class Instruction_branch_label_conditional : public Instruction_branch_label {
        // br t label
        public:
            Instruction_branch_label_conditional (Item *t, Item *label);
            void accept(Visitor *visitor) override;
            Item* getCondition() const;
        private:
            Item* t;
    };

    class Instruction_call_function : public Instruction {
        // call callee ( args )
        public:
            /*
            Note - we are passing by reference for the vector of args. Would it be better to copy each item in the vector?
            */
            Instruction_call_function (Item *callee);
            void accept(Visitor *visitor) override;
            Item* getCallee() const;
            std::vector<Item*> getArgs() const;
            void addArg(Item* arg);
        protected:
            Item* callee;
            std::vector<Item*> args;
    };

    class Instruction_call_function_assignment : public Instruction_call_function {
        // var <- call callee ( args )
        public:
            Instruction_call_function_assignment (Item *var, Item *callee);
            void accept(Visitor *visitor) override;
            Item* getDest() const;
        private:
            Item* var;
    };


    /*
    Function / Program
    */
    class Function {
        public:
            void print() const;
            void setFunctionName(std::string new_name);
            void addParameter(Item *new_parameter);             // push onto parameters stack
            void addInstruction(Instruction *new_instruction);  // push onto instructions stack
        private:
            std::string name;
            std::vector<Item*> parameters;
            std::vector<Instruction*> instructions;
    };

    class Program {
        public:
            void print() const;
            void addFunction(Function *new_function);
            void getLastFunction();
        private:
            std::vector<Function*> functions;
    };


    /*
    Visitor Interface.
    -None necessary for the naive implementation.
    */
    class Visitor {
        public:
            virtual void visit(Instruction_assignment *instruction) = 0;
            virtual void visit(Instruction_load *instruction) = 0;
            virtual void visit(Instruction_store *instruction) = 0;
            virtual void visit(Instruction_action *instruction) = 0;
            virtual void visit(Instruction_operation *instruction) = 0;
            virtual void visit(Instruction_comparison *instruction) = 0;
            virtual void visit(Instruction_return *instruction) = 0;
            virtual void visit(Instruction_return_value *instruction) = 0;
            virtual void visit(Instruction_label *instruction) = 0;
            virtual void visit(Instruction_branch_label *instruction) = 0;
            virtual void visit(Instruction_branch_label_conditional *instruction) = 0;
            virtual void visit(Instruction_call_function *instruction) = 0;
            virtual void visit(Instruction_call_function_assignment *instruction) = 0;
    };

//     /*
//     Print Visitor for instructions.
//     */
//     class PrintVisitor : public Visitor {
//         virtual void visit(Instruction_assignment *instruction) override;
//         virtual void visit(Instruction_load *instruction) override;
//         virtual void visit(Instruction_store *instruction) override;
//         virtual void visit(Instruction_action *instruction) override;
//         virtual void visit(Instruction_operation *instruction) override;
//         virtual void visit(Instruction_comparison *instruction) override;
//         virtual void visit(Instruction_return *instruction) override;
//         virtual void visit(Instruction_return_value *instruction) override;
//         virtual void visit(Instruction_label *instruction) override;
//         virtual void visit(Instruction_branch_label *instruction) override;
//         virtual void visit(Instruction_branch_label_conditional *instruction) override;
//         virtual void visit(Instruction_call_function *instruction) override;
//         virtual void visit(Instruction_call_function_assignment *instruction) override;
//     };


}