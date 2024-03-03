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

namespace IR{
    class Token {
        public:
        virtual ~Token() = default;
    };
    class Type : public Token{};

    class TupleType : public Type {
        friend class Singleton;
        TupleType() = default;
    };

    class CodeType : public Type {
        friend class Singleton;
        CodeType() = default;
    };

    class IntType : public Type {
        friend class Singleton;
        IntType() = default;
    };

    class VoidType : public Type{
        friend class Singleton;
        VoidType() = default;
    };
    class Item : public Token {
        public:
    };
    class Number : public Item {
        public:
            explicit Number(int64_t value);
            int64_t const value; 
    };
    class arrAccess: public Item{
        public:
            explicit arrAccess(Variable *obj);
            Variable *const object;

    };
    class Variable : public Item{
        public:
            explicit Variable(std::string name);
            std::string name;
    };
    class userFuncName : public Item {
        public:
            // Constructor
            explicit userFuncName(const std::string& name);
            std::string getName() const;
            std::string name;
        };
    enum OperatorEnum {
        gt,
        geq,
        eq,
        leq,
        times,
        minus,
        plus, 
        lt,
        left,
        right,
        amp,
    };

    class OperatorSingletons {
    public:
        inline static Operator *const EQ = new Operator(eq);
        inline static Operator *const GEQ = new Operator(geq);
        inline static Operator *const GT = new Operator(gt);
        inline static Operator *const PLUS = new Operator(plus);
        inline static Operator *const MINUS = new Operator(minus);
        inline static Operator *const RIGHT = new Operator(right);
        inline static Operator *const LT = new Operator(lt);
        inline static Operator *const LEQ = new Operator(leq);
        inline static Operator *const TIMES = new Operator(times);
        inline static Operator *const AMP = new Operator(amp);
        inline static Operator *const LEFT = new Operator(left);
    };

    class Operator : public Item {
        friend class OperatorSingletons; 
        explicit Operator(OperatorEnum id); 
        OperatorEnum id; 
    public:
        OperatorEnum getID() const; 
    };


    class Singleton {
        public:
            inline static IntType *const INT_TYPE = new IntType();
            inline static VoidType *const VOID_TYPE = new VoidType();
            inline static TupleType *const TUPLE_TYPE = new TupleType();
            inline static CodeType *const CODE_TYPE = new CodeType();
    };

    class Visitor {
        public:
           
    };

    // Specific IR declarations

    class Instruction : public Token {
        public:

    };
    class voidInstruction : public Instruction {
        public:
            virtual void gen(Function *f, std::ofstream &outputFile) = 0;
    }; 

    class nonVoidInstruction : public Instruction {
        public:
            virtual void gen(Function *f, std::ofstream &outputFile) = 0;
            explicit nonVoidInstruction(Variable *dst);
            Variable *const dst;
    };
    class Assignment : public nonVoidInstruction{
        public:
            void gen(Function *f, std::ofstream &outputFile) override;
            explicit Assignment(Variable *dst, Item *src);
            Item *const src;
    };
    class labelInstruction : public voidInstruction {
        public:
            void gen(Function *f, std::ofstream &outputFile) override;
            explicit labelInstruction(std::string label);
            std::string label;
    };
    class operationInstruction: public nonVoidInstruction{
        public:
            void gen(Function *f, std::ofstream &outputFile) override;

            explicit operationInstruction(Variable *dst, Item *t1, Operator *op, Item *t2);
            
            Item *const t1;
            Item *const t2;
            Operator *const op;
    };
    class loadInstruction : public nonVoidInstruction{
        public:
            void gen(Function *f, std::ofstream &outputFile) override;
            explicit loadInstruction(arrAccess *access, Item *var);
            arrAccess *const access;
            Item *const var;
    };
    class storeInstruction: public nonVoidInstruction {
        public:
            void gen(Function *f, std::ofstream &outputFile) override;
            explicit storeInstruction(arrAccess *access, Item *var);
            arrAccess *const access;
            Item *const var; 
    };
    class arrLength : public nonVoidInstruction{
        public:
            void gen(Function *f, std::ofstream &outputFile) override;
            explicit arrLength(Variable *dst, Variable *arr, Item *dim);
            Variable *const arr;
            Item *const dim;
    };
    class tupleLength : public nonVoidInstruction{
        public:
            void gen(Function *f, std::ofstream &outputFile) override;
            explicit tupleLength(Variable *dst, Variable *tuple);
            Variable *const dst;
            Variable *const tuple;
    };

