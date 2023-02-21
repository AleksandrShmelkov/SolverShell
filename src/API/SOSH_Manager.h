#ifndef SOSH_MANAGER_H
#define SOSH_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

#include "API/SOSH_Shell.h"

class SOSH_Manager {
private:
    std::vector<SOSH_Shell> shell_pool;
public:
    bool AddShell(SOSH_Shell &s);
    SOSH_Shell FindShell(const std::string &s);
    std::vector<SOSH_Shell> ListShell();
};

#endif