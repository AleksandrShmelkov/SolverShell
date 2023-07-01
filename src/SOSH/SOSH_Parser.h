#ifndef SOSH_PARSER_H
#define SOSH_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

#include "SOSH_AST.h"
#include "SOSH_Lexer.h"


/**
 * @file SOSH_Parser.h
 * @brief Объявление класса SOSH_Parser.
 */

/**
 * @brief Класс SOSH_Parser используется для разбора строки команды в SOSH скрипте.
 */
class SOSH_Parser {
public:
    /**
     * @brief Конструктор парсера.
     * @param expression Входное выражение для разбора.
     * @param shell Объект типа SOSH_Shell.
     */
    SOSH_Parser(const std::string& expression, SOSH_Shell shell = SOSH_Shell("")) : lexer(expression, shell), currentPosition(0), shell(shell) {};

    /**
     * @brief Конструктор парсера.
     * @param lexer Лексер для получения токенов.
     * @param shell Объект типа SOSH_Shell.
     */
    SOSH_Parser(Lexer lexer, SOSH_Shell shell = SOSH_Shell("")) : lexer(lexer), currentPosition(0), shell(shell) {};

    /**
     * @brief Метод для парсинга выражения.
     * @return Указатель на корневой узел абстрактного синтаксического дерева (AST).
     */
    ASTNode* parse();

    /**
     * @brief Метод для токенизации входной строки.
     * @param s Входная строка для токенизации.
     * @return Вектор токенов.
     */
    std::vector<SOSH_Token> Tokenize(const std::string &s);

private:
    Lexer lexer; ///< Лексер для получения токенов.
    size_t currentPosition; ///< Текущая позиция в токенах.
    SOSH_Shell shell; ///< Объект типа SOSH_Shell.
    std::string value; ///< Входная строка для разбора. Tokenize.
    std::vector<SOSH_Token> out; ///< Результат разбора в виде вектора токенов. Tokenize.

    /**
     * @brief Метод для парсинга выражения или функции.
     * @param tokens Вектор токенов.
     * @return Указатель на узел абстрактного синтаксического дерева (AST).
     */
    ASTNode* parseExpressionOrFunction(const std::vector<SOSH_Token>& tokens);

    /**
     * @brief Метод для парсинга выражения.
     * @param tokens Вектор токенов.
     * @return Указатель на узел абстрактного синтаксического дерева (AST).
     */
    ASTNode* parseExpression(const std::vector<SOSH_Token>& tokens);

    /**
     * @brief Метод для парсинга терма.
     * @param tokens Вектор токенов.
     * @return Указатель на узел абстрактного синтаксического дерева (AST).
     */
    ASTNode* parseTerm(const std::vector<SOSH_Token>& tokens);

    /**
     * @brief Метод для парсинга фактора.
     * @param tokens Вектор токенов.
     * @return Указатель на узел абстрактного синтаксического дерева (AST).
     */
    ASTNode* parseFactor(const std::vector<SOSH_Token>& tokens);
};

#endif // SOSH_PARSER_H
