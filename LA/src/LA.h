#pragma once 

#include <utility>
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
    class Item;
    class Visitor;
    class FileVisitor;

    /*
    Utility class for creating unique names.
    */
    class UniqueNameTracker {
        public:
            static std::string getLongestName();
            static void updateLongestName(const std::string& new_name);
            static std::string getUniqueName();
        private:
            static int64_t counter;
            static std::string longest_name;
    };

    /*
    Enums for operations/comparision tokens, which we store in an Action class
    */
    enum class OperationEnum {
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

    enum TypeEnum {
        int64,  // encodes both single and array int64s using its dims field
        tuple,
        code,
        voidt,
        bracks  // to catch the "[]" dimensions in int64 arrays
    };

    enum CollectionEnum {
        Array,
        Tuple
    };
    
    /*
    Utilities for the above enums, name cleaning, etc
    */
    OperationEnum stringToOperation(const std::string& str);

    TypeEnum stringToType(const std::string& str);

    std::string removeAtSymbol(const std::string& str);

    Item* popAndGrabBack(std::vector<Item*>& stack);

    Item* popAndGrabFront(std::vector<Item*>& stack);


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
            virtual std::string gen() const = 0;
    };

    class Number : public Item {
        public:
            Number (int64_t n);
            std::string print() const override;
            std::string gen() const override;
            void encode();
        // private:
            int64_t value;
    };

    class Name : public Item {
        public:
            Name (std::string value);
            std::string print() const override;
            std::string gen() const override;
        // private:
            std::string value;
            bool isFunctionName = false;
    };

    class Operation : public Item {
        public:
            Operation (OperationEnum op);
            std::string print() const override;
            std::string gen() const override;
            OperationEnum get_operation() const;
        // private:
            OperationEnum value;
    };

    class Type : public Item {
        public:
            Type (TypeEnum type);
            std::string print() const override;
            std::string gen() const override;
            TypeEnum get_type() const;
            int64_t get_dims() const;
            void set_dims(int64_t new_dim);
        // private:
            TypeEnum value;
            int64_t dims = 0;
    };

    class Label : public Item {
        public:
            Label (std::string value);
            std::string print() const override;
            std::string gen() const override;
        // private:
            std::string value;
    };

    class Parameter {
        public:
            Parameter (Item* type, Item* name);
            std::string print() const;
            std::string gen() const;
        private:
            Item *type;
            Item *name;
    };


    /*
    Instruction interface and classes
    */
    class Instruction {
        public:
            virtual void accept(Visitor *visitor) = 0;
            virtual void accept(FileVisitor *visitor, std::ofstream &outputFile) = 0;
    };

    class Instruction_type_declaration : public Instruction {
        // type name
        public:
            Instruction_type_declaration (Item *type, Item *name);
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
        // private:
            Item *type;
            Item *name;
    };

    class Instruction_assignment : public Instruction {
        // name <- t
        public:
            Instruction_assignment (Item *dest, Item *src);
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
        // protected:
            Item* dest;
            Item* src;
    };

    class Instruction_length : public Instruction_assignment {
        // name1 <- length name2 t?
        public:
            Instruction_length (Item *name1, Item *name2);
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
            void setIndex(Item *index);
        // private:
            Item* t = nullptr;
    };

    class Instruction_call_function : public Instruction {
        // name1 ( args? )
        public:
            Instruction_call_function (Item *name1);
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
            void addArg(Item* arg);
        // protected:
            Item *callee;
            std::vector<Item *> args;
    };

    class Instruction_call_function_assignment :  public Instruction_call_function {
        // name1 <- name2 ( args? )
        public:
            Instruction_call_function_assignment (Item *name1, Item *name2);
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
        // private:
            Item* dest;
    };

    class Instruction_initialization : public Instruction {
        // name <- new <Array/Tuple> ( <args?/t> )
        public: 
            Instruction_initialization (Item *name, CollectionEnum type);
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
            void addArg(Item* arg);
        // private:
            Item *dest;
            CollectionEnum type;
            std::vector<Item *> args;
    };

    class Instruction_store : public Instruction_assignment {
        // name1[t]... <- t
        public:
            Instruction_store (Item *name, Item *t);
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
            void addArg(Item* arg);
        // private:
            std::vector<Item *> args;
            int64_t line_number;
    };

    class Instruction_load : public Instruction_assignment {
        // name1 <- name2[t]...
        public:
            Instruction_load (Item *name1, Item *name2);
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
            void addArg(Item* arg);
        // private:
            std::vector<Item *> args;
            int64_t line_number;
    };

    class Instruction_operation : public Instruction {
        // name <- t1 op t2
        public:
            Instruction_operation (Item *name, Item *t1, Item *op, Item *t2);
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
        // private:
            Item *name;
            Item *t1;
            Item *op;
            Item *t2;
    };

    class Instruction_branch_single : public Instruction {
        // br label1
        public:
            Instruction_branch_single (Item *label1);
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
        // protected:
            Item* label1;
    };

    class Instruction_branch_double : public Instruction_branch_single {
        // br t label1 label2
        public:
            Instruction_branch_double (Item *t, Item *label1, Item *label2);
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
        // private:
            Item *t;
            Item *label2;
    };

    class Instruction_return : public Instruction {
        // return
        public:
            Instruction_return ();
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
    };

    class Instruction_return_value : public Instruction_return {
        // return t
        public:
            Instruction_return_value (Item *t);
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
        // private:
            Item *t;
    };

    class Instruction_label : public Instruction {
        // label
        public:
            Instruction_label (Item *label);
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
        // private:
            Item *label;
    };

    class Instruction_error : public Instruction {
        // <tensor/tuple>-error( args )
        public:
            Instruction_error ();
            void accept(Visitor *visitor) override;
            void accept(FileVisitor *visitor, std::ofstream &outputFile) override;
            std::string type;
            std::vector<Item*> args;
    };



    /*
    Function / Program.
    */
    class Function {
        public:
            Function(Item *functionName, Item *returnType);
            void addInstruction(Instruction *new_instruction);
            void addParameter(Parameter *param);
        // private:
            std::vector<Instruction *> instructions;
            std::vector<Parameter *> parameters;
            Item *functionName;
            Item *returnType;
            std::unordered_map<std::string, Type*> variableNameToType;
    };

    class Program {
        public:
            void addFunction(Function *new_function);
            Function* getLastFunction();
            int64_t getSize();
            const std::vector<Function*>& getFunctions() const;
            // void accept(ProgramVisitor *v);
            // userFuncName *getFunctionName(const std::string& name);
            // std::unordered_map<std::string, userFuncName *> functionNames;
        // private:
            std::vector<Function *> functions;
            std::string longest_name = "";
    };
    

    /*
    Visitors.
    */
    class Visitor {
        public:
            virtual void visit(Instruction_type_declaration* i) = 0;
            virtual void visit(Instruction_assignment* i) = 0;
            virtual void visit(Instruction_length* i) = 0;
            virtual void visit(Instruction_call_function* i) = 0;
            virtual void visit(Instruction_call_function_assignment* i) = 0;
            virtual void visit(Instruction_initialization* i) = 0;
            virtual void visit(Instruction_operation* i) = 0;
            virtual void visit(Instruction_store* i) = 0;
            virtual void visit(Instruction_load* i) = 0;
            virtual void visit(Instruction_branch_single* i) = 0;
            virtual void visit(Instruction_branch_double* i) = 0;
            virtual void visit(Instruction_return* i) = 0;
            virtual void visit(Instruction_return_value* i) = 0;
            virtual void visit(Instruction_label* i) = 0;
            virtual void visit(Instruction_error* i) = 0;
    };

    class FileVisitor {
        public:
            virtual void visit(Instruction_type_declaration* i, std::ofstream &outputFile) = 0;
            virtual void visit(Instruction_assignment* i, std::ofstream &outputFile) = 0;
            virtual void visit(Instruction_length* i, std::ofstream &outputFile) = 0;
            virtual void visit(Instruction_call_function* i, std::ofstream &outputFile) = 0;
            virtual void visit(Instruction_call_function_assignment* i, std::ofstream &outputFile) = 0;
            virtual void visit(Instruction_initialization* i, std::ofstream &outputFile) = 0;
            virtual void visit(Instruction_operation* i, std::ofstream &outputFile) = 0;
            virtual void visit(Instruction_store* i, std::ofstream &outputFile) = 0;
            virtual void visit(Instruction_load* i, std::ofstream &outputFile) = 0;
            virtual void visit(Instruction_branch_single* i, std::ofstream &outputFile) = 0;
            virtual void visit(Instruction_branch_double* i, std::ofstream &outputFile) = 0;
            virtual void visit(Instruction_return* i, std::ofstream &outputFile) = 0;
            virtual void visit(Instruction_return_value* i, std::ofstream &outputFile) = 0;
            virtual void visit(Instruction_label* i, std::ofstream &outputFile) = 0;
            virtual void visit(Instruction_error* i, std::ofstream &outputFile) = 0;
    };




}