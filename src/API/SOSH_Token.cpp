#ifndef SOSH_TOKEN_CPP
#define SOSH_TOKEN_CPP

#include "SOSH_Token.h"

void SOSH_Token::EditValue(std::string v) {
    value = v;
};

Token_t SOSH_Token::GetType(){
    return token;
};

template<> 
std::string SOSH_Token::GetValue<std::string>() const {
    return value;
};

std::variant<int, double, std::string> SOSH_Token::GetTypedValue() const {
    switch (token) {
        case Token_t::SOSH_INT:
            return std::stoi(value);
        case Token_t::SOSH_DOUBLE:
            return std::stod(value);
        case Token_t::SOSH_STRING:
            return value;
        default:
            throw std::runtime_error("Cannot convert value to type specified by token");
    }
};

std::string tokenToString(Token_t token) {
    switch(token) {
        case Token_t::SOSH_FUNCTION_NAME:
            return "SOSH_FUNCTION_NAME";
        case Token_t::SOSH_INT:
            return "SOSH_INT";
        case Token_t::SOSH_DOUBLE:
            return "SOSH_DOUBLE";
        case Token_t::SOSH_STRING:
            return "SOSH_STRING";
        default:
            return "SOSH_UNDEFINED";
    };
};

std::ostream &operator<<(std::ostream &stream, const Token_t token) {
  switch (token) {
    case Token_t::SOSH_FUNCTION_NAME:
      stream << "SOSH_FUNCTION_NAME";
      break;
    case Token_t::SOSH_INT:
      stream << "SOSH_INT";
      break;
    case Token_t::SOSH_DOUBLE:
      stream << "SOSH_DOUBLE";
      break;
    case Token_t::SOSH_STRING:
      stream << "SOSH_STRING";
      break;
    case Token_t::SOSH_UNDEFINED:
      stream << "SOSH_UNDEFINED";
      break;
  };

  return stream;
};

#endif // SOSH_TOKEN_CPP
