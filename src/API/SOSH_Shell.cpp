#include "sshell_api.h"

bool SOSH_Shell::DeclareFunction(const std::string &s) {
    SOSH_Function func(s);
    FUNCS_POOL.push_back(func);
    return true;
};

SOSH_Function SOSH_Shell::FindFunction(const std::string &s) {
    for (int i = 0; i <= FUNCS_POOL.size() - 1; i++) {
        if (s == FUNCS_POOL[i].get()) {
            SOSH_Function &fp = FUNCS_POOL[i]; // Security?
            return fp;
        };
    };
    return nullptr; 
};

std::vector<SOSH_Function> SOSH_Shell::ListFunction() {
    return FUNCS_POOL;
};

std::string SOSH_Shell::get() {
    return name;
};
