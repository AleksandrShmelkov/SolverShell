#include "sshell_api.h"

bool SOSH_Manager::CreateShell(const std::string &s) {
    SOSH_Shell f(s); // , &func = func;
    shell_pool.push_back(f);
    return true;
};

SOSH_Shell SOSH_Manager::FindShell(const std::string &s) {
    for (int i = 0; i <= shell_pool.size() - 1; i++) {
        if (s == shell_pool[i].Get()) {
            return shell_pool[i];
        };
    };
    return nullptr;
};

std::vector<SOSH_Shell> SOSH_Manager::ListShell() {
    return shell_pool;
};
