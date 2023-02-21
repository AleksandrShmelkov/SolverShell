#ifndef SOSH_FUNCTION_H
#define SOSH_FUNCTION_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

class SOSH_Function {
private:
    std::string name;
    double (*link)(double,double);
    std::string arg;
public:
    SOSH_Function() = default;
    SOSH_Function(const std::string &s, double (*l)(double,double)) :name(s), link(l) {};
    bool EditFunction(const std::string &s, double (*l)(double,double));
    double Run(double i, double j);
    std::string GetName();
};

// SOSH_function.h .cpp в нем классы фунции и аргументов

#endif