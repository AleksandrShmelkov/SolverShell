#ifndef SOSH_INTERPRETER_H
#define SOSH_INTERPRETER_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

#include "SOSH_Parser.h"


/**
 * @file Interpreter.h
 * @brief Объявление класса Interpreter
 */

/**
 * @class Interpreter
 * @brief Класс, представляющий интерпретатор для вычисления выражений
 */
class Interpreter {
public:

    /**
     * @brief Выполняет вычисление выражения
     * @param expression Выражение для вычисления
     * @param shell Объект SOSH_Shell, представляющий оболочку
     * @return Результат вычисления в виде объекта SOSH_Token
     */
    static SOSH_Token Interpreter::evaluate(const std::string& expression, SOSH_Shell shell = SOSH_Shell(""));

};

#endif // SOSH_INTERPRETER_H
