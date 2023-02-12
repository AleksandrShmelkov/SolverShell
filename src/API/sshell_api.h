#ifndef SSHELL_API_H
#define SSHELL_API_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>

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
    bool AddFunction(SOSH_Function &f);
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

enum class Token_t { SOSH_FUNCTION_NAME, SOSH_INT, SOSH_DOUBLE, SOSH_STRING, SOSH_UNDEFINED };

class SOSH_Token {
private:
    const Token_t token;
    const std::string value;
public:
    //SOSH_Token() = default; // возможно в дальнейшем удалим
    SOSH_Token(Token_t t, const std::string &s) :token(t), value(s) {};
    ~SOSH_Token() = default;
    /*void EditToken(Token_e t); // закомнентировать
    void EditValue(const std::string &s); // закомнентировать
    std::string TestToken(); // удалииь
    std::string TestValue(); // переименовать в Value
    // добавить функцию Type которая возврвщает тип токена
    // метод возвращающий данные в ее типе*/
    std::string Value(); // сделать шаблонной
    Token_t Type();
};

// SSHELL_toolkin.h файлы с токенами
// SSHELL_toolkin.cpp
// SOSH_function.h .cpp в нем классы фунции и аргументов


class SOSH_Parser { // IST
private:
    std::string value;
    std::vector<SOSH_Token> out;
public:
    SOSH_Parser() = default;
    ~SOSH_Parser() = default;
    std::vector<SOSH_Token> Tokenize(const std::string &s);
};

class SOSH_Arguments {
private:
public:
    SOSH_Arguments() = default;
    ~SOSH_Arguments() = default;
};

#endif
