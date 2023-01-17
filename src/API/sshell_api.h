#ifndef SSHELL_API_H
#define SSHELL_API_H

#include <iostream>
#include <string>
#include <vector>

class SOSH_Function {
private:
    std::string name;
public:
    SOSH_Function() = default;
    SOSH_Function(const std::string &s) :name(s) {};
    ~SOSH_Function() = default;
    std::string get();
};

class SOSH_Shell {
private:
    std::vector<SOSH_Function> FUNCS_POOL;
    std::string name;
public:
    SOSH_Shell() = default;
    SOSH_Shell(const std::string &s) :name(s) {};
    ~SOSH_Shell() = default;
    bool DeclareFunction(const std::string &s);
    SOSH_Function FindFunction(const std::string &s);
    std::vector<SOSH_Function> ListFunction();
    std::string get();
};

class SOSH_Manager {
private:
    std::vector<SOSH_Shell> SHELL_POOL;
public:
    SOSH_Manager() = default;
    ~SOSH_Manager() = default;
    bool DeclareShell(const std::string &s);
    SOSH_Shell FindShell(const std::string &s);
    std::vector<SOSH_Shell> ListShell();
};

#endif
