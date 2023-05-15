#ifndef SOSH_TOOLKIT_H
#define SOSH_TOOLKIT_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <variant>

enum class Token_t {
    SOSH_FUNCTION_NAME,
    SOSH_INT,
    SOSH_DOUBLE,
    SOSH_STRING,
    SOSH_VOID,
    SOSH_UNDEFINED
};

const std::string token_names[] = {
    "SOSH_FUNCTION_NAME",
    "SOSH_INT",
    "SOSH_DOUBLE",
    "SOSH_STRING",
    "SOSH_VOID",
    "SOSH_UNDEFINED"
};

class SOSH_Token {
private:
    Token_t token;
    std::string value;
public:
    SOSH_Token(Token_t t, std::string s) :token(t), value(s) {};
    SOSH_Token(Token_t t) :token(t) {};
    void EditValue(std::string v); // Изменяет внутренее значение
    Token_t GetType(); // Возвращает внутрений тип
    template<typename T = std::string> T GetValue() const; // Возвращает значение на основе внешнего типа
    std::variant<int, double, std::string> GetTypedValue() const; // Конвертирует на основе внутреннего Token_t
    template<Token_t TokenType> auto GetValueByTokenType() const; // Конвертирует на основе внешнего Token_t
};

template<typename T> 
T SOSH_Token::GetValue() const {
    T v;
    std::istringstream ( value ) >> v;
    return v;
};

template<Token_t TokenType>
auto SOSH_Token::GetValueByTokenType() const {
    if constexpr (TokenType == Token_t::SOSH_FUNCTION_NAME) {
        return value;
    } else if constexpr (TokenType == Token_t::SOSH_INT) {
        return std::stoi(value);
    } else if constexpr (TokenType == Token_t::SOSH_DOUBLE) {
        return std::stod(value);
    } else if constexpr (TokenType == Token_t::SOSH_STRING) {
        return value;
    } else {
        return value;
    };
};

#endif
