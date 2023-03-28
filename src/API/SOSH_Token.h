#ifndef SOSH_TOOLKIT_H
#define SOSH_TOOLKIT_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

enum class Token_t { SOSH_FUNCTION_NAME, SOSH_INT, SOSH_DOUBLE, SOSH_STRING, SOSH_UNDEFINED };
class SOSH_Token {
private:
    const Token_t token;
    const std::string value;
public:
    SOSH_Token(Token_t t, const std::string &s) :token(t), value(s) {};
    template<typename T = std::string> T Value(); // Возвращает значение в типе
    Token_t Type(); // Возвращает тип 
};

template<typename T> 
T SOSH_Token::Value(){
    T v;
    std::istringstream ( value ) >> v;
    return v;
};

#endif