#include "SOSH_Shell.h"

bool SOSH_Shell::AddFunction(SOSH_Function_Base &f) {
    funcs_pool.push_back(f);
    return true;
};

SOSH_Function_Base* SOSH_Shell::FindFunction(const std::string &s) {
    for (int i = 0; i < funcs_pool.size(); i++) {
        if (s == funcs_pool[i].get().GetName()) {
            return &funcs_pool[i].get();
        };
    };
    return nullptr; // Возвращает nullptr, если функция не найдена
};

std::vector<std::reference_wrapper<SOSH_Function_Base>> SOSH_Shell::ListFunction() {
    return funcs_pool;
};

std::string SOSH_Shell::GetName() {
    return name;
};
