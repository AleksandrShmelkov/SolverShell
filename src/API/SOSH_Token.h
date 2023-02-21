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
    //constexpr bool value = std::is_one_same<T,int,double,std::string>::value;
    //std::cout << is_one_same<int,int,float,double,int&>::value << std::endl;
    /*if (constexpr (std::is_same_v<T, int>) || 
        constexpr (std::is_same_v<T, double>) ||
        constexpr (std::is_same_v<T, std::string>)){
        // ...
    }*/
    T v;
    std::istringstream ( value ) >> v;
    return v;
};

#endif