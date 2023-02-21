#include "SOSH_Function.h"

std::string SOSH_Function::GetName() {
    return name;
};

bool SOSH_Function::EditFunction(const std::string &s, double (*l)(double,double)){
    name = s;
    link = l;
    return true;
};

double SOSH_Function::Run(double i, double j){
    return link(i, j);
};