    class VoidCallInstruction : public voidInstruction {
        public:
            void gen(Function *f, std::ofstream &outputFile) override;
            explicit VoidCallInstruction(Item *callee, std::vector<Item *> args);
            Item *const callee;
            std::vector<Item *> args; 
    };
    class NonVoidCallInstruction : public nonVoidInstruction {
    public:
        void gen(Function *f, std::ofstream &outputFile) override;
        explicit NonVoidCallInstruction(Variable *dest, Item *callee, std::vector<Item *> args);
        Item *const callee;
        std::vector<Item *> args; // Now included directly in this class
        Variable *destination; // Assuming Variable *dest is similar to Atom *callee
    };

    class newArray : public nonVoidInstruction {
        public:
            void gen(Function *f, std::ofstream &outputFile) override;
            explicit newArray(Variable *dest, std::vector<Item *> args);
            std::vector<Item *> args; 
            Variable *destination; 
            int offset;
            std::vector<int> dimensions;            
    };
    class newTuple : public nonVoidInstruction {
        public:
            void gen(Function *f, std::ofstream &outputFile) override;
            explicit newTuple(Variable *dest, Item *size);
            Item *const size;
    };

    enum SystemFunctionType {
        Print,
        Input,
        ToUpper,
        Tenserr
    };

    class SystemCallFunction : public Item {
    private:
        explicit SystemCallFunction(SystemFunctionType type) : type_(type) {}

    public:
        const SystemFunctionType type_;


        SystemFunctionType getType() const {
            return type_;
        }

        // Singleton instances
        static SystemCallFunction *const PrintInstance() {
            static SystemCallFunction instance(SystemFunctionType::Print);
            return &instance;
        }

        static SystemCallFunction *const InputInstance() {
            static SystemCallFunction instance(SystemFunctionType::Input);
            return &instance;
        }

        static SystemCallFunction *const ToUpperInstance() {
            static SystemCallFunction instance(SystemFunctionType::ToUpper);
            return &instance;
        }

        static SystemCallFunction *const TenserrInstance() {
            static SystemCallFunction instance(SystemFunctionType::Tenserr);
            return &instance;
        }
    };


    class varArguments : public Token {
        public:
            explicit varArguments(std::vector<Item*> args);
            std::vector<Item *> args;
    };


    class Block : public Token {
        public:
            explicit Block(std::string label);
            void appendInstruction(Instruction *i);
            std::string getLabel();
            bool marked = false;
            std::vector<Block *> successors;
            std::vector<Instruction*> instructionBody;
            std::string label;
            teInstruction *terminator = nullptr;
    };
    class teInstruction : public voidInstruction {
        public:
            virtual std::vector<Block *> getSuccessors() = 0;
    };

    class oneSuccBranch : public teInstruction {
        public: 
            explicit oneSuccBranch(Block *block);
            std::vector<Block *> getSuccessors() override;
            Block *const block;
    };

    class twoSuccBranch : public teInstruction {
        public:
            twoSuccBranch(Item *t, Block *trueBBlock , Block *falseB);
            std::vector<Block*> getSuccessors() override;
            Item *const t;
            Block *const trueB;
            Block *const falseB;
    };

    class falseReturn : public teInstruction{
        public:
            std::vector<Block *> getSuccessors() override;
    };

    class trueReturn : public teInstruction {
        public:
            explicit trueReturn(Item *returnVal);
            std::vector<Block *> getSuccessors() override;
            Item *const returnVal;
    };
    class blockVisitor{
        public:
            virtual void forBlock(Function *function)= 0;
    };
    class Function {
        public:
            explicit Function(userFuncName* functionName, Type* returnType);
            void accept(blockVisitor* visitor); 
            void assignTypeToVariable(Variable* variable, Type* type);
            Block* getBlockByName(const std::string& blockName);
            Variable* getVariableByName(const std::string& variableName);
            userFuncName* getFunctionName() const;
            std::vector<Instruction *> instructions;
            std::vector<Variable*> parameters;
            std::vector<Block*> codeBlocks;
            std::vector<Block*> executionTraceOrder;
            std::unordered_map<std::string, Variable*> variableNameToPointer;
            std::unordered_map<Variable*, Type*> variableToTypeMapping;
            std::unordered_map<std::string, Block*> blockNameToPointer;
            Type* returnType;
            userFuncName* functionName;
    };

    class ProgramVisitor;

    class Program {
        public:
            void accept(ProgramVisitor *v);
            std::vector<Function *> functions;
            userFuncName *getFunctionName(const std::string& name);
            std::unordered_map<std::string, userFuncName *> functionNames;
    };
    
}