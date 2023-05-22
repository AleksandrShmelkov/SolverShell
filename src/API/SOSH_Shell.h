#ifndef SOSH_SHELL_H
#define SOSH_SHELL_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

#include "API/SOSH_Function.h"

class SOSH_Shell {
private:
    std::vector<std::reference_wrapper<SOSH_Function_Base>> funcs_pool;
    std::string name;
public:
    SOSH_Shell() = default;
    SOSH_Shell(const std::string &s) :name(s) {};
    bool AddFunction(SOSH_Function_Base &f);
    SOSH_Function_Base* FindFunction(const std::string &s);
    std::vector<std::reference_wrapper<SOSH_Function_Base>> ListFunction();
    std::string GetName();
};

#endif