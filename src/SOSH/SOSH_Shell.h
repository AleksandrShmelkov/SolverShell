#ifndef SOSH_SHELL_H
#define SOSH_SHELL_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

#include "SOSH_Function.h"


/**
 * @file SOSH_Shell.h
 * @brief Объявление класса SOSH_Shell.
 */

/**
 * @brief Класс, представляющий оболочку SOSH_Shell.
 * 
 * Оболочка SOSH_Shell предоставляет интерфейс для добавления, поиска и
 * отображения функций в рамках данной оболочки.
 */
class SOSH_Shell {
private:
    std::vector<std::reference_wrapper<SOSH_Function_Base>> funcs_pool; // Пул функций, хранящихся в оболочке.
    std::string name; // Имя оболочки.
public:

	/**
     * @brief Конструктор по умолчанию для класса SOSH_Shell.
     */
    SOSH_Shell() = default;
	
	/**
     * @brief Конструктор класса SOSH_Shell с заданным именем.
     * 
     * @param s Имя оболочки.
     */
    SOSH_Shell(const std::string &s) :name(s) {};
	
	/**
     * @brief Добавляет функцию в пул функций оболочки.
     * 
     * @param f Ссылка на объект типа SOSH_Function_Base, представляющий добавляемую функцию.
     * @return true, если функция успешно добавлена, в противном случае false.
     */
    bool AddFunction(SOSH_Function_Base &f); 
	
	/**
     * @brief Находит функцию по заданному имени.
     * 
     * @param s Имя функции.
     * @return Указатель на объект типа SOSH_Function_Base, представляющий найденную функцию. 
     *         Если функция не найдена, возвращается nullptr.
     */
    SOSH_Function_Base* FindFunction(const std::string &s); 
	
	/**
     * @brief Возвращает список функций, хранящихся в пуле функций оболочки.
     * 
     * @return Вектор, содержащий ссылки на объекты типа SOSH_Function_Base, представляющие функции в оболочке.
     */
    std::vector<std::reference_wrapper<SOSH_Function_Base>> ListFunction(); 
	
	/**
     * @brief Возвращает имя оболочки.
     * 
     * @return Имя оболочки.
     */
    std::string GetName(); 
};

#endif // SOSH_SHELL_H
