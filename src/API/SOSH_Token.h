#pragma once

#ifndef SOSH_TOKEN_H
#define SOSH_TOKEN_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <variant>

// Перечисление Token_t представляет собой перечисление типов токенов, которые могут быть использованы в языке программирования. Каждому типу соответствует уникальное значение.
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

/*

Класс SOSH_Token представляет собой объект токена, который может быть использован в парсере для обработки кода на языке DSL.

Поля:
- token - тип токена из перечисления Token_t.
- value - строковое значение токена.

Методы:
- SOSH_Token(Token_t t, std::string s) - конструктор класса, принимающий тип токена и строковое значение.
- SOSH_Token(Token_t t) - конструктор класса, принимающий только тип токена.
- EditValue(std::string v) - изменяет значение токена на переданную строку.
- GetType() - возвращает тип токена.
- template<typename T = std::string> T GetValue() const - возвращает значение токена, приведенное к заданному типу данных T.
- std::variant<int, double, std::string> GetTypedValue() const - конвертирует значение токена на основе его внутреннего типа.
- template<Token_t TokenType> auto GetValueByTokenType() const - конвертирует значение токена на основе заданного типа токена.

*/

class SOSH_Token {
private:
    Token_t token; // тип токена из перечисления Token_t
    std::string value; // строковое значение токена
public:
    SOSH_Token(Token_t t, std::string s) :token(t), value(s) {};
    SOSH_Token(Token_t t) :token(t) {};
    void EditValue(std::string v); // Изменяет внутренее значение
    Token_t GetType(); // Возвращает внутрений тип
    template<typename T = std::string> T GetValue() const; // Возвращает значение на основе внешнего типа
    template<> std::string GetValue<std::string>() const;

    std::variant<int, double, std::string> GetTypedValue() const; // Конвертирует на основе внутреннего Token_t
    template<Token_t TokenType> auto GetValueByTokenType() const; // Конвертирует на основе внешнего Token_t
};

template<typename T> 
T SOSH_Token::GetValue() const {
    T v;
    std::istringstream iss(value);
    /*if (std::is_same<T, std::string>::value) {
        std::getline(iss, v, '\n');
    };*/
    /*int count = 0;
    std::string buff = "";
    for (char c : value) {
        if (c == '\n') {
            count++;
        };
    };
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            iss >> v;
            buff = buff + v;
        };
        v = buff;
    } else {
        iss >> v;
    };*/
    iss >> v;
    return v;
};

template<> 
std::string SOSH_Token::GetValue<std::string>() const {
    return value;
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

// Дочерний класс для описания добавляемых типов ?
// Создать структуру в виде двухсвязного списка где поля содержит ссылку на объект типа этой структуры ? 
// ...Первй пустой обьект этой структуры присвоить классу shell. Структура будет содержать ссылки на обьекты класса функции.

#endif
