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
    std::vector<SOSH_Function> funcs_pool;
    std::string name;
public:
    SOSH_Shell() = default;
    SOSH_Shell(const std::string &s) :name(s) {};
    bool AddFunction(SOSH_Function &f);
    SOSH_Function FindFunction(const std::string &s);
    std::vector<SOSH_Function> ListFunction();
    std::string GetName();
};

#endif