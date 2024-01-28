#include "L1.h"

namespace L1 {

/*
  Token Classes
*/
Register::Register (std::string r)
  : ID {r}{
  return ;
}
std::string Register::translate() {
  return "%" + this->ID;
}
std::string Register::get_ID() {
  return this->ID;
}

Number::Number (int n)
  : value {n}{
  return ;
}
std::string Number::translate () {
  return "$" + this->value;
}
int Number::get_value() {
  return this->value;
}

Name::Name (const std::string &value)
  : value {value}{
  return ;    
}
std::string Name::translate () {
  return "$_" + this->value;
}
std::string Name::get_value() {
  return this->value;
}

Label::Label (const std::string &value)
  : value {value}{
  return ;
}
std::string Label::translate () {
  return "$" + this->value;
}
std::string Label::get_value() {
  return this->value;
}


Instruction_assignment::Instruction_assignment (Item *dst, Item *src)
  : s { src },
    d { dst } {
  return ;
}

}
