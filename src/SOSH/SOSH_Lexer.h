#ifndef SOSH_LEXER_H
#define SOSH_LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <stack>
#include <stdexcept>

#include "SOSH_Token.h"
#include "SOSH_Shell.h"


/**
 * @file Interpreter.h
 * @brief Объявление класса Interpreter
 */

/**
 * @class Lexer
 * @brief Класс, выполняющий лексический анализ и разделение кода на токены.
 */
class Lexer {
public:
    /**
     * @brief Конструктор класса Lexer.
     * @param code Код, который требуется проанализировать.
     * @param shell Объект класса SOSH_Shell, используемый для поиска функций.
     */
    Lexer::Lexer(const std::string& code, SOSH_Shell shell = SOSH_Shell("")) : code(code), currentPosition(0), shell(shell) {};

    /**
     * @brief Метод для выполнения лексического анализа кода.
     * @return Вектор токенов, полученных в результате анализа.
     */
    std::vector<SOSH_Token> tokenize();

private:
    std::string code; /**< Код для анализа */
    size_t currentPosition; /**< Текущая позиция в коде */
    SOSH_Shell shell; /**< Объект класса SOSH_Shell, используемый для поиска функций */

    /**
     * @brief Проверяет, является ли символ пробелом.
     * @param c Символ для проверки.
     * @return true, если символ является пробелом, иначе false.
     */
    bool isWhitespace(char c);

    /**
     * @brief Проверяет, является ли символ буквой.
     * @param c Символ для проверки.
     * @return true, если символ является буквой, иначе false.
     */
    bool isAlpha(char c);

    /**
     * @brief Проверяет, является ли символ цифрой.
     * @param c Символ для проверки.
     * @return true, если символ является цифрой, иначе false.
     */
    bool isDigit(char c);

    /**
     * @brief Проверяет, является ли символ оператором.
     * @param c Символ для проверки.
     * @return true, если символ является оператором, иначе false.
     */
    bool isOperator(char c);

    /**
     * @brief Проверяет, является ли символ разделителем.
     * @param c Символ для проверки.
     * @return true, если символ является разделителем, иначе false.
     */
    bool isDelimiter(char c);

    /**
     * @brief Выполняет разбор идентификатора или ключевого слова.
     * @return Токен, представляющий идентификатор или ключевое слово.
     */
    SOSH_Token parseIdentifierOrKeyword();

    /**
     * @brief Выполняет разбор числа.
     * @return Токен, представляющий число.
     */
    SOSH_Token parseNumber();

    /**
     * @brief Выполняет разбор строки.
     * @return Токен, представляющий строку.
     */
    SOSH_Token parseString();

    /**
     * @brief Выполняет разбор символа.
     * @return Токен, представляющий символ.
     */
    SOSH_Token parseCharacter();

    /**
     * @brief Выполняет разбор оператора.
     * @return Токен, представляющий оператор.
     */
    SOSH_Token parseOperator();

    /**
     * @brief Выполняет разбор разделителя.
     * @return Токен, представляющий разделитель.
     */
    SOSH_Token parseDelimiter();

    /**
     * @brief Выполняет разбор комментария.
     */
    void parseComment();
};

#endif // SOSH_LEXER_H
