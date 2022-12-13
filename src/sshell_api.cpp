#include "sshell_api.h"

std::string SOSH_Functions::get(int arg) {
    return names[arg];
};

void SOSH_Functions::add(std::string s){
    names.push_back(s);
}

void SOSH_DeclareFunction (const std::string s, SOSH_Functions func){
    func.add(s);
};
