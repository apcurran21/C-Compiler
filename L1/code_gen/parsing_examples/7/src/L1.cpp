#include "L1.h"

namespace L1 {

/*
  Token Classes
*/
Register::Register (std::string r)
  : ID {r}{
  return ;
}
int Register::translate() {
  return 0;
}
std::string Register::get_ID() {
  return this->ID;
}

Number::Number (int n)
  : value {n}{
  return ;
}
int Number::translate () {
  return 1;
}
int Number::get_value() {
  return this->value;
}

Name::Name (const std::string &value)
  : value {value}{
  return ;    
}
int Name::translate () {
  return 2;
}
std::string Name::get_value() {
  return this->value;
}

Label::Label (const std::string &value)
  : value {value}{
  return ;
}
int Label::translate () {
  return 3;
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
