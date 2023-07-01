#ifndef SOSH_TOKEN_H
#define SOSH_TOKEN_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <variant>


/**
 * @file SOSH_Token.h
 * @brief Объявление класса SOSH_Token.
 */

/**
 * @brief Перечисление, представляющее типы токенов.
 */
enum class Token_t {
    SOSH_FUNCTION_NAME,
    SOSH_KEYWORD,
    SOSH_LITERAL,
    SOSH_DATA_TYPE,
    SOSH_FLOAT,
    SOSH_DOUBLE,
    SOSH_INT,
    SOSH_STRING,
    SOSH_CHAR,
    SOSH_IDENTIFIER,
    SOSH_OPERATOR,
    SOSH_DELIMITER,
    SOSH_COMMENT,
    SOSH_VOID,
    SOSH_UNDEFINED
};

/**
 * @brief Массив соответствий имен типов токенов и их перечислений.
 */
const std::string token_names[] = {
    "SOSH_FUNCTION_NAME",
    "SOSH_KEYWORD",
    "SOSH_LITERAL",
    "SOSH_DATA_TYPE",
    "SOSH_FLOAT",
    "SOSH_DOUBLE",
    "SOSH_INT",
    "SOSH_STRING",
    "SOSH_CHAR",
    "SOSH_IDENTIFIER",
    "SOSH_OPERATOR",
    "SOSH_DELIMITER",
    "SOSH_COMMENT",
    "SOSH_VOID",
    "SOSH_UNDEFINED"
};

/**
 * @brief Класс, представляющий токен.
 */
class SOSH_Token {
private:
    Token_t type; 
    std::string lexeme; 
public:
	
	/**
     * @brief Конструктор класса SOSH_Token.
     * 
     * @param t Тип токена.
     * @param s Лексема токена.
     */
    SOSH_Token(Token_t t, std::string s) :type(t), lexeme(s) {};
	
	/**
     * @brief Конструктор класса SOSH_Token.
     * 
     * @param t Тип токена.
     */
    SOSH_Token(Token_t t) :type(t) {};
	
	/**
     * @brief Метод для изменения значения лексемы токена.
     * 
     * @param v Новое значение лексемы.
     */
    void EditValue(std::string v);
	
	/**
     * @brief Метод для получения типа токена.
     * 
     * @return Тип токена.
     */
    Token_t GetType() const; 
	
	/**
     * @brief Шаблонный метод для получения значения токена.
     * 
     * @tparam T Тип значения, который требуется получить.
     * @return Значение токена в указанном типе.
     */
    template<typename T = std::string> T GetValue() const;
	
	/**
     * @brief Специализация шаблонного метода GetValue для типа std::string.
     * 
     * @return Значение токена в типе std::string.
     */
    template<> std::string GetValue<std::string>() const;
};

template<typename T> 
T SOSH_Token::GetValue() const {
    T v;
    std::istringstream iss(lexeme);
    iss >> v;
    return v;
};

template<> 
std::string SOSH_Token::GetValue<std::string>() const {
    return lexeme;
};

#endif // SOSH_TOKEN_H
