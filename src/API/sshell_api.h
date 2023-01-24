#ifndef SSHELL_API_H
#define SSHELL_API_H

#include <iostream>
#include <string>
#include <vector>

class SOSH_Function {
private:
    std::string name;
    double (*link)(double,double);
    std::string arg;
public:
    SOSH_Function() = default;
    SOSH_Function(const std::string &s, double (*l)(double,double)) :name(s), link(l) {};
    ~SOSH_Function() = default;
    std::string Get();
    bool AddFunction(const std::string &s, double (*l)(double,double));
    double Run(double i, double j);
};

class SOSH_Shell {
private:
    std::vector<SOSH_Function> funcs_pool;
    std::string name;
public:
    SOSH_Shell() = default;
    SOSH_Shell(const std::string &s) :name(s) {};
    ~SOSH_Shell() = default;
    bool AddFunction(SOSH_Function f);
    SOSH_Function FindFunction(const std::string &s);
    std::vector<SOSH_Function> ListFunction();
    std::string Get();
};

class SOSH_Manager {
private:
    std::vector<SOSH_Shell> shell_pool;
public:
    SOSH_Manager() = default;
    ~SOSH_Manager() = default;
    bool CreateShell(const std::string &s);
    SOSH_Shell FindShell(const std::string &s);
    std::vector<SOSH_Shell> ListShell();
};

#endif
