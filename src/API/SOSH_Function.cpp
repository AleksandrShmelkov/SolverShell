#include "sshell_api.h"

std::string SOSH_Function::Get() {
    return name;
};

bool SOSH_Function::AddFunction(const std::string &s, double (*l)(double,double)){
    name = s;
    link = l;
    return true;
};

double SOSH_Function::Run(double i, double j){
    return link(i,j);
};