#ifndef SOSH_SHELL_H
#define SOSH_SHELL_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

#include "SOSH_Function.cpp"
#include "SOSH_Parser.cpp"

/*

Класс SOSH_Shell представляет интерактивную оболочку, которая используется для выполнения функций, определенных в классе-функции SOSH_Function_Base.

Поля класса:
- funcs_pool - это вектор ссылок на объекты класса SOSH_Function_Base. Он используется для хранения всех функций, которые могут быть вызваны в рамках данной оболочки.
- name - это приватное строковое поле, которое содержит имя оболочки. Оно может быть установлено при создании объекта или пустым по умолчанию.

Методы класса:
- SOSH_Shell() - это конструктор класса по умолчанию, который не принимает аргументов и инициализирует поля по умолчанию.
- SOSH_Shell(const std::string &s) - это конструктор с параметром, который принимает строку имени и инициализирует поле name значением s.
- AddFunction(SOSH_Function_Base &f) - это метод, который добавляет функцию f в вектор funcs_pool, если ее имя не повторяется с уже существующими функциями в векторе.
- FindFunction(const std::string &s) - это метод, который принимает строку имени функции в качестве аргумента и возвращает указатель на объект функции с таким именем, если такая функция существует в векторе funcs_pool, в противном случае возвращает nullptr.
- ListFunction() - это метод, который возвращает вектор ссылок на все функции, которые были добавлены в вектор funcs_pool.
- GetName() - это метод, который возвращает имя оболочки в виде строки.

*/

class SOSH_Shell {
private:
    std::vector<std::reference_wrapper<SOSH_Function_Base>> funcs_pool; // вектор ссылок на объекты класса SOSH_Function_Base
    std::string name; // приватное строковое поле, которое содержит имя оболочки
public:
    SOSH_Shell() = default;
    SOSH_Shell(const std::string &s) :name(s) {};
    bool AddFunction(SOSH_Function_Base &f); // метод, который добавляет функцию f в вектор funcs_pool, если ее имя не повторяется с уже существующими функциями в векторе
    SOSH_Function_Base* FindFunction(const std::string &s); // метод, который принимает строку имени функции в качестве аргумента и возвращает указатель на объект функции с таким именем
    std::vector<std::reference_wrapper<SOSH_Function_Base>> ListFunction(); // метод, который возвращает вектор ссылок на все функции, которые были добавлены в вектор funcs_pool
    std::string GetName(); // метод, который возвращает имя оболочки в виде строки
};

#endif // SOSH_SHELL_H
