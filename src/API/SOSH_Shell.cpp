#include "sshell_api.h"

bool SOSH_Shell::AddFunction(SOSH_Function f) {
    funcs_pool.push_back(f);
    return true;
};

SOSH_Function SOSH_Shell::FindFunction(const std::string &s) {
    for (int i = 0; i <= funcs_pool.size() - 1; i++) {
        if (s == funcs_pool[i].Get()) {
            SOSH_Function &fp = funcs_pool[i]; // Security?
            return fp;
        };
    };
    //return nullptr; 
};

std::vector<SOSH_Function> SOSH_Shell::ListFunction() {
    return funcs_pool;
};

std::string SOSH_Shell::Get() {
    return name;
};
