#ifndef SOSH_MANAGER_CPP
#define SOSH_MANAGER_CPP

#include "SOSH_Manager.h"

bool SOSH_Manager::AddShell(SOSH_Shell &s) {
    shell_pool.push_back(s);
    return true;
};

SOSH_Shell SOSH_Manager::FindShell(const std::string &s) {
    for (int i = 0; i <= shell_pool.size() - 1; i++) {
        if (s == shell_pool[i].GetName()) {
            return shell_pool[i];
        };
    };
    return SOSH_Shell();
};

std::vector<SOSH_Shell> SOSH_Manager::ListShell() {
    return shell_pool;
};

#endif // SOSH_MANAGER_CPP
