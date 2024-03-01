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
    class ItemVisitor;
    class Item : public Token {
        public:
        virtual void accept (ItemVisitor *v) = 0;
    };
    class Number : public Item {
        public:
            void accept(ItemVisitor *v) override;
            explicit Number(int64_t value);
            int64_t const value; 
    };
    class arrAccess: public Item{
        public:
            void accept(ItemVisitor *v) override;
            explicit arrAccess(Variable *obj);
            Variable *const object;

    };
    class Variable : public Item{
        public:
            void accept(ItemVisitor *v) override;
            explicit Variable(std::string name);
            std::string name;
    };
    class userFuncName : public Item {
        public:
            // Constructor
            explicit userFuncName(const std::string& name);
            void accept(ItemVisitor *v) override;
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
        void accept(ItemVisitor *v) override;
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

    class InstructionVisitor;

    class Instruction : public Token {
        public:
        virtual void accept(InstructionVisitor *v) = 0;
    };
    class voidInstruction : public Instruction {}; 

    class nonVoidInstruction : public Instruction {
        public:
            explicit nonVoidInstruction(Variable *dst);
            Variable *const dst;
    };
    class Assignment : public nonVoidInstruction{
        public:
            void accept(InstructionVisitor *v) override;
            explicit Assignment(Variable *dst, Item *src);
            Item *const src;
    };

    class operationInstruction: public nonVoidInstruction{
        public:
            void accept(InstructionVisitor *) override;
            explicit operationInstruction(Variable *dst, Item *t1, Operator *op, Item *t2);
            Item *const t1;
            Item *const t2;
            Operator *const op;
    };
    class loadInstruction : public nonVoidInstruction{
        public:
            void accept(InstructionVisitor *) override;
            explicit loadInstruction(arrAccess *access, Item *var);
            arrAccess *const access;
            Item *const var;
    };
    class storeInstruction: public nonVoidInstruction {
        public:
            void accept(InstructionVisitor *) override;
            explicit storeInstruction(arrAccess *access, Item *var);
            arrAccess *const access;
            Item *const var; 
    };
    class getArrDimension : public nonVoidInstruction{
        public:
            void accept(InstructionVisitor *) override;
            explicit getArrDimension(Variable *dst, Variable *arr, Item *dim);
            Variable *const arr;
            Item *const dim;
    };
    class tupleLength : public nonVoidInstruction{
        public:
            void accept(InstructionVisitor *) override;
            explicit tupleLength(Variable *dst, Variable *tuple);
            Variable *const dst;
            Variable *const tuple;
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

        void accept(ItemVisitor *v) override {
        }

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
    class VoidCallInstruction : public voidInstruction {
        public:
            void accept(InstructionVisitor *v) override;
            explicit VoidCallInstruction(Item *callee, std::vector<Item *> args);
            Item *const callee;
            std::vector<Item *> args; 
    };
    class NonVoidCallInstruction : public nonVoidInstruction {
    public:
        void accept(InstructionVisitor *v) override;
        explicit NonVoidCallInstruction(Variable *dest, Item *callee, std::vector<Item *> args);
        Item *const callee;
        std::vector<Item *> args; // Now included directly in this class
        Variable *destination; // Assuming Variable *dest is similar to Atom *callee
    };

    class newArray : public nonVoidInstruction {
        public:
            void accept(InstructionVisitor *v) override;
            explicit newArray(Variable *dest, std::vector<Item *> args);
            std::vector<Item *> args; 
            Variable *destination; 
    };
    class newTuple : public nonVoidInstruction {
        public:
            void accept(InstructionVisitor *v) override;
            explicit newTuple(Variable *dest, Item *size);
            Item *const size;
    };

    class Block : public Token {
        public:
            Block(std::string label);
            std::vector<Block *> getSuccessors();
            void appendInstruction(Instruction *i);
            std::string getLabel();
            bool marked = false;
            std::vector<Instruction*> instructionBody;
            std::string label;
            teInstruction *terminator = nullptr;
    };
    class teInstructionVisitor;

    class teInstruction : public voidInstruction {
        public:
            void accept(InstructionVisitor *v) override;
            virtual void accept(teInstructionVisitor *v) = 0;
            virtual std::vector<Block *> getSuccessors() = 0;
    };

    class oneSuccBranch : public teInstruction {
        public: 
            void accept(teInstructionVisitor *v) override;
            explicit oneSuccBranch(Block *block);
            std::vector<Block *> getSuccessors() override;
            Block *const block;
    };

    class twoSuccBranch : public teInstruction {
        public:
            void accept(teInstructionVisitor *v) override;
            twoSuccBranch(Item *t, Block *trueBBlock , Block *falseB);
            std::vector<Block*> getSuccessors() override;
            Item *const t;
            Block *const trueB;
            Block *const falseB;
    };

    class falseReturn : public teInstruction{
        public:
            void accept(teInstructionVisitor *v) override;
            std::vector<Block *> getSuccessors() override;
    };

    class trueReturn : public teInstruction {
        public:
            void accept(teInstructionVisitor *v) override;
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