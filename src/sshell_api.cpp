#include "sshell_api.h"

//shellid_t CreateShell() {return 5};

//
// SOSH_Manager 
//

bool SOSH_Manager::DeclareShell(const std::string &s) {
    SOSH_Shell func(s); // , &func = func; // Работает ?
    SHELL_POOL.push_back(func);
    return true;
};

SOSH_Shell SOSH_Manager::FindShell(const std::string &s) {
    for (int i = 0; i <= SHELL_POOL.size() - 1; i++) {
        if (s == SHELL_POOL[i].get()) {
            return SHELL_POOL[i];
        };
    };
    //return false; // not SOSH_Shell // Что возвращать при отсутствии ?
};

std::vector<SOSH_Shell> SOSH_Manager::ListShell() {
    return SHELL_POOL;
};

//
// SOSH_Shell 
//

bool SOSH_Shell::DeclareFunction(const std::string &s) {
    SOSH_Function func(s);
    FUNCS_POOL.push_back(func);
    return true;
};

SOSH_Function SOSH_Shell::FindFunction(const std::string &s) {
    for (int i = 0; i <= FUNCS_POOL.size() - 1; i++) {
        if (s == FUNCS_POOL[i].get()) {
            return FUNCS_POOL[i];
        };
    };
    //return false; // not SOSH_Function // Что возвращать при отсутствии ?
};

std::vector<SOSH_Function> SOSH_Shell::ListFunction() {
    return FUNCS_POOL;
};

std::string SOSH_Shell::get() {
    return name;
};

//
// SOSH_Function 
//

std::string SOSH_Function::get() {
    return name;
};