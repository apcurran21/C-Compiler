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
    OperationType stringToOperation(const std::string& str) {
        static const std::map<std::string, OperationType> OperationMap = {
            {"+", OperationType::plus},
            {"-", OperationType::minus},
            {"*", OperationType::times},
            {"&", OperationType::bwand},
            {"<<", OperationType::lshift},
            {">>", OperationType::rshift},
            {"<", OperationType::less},
            {"<=", OperationType::lesseq},
            {"=", OperationType::eq},
            {">=", OperationType::greatereq},
            {">", OperationType::greater}
        };

        auto it = OperationMap.find(str);
        if (it != OperationMap.end()) {
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
    Name::Name(std::string val) : value(val) {}

    std::string Name::print() const {
        return value;
    }

    /*
    Operation
    */
    Operation::Operation(OperationType val) : value(val) {}

    std::string Operation::print() const {
        std::string res;

        switch (value) {
            case OperationType::plus:
                res = "+";
                break;
            case OperationType::minus:
                res = "-";
                break;
            case OperationType::times:
                res = "*";
                break;
            case OperationType::bwand:
                res = "&";
                break;
            case OperationType::lshift:
                res = "<<";
                break;
            case OperationType::rshift:
                res = ">>";
                break;
            case OperationType::less:
                res = "<";
                break;
            case OperationType::lesseq:
                res = "<=";
                break;
            case OperationType::eq:
                res = "=";
                break;
            case OperationType::greatereq:
                res = ">=";
                break;
            case OperationType::greater:
                res = ">";
                break;
        }

        return res;
    }

    

    OperationType Operation::get_operation() const {
        return value;
    }


}