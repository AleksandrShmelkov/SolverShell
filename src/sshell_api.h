#ifndef SSHELL_API_H
#define SSHELL_API_H

#include <iostream>
#include <vector>
#include <string>

class SOSH_Functions {
private:
    std::vector<std::string> names;
public:
    std::string get(int arg);
    void add(std::string s);
};

void SOSH_DeclareFunction (const std::string s);

#endif
