#include "sshell_api.h"

bool SOSH_Manager::DeclareShell(const std::string &s) {
    SOSH_Shell func(s); // , &func = func;
    SHELL_POOL.push_back(func);
    return true;
};

SOSH_Shell SOSH_Manager::FindShell(const std::string &s) {
    for (int i = 0; i <= SHELL_POOL.size() - 1; i++) {
        if (s == SHELL_POOL[i].get()) {
            return SHELL_POOL[i];
        };
    };
    return nullptr;
};

std::vector<SOSH_Shell> SOSH_Manager::ListShell() {
    return SHELL_POOL;
};
