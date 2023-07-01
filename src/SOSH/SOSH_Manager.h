#ifndef SOSH_MANAGER_H
#define SOSH_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

#include "SOSH_Shell.h"
#include "SOSH_Interpreter.h"


/**
 * @file SOSH_Manager.h
 * @brief Объявление класса SOSH_Manager.
 */

/**
 * @class SOSH_Manager
 * @brief Класс, отвечающий за управление несколькими экземплярами класса SOSH_Shell.
 */
class SOSH_Manager {
private:
    std::vector<SOSH_Shell> shell_pool; // Пулл экземпляров класса SOSH_Shell.
public:

	/**
     * @brief Добавляет экземпляр класса SOSH_Shell в пулл.
     * @param s Ссылка на экземпляр класса SOSH_Shell для добавления.
     * @return true, если добавление успешно, false в противном случае.
     */
    bool AddShell(SOSH_Shell &s); 
	
	/**
     * @brief Находит экземпляр класса SOSH_Shell в пулле по заданной строке.
     * @param s Строка для поиска экземпляра класса SOSH_Shell.
     * @return Найденный экземпляр класса SOSH_Shell или nullptr, если не найден.
     */
    SOSH_Shell FindShell(const std::string &s); 
	
	/**
     * @brief Возвращает список всех экземпляров класса SOSH_Shell в пулле.
     * @return Список экземпляров класса SOSH_Shell в пулле.
     */
    std::vector<SOSH_Shell> ListShell(); 
};

#endif // SOSH_MANAGER_H