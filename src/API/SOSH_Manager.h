#ifndef SOSH_MANAGER_H
#define SOSH_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

#include "SOSH_Shell.h"

/*

Класс SOSH_Manager представляет менеджер оболочек. Он содержит в себе список оболочек, которые могут быть добавлены, найдены или перечислены.

Поля класса:
- shell_pool - вектор объектов типа SOSH_Shell, который хранит все добавленные оболочки.

Методы класса:
- bool AddShell(SOSH_Shell &s) - метод, который добавляет объект типа SOSH_Shell в shell_pool. Метод возвращает true, если объект успешно добавлен, и false, если не удалось.
- SOSH_Shell FindShell(const std::string &s) - метод, который находит указанную оболочку по её имени и возвращает её объект типа SOSH_Shell.
- std::vector<SOSH_Shell> ListShell() - метод, который возвращает вектор объектов типа SOSH_Shell, содержащий все добавленные оболочки в shell_pool.

*/

class SOSH_Manager {
private:
    std::vector<SOSH_Shell> shell_pool; // вектор объектов типа SOSH_Shell, который хранит все добавленные оболочки
public:
    bool AddShell(SOSH_Shell &s); // метод, который добавляет объект типа SOSH_Shell в shell_pool
    SOSH_Shell FindShell(const std::string &s); // метод, который находит указанную оболочку по её имени и возвращает её объект типа SOSH_Shell
    std::vector<SOSH_Shell> ListShell(); // метод, который возвращает вектор объектов типа SOSH_Shell, содержащий все добавленные оболочки в shell_pool
};

#endif // SOSH_MANAGER_H